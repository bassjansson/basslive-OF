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
    
    sig output = *memory->getDAC()->getOutput();
    
    float newRMS = 0.0f;
    
    for (tick t = 0; t < output.size(); t++)
         newRMS += powf(output[t].L, 2.0f);
    
    newRMS = sqrtf(newRMS / output.size());
    
    RMS = 0.8f * RMS + 0.2f * newRMS;
    
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
                case 'f': add(new NumberType()); break;
                case 'i': add(new  InputType()); break;
                case 'm': add(new ModuleType()); break;
                    
                case 'n': add(new ModuleFunction()); break;
                case 'b': add(new BufferFunction()); break;
                    
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
                case CHAR_TYPE_NUMBER: charSelected->add(new NumberType()); break;
                case CHAR_TYPE_INPUT : charSelected->add(new  InputType()); break;
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
                charSelected = charSelected->getFunction(LEFT);
                break;
                
            case OF_KEY_RIGHT:
                charSelected = charSelected->getFunction(RIGHT);
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
                charSelected = charSelected->getType(UP);
                break;
                
            case OF_KEY_DOWN:
                charSelected = charSelected->getType(DOWN);
                break;
        }
    }
}

sig* MainFunction::compile (Memory* memory, bool record)
{
    int channel = 0;
    
    for (Character* c = getType(RIGHT);
         c != end();
         c = c->end()->right)
    {
        Type* t = (Type*)c;
        
        // TODO: set remaining inputs to zero
        memory->getDAC()->setInput(t->compile(memory, record), channel);
        channel++;
    }
    
    flash(COLOR_FUNC_MAIN);
}

//========================================================================
void MainFunction::mousePressed (float x, float y, int button)
{
    if (button == OF_MOUSE_BUTTON_LEFT)
    {
        for (Character* c = begin; c != end(); c = c->right)
        {
            if (c != charSelected &&
                (x >= c->x - 1 && x < c->x + charWidth  + 1) &&
                (y >= c->y - 1 && y < c->y + charHeight + 1))
            {
                charSelected = c;
                return;
            }
        }
    }
}

void MainFunction::mouseReleased (float x, float y, int button)
{
    x -= charWidth * 0.5f;
    
    if (button == OF_MOUSE_BUTTON_LEFT)
    {
        for (Character* c = begin; c != end(); c = c->right)
        {
            if (c != charSelected &&
                (x >= c->x - 1 && x < c->x + charWidth  + 1) &&
                (y >= c->y - 1 && y < c->y + charHeight + 1))
            {
                c->add(charSelected, false);
                return;
            }
        }
    }
}
