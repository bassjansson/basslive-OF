//
//  MainFunction.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 18/02/16.
//
//

#include "Types.h"


//========================================================================
MainFunction::MainFunction (const string& name)
: ModuleFunction(this)
{
    ofxGuiPage::setup(name);
    
    charFont.load("fonts/Menlo-Bold.ttf", FONT_SIZE * 2);
    charWidth  = charFont.stringWidth("X");
    charHeight = charFont.stringHeight("Xgj{|");
    
    moduleIDCounter = 0;
    bufferIDCounter = 0;
    
    cursorTime = 0;
    beatLength = SAMPLERATE / 2;
    barLength  = beatLength * 4;
    
    adc = new sample[BUFFERSIZE];
    for (tick t = 0; t < BUFFERSIZE; t++)
        adc[t] = 0.0f;
    
    // Create main mixer
    new Character('+', mf);
    charSelected = identifier;
    new ModuleFunction(mf);
}

MainFunction::~MainFunction()
{
    delete[] adc;
    
    // TODO: delete all characters
}

//========================================================================
void MainFunction::mousePressed (float x, float y, int button)
{
    Character::mousePressed(x, y, button);
}

void MainFunction::mouseReleased (float x, float y, int button)
{
    Character::mouseReleased(x - charWidth / 2, y, button);
}

void MainFunction::keyPressed (int key)
{
    cursorTime = 0;
    
    
    // Add and remove characters
    if (charSelected->getParentType() != mf &&
        charSelected->getParentType() != close)
    {
        if (ofGetKeyPressed(OF_KEY_COMMAND))
        {
            switch (key)
            {
                case 'n': removeTypeIfSelected(); new NumberType(mf); break;
                case 'i': removeTypeIfSelected(); new InputType(mf); break;
                case 'm': removeTypeIfSelected(); new ModuleType(mf); break;
                case 'b': removeTypeIfSelected(); new BufferType(mf); break;
                    
                case 'f': removeTypeIfSelected(); new ModuleFunction(mf); break;
                case 'g': removeTypeIfSelected(); new BufferFunction(mf); break;
                    
                case 'o':
                    charSelected = identifier->getEndChar();
                    new ModuleFunction(mf);
                    break;
                    
                case OF_KEY_RETURN:
                    if (ofGetKeyPressed(OF_KEY_SHIFT))
                        charSelected = this;
                    charSelected->getParentType()->trigger();
                    break;
            }
        }
        else
        {
            charSelected->getParentType()->keyPressed(key);
            
            switch (key)
            {
                case CHAR_TYPE_NUMBER: removeTypeIfSelected(); new NumberType(mf); break;
                case CHAR_TYPE_INPUT:  removeTypeIfSelected(); new InputType(mf); break;
                case CHAR_TYPE_MOD_ID: removeTypeIfSelected(); new ModuleType(mf); break;
                case CHAR_TYPE_BUF_ID: removeTypeIfSelected(); new BufferType(mf); break;
                    
                case OF_KEY_RETURN:
                case CHAR_FUNC_MOD_OPEN: removeTypeIfSelected(); new ModuleFunction(mf); break;
                case CHAR_FUNC_BUF_OPEN: removeTypeIfSelected(); new BufferFunction(mf); break;
                    
                case ' ':
                    removeTypeIfSelected();
                    if (ofGetKeyPressed(OF_KEY_SHIFT))
                        new ModuleType(mf);
                    else
                        new NumberType(mf);
                    break;
                    
                case OF_KEY_BACKSPACE:
                    if (ofGetKeyPressed(OF_KEY_SHIFT))
                        charSelected = charSelected->getParentType();
                    removeSelectedChar(false);
                    break;
            }
        }
    }
    
    
    // Move cursor
    if (ofGetKeyPressed(OF_KEY_SHIFT))
    {
        switch (key)
        {
            case OF_KEY_TAB:
                charSelected = charSelected->getType(LEFT);
                break;
                
            case OF_KEY_LEFT:
                charSelected = charSelected->getType(LEFT);
                break;
                
            case OF_KEY_RIGHT:
                charSelected = charSelected->getType(RIGHT);
                break;
                
            case OF_KEY_UP:
                charSelected = mf;
                break;
                
            case OF_KEY_DOWN:
                charSelected = mf;
                break;
        }
    }
    else
    {
        switch (key)
        {
            case OF_KEY_TAB:
                charSelected = charSelected->getType(RIGHT);
                break;
                
            case OF_KEY_LEFT:
                charSelected = charSelected->getCharacter(LEFT);
                break;
                
            case OF_KEY_RIGHT:
                charSelected = charSelected->getCharacter(RIGHT);
                break;
                
            case OF_KEY_UP:
                charSelected = charSelected->getFunction(UP);
                break;
                
            case OF_KEY_DOWN:
                charSelected = charSelected->getFunction(DOWN);
                break;
        }
    }
}

//========================================================================
int MainFunction::getNewModuleID()
{
    return ++moduleIDCounter;
}

int MainFunction::getNewBufferID()
{
    return ++bufferIDCounter;
}

//========================================================================
tick MainFunction::getBeatLength()
{
    return beatLength;
}

tick MainFunction::getBarLength()
{
    return barLength;
}

//========================================================================
sig MainFunction::getADC (int channel)
{
    if (channel == 0)
        return adc;
    else
        return NULL;
}

//========================================================================
void MainFunction::render()
{
    // TODO not working
    string id = getIdentifierString();
    if (id != "") setName(id);
    
    ofxGuiPage::render();
    
    float x = FONT_SIZE * 2;
    float y = FONT_SIZE * 4;
    
    Function::draw(x, y, VERTICAL, false);
    
    if (cursorTime < FRAME_RATE / 2)
        charSelected->drawCursor();
    
    cursorTime = (cursorTime + 1) % FRAME_RATE;
}

bool MainFunction::removeTypeIfSelected()
{
    if (charSelected->charType != CHARACTER)
        removeSelectedChar(false);
    else
    {
        if (charSelected->getParentType()->charType == FUNCTION)
            charSelected = charSelected->getType(RIGHT)
            ->getType(RIGHT)->getCharacter(LEFT);
        else
            charSelected = charSelected->getType(RIGHT)->getCharacter(LEFT);
    }
}
