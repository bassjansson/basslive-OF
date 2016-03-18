//
//  MainFunction.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 18/02/16.
//
//

#include "Syntax.h"


//========================================================================
MainFunction::MainFunction (Memory* memory) : Function(CHAR_FUNC_MAIN_OPEN,
                                                       CHAR_FUNC_MAIN_CLOSE)
{
    charType = MAIN;
    typeType = MODULE;
    
    charFont.load("fonts/Menlo-Bold.ttf", FONT_SIZE);
    charWidth    = charFont.stringWidth("X");
    charHeight   = charFont.stringHeight("Xgj{|");
    charSelected = this;
    
    this->memory = memory;
    this->cursorTime = 0;
    
                  add(new Character('B'));
    charSelected->add(new Character('a'));
    charSelected->add(new Character('s'));
    charSelected->add(new Character('s'));
    charSelected->add(new Character('L'));
    charSelected->add(new Character('i'));
    charSelected->add(new Character('v'));
    charSelected->add(new Character('e'));
    
    flash(COLOR_FUNC_MAIN);
}

MainFunction::~MainFunction()
{
    remove(true);
}

//========================================================================
sig* MainFunction::compile (Memory* memory, bool record)
{
    int channel = 0;
    
    for (Type* t = getType(RIGHT);
         t != close;
         t = t->getEndChar()->getType(RIGHT))
    {
        memory->getDAC()->setInput(t->compile(memory, record), channel);
        channel++;
    }
    
    flash(COLOR_FUNC_MAIN);
}

//========================================================================
void MainFunction::draw()
{
    float x = ofGetWidth()  * 0.5f - charWidth * 6.0f;
    float y = ofGetHeight() * 0.5f - charHeight;
    
    Function::draw(x, y, VERTICAL, false, true);
    
    if (cursorTime < FRAME_RATE / 2)
        charSelected->drawCursor();
    
    cursorTime = (cursorTime + 1) % FRAME_RATE;
}

//========================================================================
void MainFunction::keyPressed (int key)
{
    // Reset cursor time when typing
    cursorTime = 0;
    
    
    // Add and remove characters
    if (charSelected != close)
    {
        if (ofGetKeyPressed(OF_KEY_COMMAND))
        {
            switch (key)
            {
                case 'n': charSelected->add(new NumberType()); break;
                case 'i': charSelected->add(new InputType());  break;
                case 'm': charSelected->add(new ModuleType()); break;
                case 'b': charSelected->add(new BufferType()); break;
                    
                case 'f': charSelected->add(new ModuleFunction()); break;
                case 'g': charSelected->add(new BufferFunction()); break;
                    
                case 'o': add(new ModuleFunction()); break;
                    
                case 'r':
                case OF_KEY_RETURN:
                    if (ofGetKeyPressed(OF_KEY_SHIFT))
                        charSelected = this;
                    charSelected->getParentType()->compile(memory, key == 'r');
                    break;
            }
        }
        else
        {
            Type* parent = charSelected->getParentType();
            if (parent->charType == MAIN)
                Function::keyPressed(key);
            else
                parent->keyPressed(key);
            
            switch (key)
            {
                case CHAR_TYPE_NUMBER: charSelected->add(new NumberType()); break;
                case CHAR_TYPE_INPUT:  charSelected->add(new InputType());  break;
                case CHAR_TYPE_MOD_ID: charSelected->add(new ModuleType()); break;
                case CHAR_TYPE_BUF_ID: charSelected->add(new BufferType()); break;
                    
                case CHAR_FUNC_MOD_OPEN: charSelected->add(new ModuleFunction()); break;
                case CHAR_FUNC_BUF_OPEN: charSelected->add(new BufferFunction()); break;
                    
                case ' ':
                    if (ofGetKeyPressed(OF_KEY_SHIFT))
                        charSelected->add(new ModuleType());
                    else
                        charSelected->add(new NumberType());
                    break;
                    
                case OF_KEY_RETURN:
                    if (ofGetKeyPressed(OF_KEY_SHIFT))
                        add(new ModuleFunction());
                    else
                        charSelected->add(new ModuleFunction());
                    break;
                    
                case OF_KEY_BACKSPACE:
                    if (ofGetKeyPressed(OF_KEY_SHIFT))
                        charSelected = charSelected->getParentType();
                    charSelected->remove(false);
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
                charSelected = charSelected->getParentType();
                break;
                
            case OF_KEY_DOWN:
                charSelected = charSelected->getEndChar()->getRightChar();
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
                charSelected = charSelected->getLeftChar();
                break;
                
            case OF_KEY_RIGHT:
                charSelected = charSelected->getRightChar();
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
