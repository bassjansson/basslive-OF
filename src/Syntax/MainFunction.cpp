//
//  MainFunction.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 18/02/16.
//
//

#include "Types.h"


//========================================================================
MainFunction::MainFunction (string name) : Function(this)
{
    ofxGuiPage::setup(name);
    
    charFont.load("fonts/Menlo-Bold.ttf", FONT_SIZE * 2);
    charWidth = charFont.stringWidth("X");
    charHeight = charFont.stringHeight("Xgj{|");
    charCursorTime = 0;
    
    // Create main
    new Character('m', mf);
    new Character('a', mf);
    new Character('i', mf);
    new Character('n', mf);
    charSelected = identifier;
    new Function(mf);
}

MainFunction::~MainFunction()
{
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
    charCursorTime = 0;
    
    
    // Add and remove characters
    if (charSelected->getParentType() != mf &&
        charSelected->getParentType() != close)
    {
        if (ofGetKeyPressed(OF_KEY_COMMAND))
        {
            switch (key)
            {
                case 'f': removeTypeIfSelected(); new Function(mf); break;
                case 'i': removeTypeIfSelected(); new Identifier(mf); break;
                case 'n': removeTypeIfSelected(); new Number(mf); break;
                    
                case 'o':
                    charSelected = identifier;
                    new Function(mf);
                    break;
                    
                case OF_KEY_RETURN:
                    charSelected->getParentType()->trigger();
                    break;
            }
        }
        else
        {
            charSelected->getParentType()->keyPressed(key);
            
            switch (key)
            {
                case OF_KEY_RETURN:
                case '(': removeTypeIfSelected(); new Function(mf); break;
                case '$': removeTypeIfSelected(); new Identifier(mf); break;
                case '#': removeTypeIfSelected(); new Number(mf); break;
                    
                case ' ':
                    removeTypeIfSelected();
                    if (ofGetKeyPressed(OF_KEY_SHIFT))
                        new Identifier(mf);
                    else
                        new Number(mf);
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
bool MainFunction::removeTypeIfSelected()
{
    if (charSelected->getCharType() != CHARACTER)
        removeSelectedChar(false);
    else
    {
        if (charSelected->getParentType()->getCharType() == FUNCTION)
            charSelected = charSelected->getType(RIGHT)
                           ->getType(RIGHT)->getCharacter(LEFT);
        else
            charSelected = charSelected->getType(RIGHT)->getCharacter(LEFT);
    }
}

//========================================================================
Function* MainFunction::getFunctionWithID (string id)
{
    Function* f = getFunction(RIGHT);
    
    while (true)
    {
        if (f == NULL || f == mf)
            return NULL;
        
        if (f->getType(RIGHT)->getTypeString() == id)
            return f;
        
        f = f->getFunction(RIGHT);
    }
}

//========================================================================
void MainFunction::render()
{
    ofxGuiPage::render();
    
    
    ofPushMatrix();
    
    float x = 0;
    float y = 0;
    
    Function::draw(x, y, HORIZONTAL);
    
    if (charCursorTime < FRAME_RATE / 2)
        charSelected->drawCursor();
    
    float xScale = (ofGetWidth()  - FONT_SIZE * 4) / x;
    float yScale = (ofGetHeight() - FONT_SIZE * 6) / y;
    
    ofScale(xScale, yScale);
    ofTranslate(FONT_SIZE * 2, FONT_SIZE * 4);
    
    ofPopMatrix();
    
    
    charCursorTime = (charCursorTime + 1) % FRAME_RATE;
    
    
    string id = identifier->getTypeString();
    if (id != "") setName(id);
}
