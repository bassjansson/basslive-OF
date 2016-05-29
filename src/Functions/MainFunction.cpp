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
    charSelected = begin;
    
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
void MainFunction::draw()
{
    float x = charWidth;
    float y = charHeight;
    
    Function::draw(x, y, HORIZONTAL, false, false);
    
    // Update RMS
    RMS = RMS * 0.8f + memory->getDAC()->getRMS().L * 0.2f;
    
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
    if (charSelected != end())
    {
        if (ofGetKeyPressed(OF_KEY_COMMAND))
        {
            switch (key)
            {
                case 'i': add(new InputType());      break;
                case 'm': add(new ModuleType());     break;
                case 'n': add(new ModuleFunction()); break;
                    
                case 'r':
                case OF_KEY_RETURN:
                    if (ofGetKeyPressed(OF_KEY_SHIFT))
                        charSelected = begin;
                    charSelected->getParentType()->compile(memory, key == 'r');
                    break;
            }
        }
        else
        {
            Type* parent = charSelected->getParentType();
            if (parent == this)
                Function::keyPressed(key);
            else
                parent->keyPressed(key);
            
            switch (key)
            {
                case CHAR_TYPE_NUMBER : charSelected->add(new  NumberType()); break;
                case CHAR_TYPE_PERCENT: charSelected->add(new PercentType()); break;
                case CHAR_TYPE_INPUT  : charSelected->add(new   InputType()); break;
                case CHAR_TYPE_MOD_ID : charSelected->add(new  ModuleType()); break;
                case CHAR_TYPE_BUF_ID : charSelected->add(new  BufferType()); break;
                    
                case CHAR_FUNC_MOD_OPEN: charSelected->add(new ModuleFunction()); break;
                case CHAR_FUNC_BUF_OPEN: charSelected->add(new BufferFunction()); break;
                    
                case ' ':
                    if (ofGetKeyPressed(OF_KEY_SHIFT))
                        charSelected->add(new PercentType());
                    else
                        charSelected->add(new NumberType());
                    break;
                    
                case OF_KEY_RETURN:
                    if (ofGetKeyPressed(OF_KEY_SHIFT))
                        charSelected->add(new BufferFunction());
                    else
                        charSelected->add(new ModuleFunction());
                    break;
                    
                case OF_KEY_BACKSPACE:
                    if (ofGetKeyPressed(OF_KEY_SHIFT))
                        charSelected = charSelected->getParentType();
                    charSelected->remove();
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
                charSelected = charSelected->end();
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
                charSelected = charSelected->left;
                break;
                
            case OF_KEY_RIGHT:
                charSelected = charSelected->right;
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

sig* MainFunction::compile (Memory* memory, bool record)
{
    sig_vec inputs;
    
    for (Character* c = getType(RIGHT);
         c != end();
         c = c->end()->right)
    {
        Type* t = (Type*)c;
        
        inputs.push_back(t->compile(memory, record));
    }
    
    memory->getDAC()->setInputs(inputs);
    inputs.clear();
    
    flash(COLOR_FUNC_MAIN);
}

//========================================================================
void MainFunction::mousePressed (float x, float y, int button)
{
    if (button == OF_MOUSE_BUTTON_LEFT || button == OF_MOUSE_BUTTON_RIGHT)
    {
        for (Character* c = begin; c != end(); c = c->right)
        {
            if ((x >= c->x && x < c->x + charWidth) &&
                (y >= c->y && y < c->y + charHeight))
            {
                if (button == OF_MOUSE_BUTTON_LEFT)
                {
                    charSelected = c;
                }
                else
                {
                    if (c->charType == TYPE)
                        ((Type*)c)->copyTo(begin);
                    else if (c->charType == FUNC)
                        ((Function*)c)->copyTo(begin);
                }
                
                return;
            }
        }
    }
}

void MainFunction::mouseReleased (float x, float y, int button)
{
    x -= charWidth * 0.5f;
    
    if (button == OF_MOUSE_BUTTON_LEFT && charSelected->charType != CHAR)
    {
        for (Character* c = begin; c != end(); c = c->right)
        {
            if (c != charSelected &&
                (x >= c->x && x < c->x + charWidth) &&
                (y >= c->y && y < c->y + charHeight))
            {
                c->add(charSelected, false);
                return;
            }
        }
    }
}
