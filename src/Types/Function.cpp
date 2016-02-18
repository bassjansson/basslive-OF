//
//  Function.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "Function.hpp"


//========================================================================
Function::Function() : Identifier('(')
{
    charType = FUNCTION;
    
    identifier = new Identifier(':');
    close      = new Type(')');
    
    charSelected = this;
    
    typeColor = ofColor(0, 160, 190);
}

Function::~Function()
{
    charSelected = identifier;
    removeSelectedChar(true);
    
    charSelected = close;
    removeSelectedChar(true);
}

//========================================================================
Character* Function::draw (float& x, float& y, bool v)
{
    // Draw function type
    Character* c = Type::draw(x, y, v);
    float indent = x;
    
    // Draw function arguments
    for (int i = 0; true; i++)
    {
        if (c == NULL)
            return NULL;
        
        if (c == close)
        {
            x -= charWidth;
            return c->draw(x, y, HORIZONTAL);
        }
        
        if (c == identifier)
        {
            x -= charWidth;
            c = c->draw(x, y, HORIZONTAL);
            indent = x;
        }
        else
        {
            if ((i > 1) &&
                (c->getCharType() == FUNCTION ||
                 c->getCharacter(LEFT)->getCharType() == FUNCTION_BODY))
            {
                x = indent;
                c = c->draw(x, y, VERTICAL);
            }
            else
            {
                c = c->draw(x, y, HORIZONTAL);
            }
        }
    }
}

//========================================================================
void Function::mousePressedMain (float x, float y, int button)
{
    charSelected->getCharacter(RIGHT)->mousePressed(x - charWidth/2, y, button);
}

void Function::keyPressedMain (int key)
{
    charCursorTime = 0;
    
    
    if (charSelected != close)
    {
        if (!ofGetKeyPressed(OF_KEY_COMMAND))
            charSelected->getParentType()->keyPressed(key);
        
        if (charSelected->getParentType() != this)
        {
            if (ofGetKeyPressed(OF_KEY_COMMAND))
            {
                switch (key)
                {
                    case 'f': removeSelectedType(true); new Function(); break;
                    case 'i': removeSelectedType(true); new Identifier('$'); break;
                    case 'n': removeSelectedType(true); new Number(); break;
                }
            }
            else
            {
                switch (key)
                {
                    case OF_KEY_RETURN:
                    case '(': removeSelectedType(true); new Function(); break;
                    case '$': removeSelectedType(true); new Identifier('$'); break;
                    case '#': removeSelectedType(true); new Number(); break;

                    case ' ':
                        removeSelectedType(true); 
                        if (ofGetKeyPressed(OF_KEY_SHIFT))
                            new Identifier('$');
                        else
                            new Number();
                        break;
                }
            }
        }
    }
    
    
    if (ofGetKeyPressed(OF_KEY_SHIFT))
    {
        switch (key)
        {
            case OF_KEY_BACKSPACE:
                charSelected = charSelected->getParentType();
                removeSelectedChar(false);
                break;
                
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
                charSelected = charSelected->getFunction(UP);
                break;
                
            case OF_KEY_DOWN:
                charSelected = charSelected->getFunction(DOWN);
                break;
        }
    }
    else
    {
        switch (key)
        {
            case OF_KEY_BACKSPACE:
                removeSelectedChar(false);
                break;
                
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
                charSelected = charSelected->getType(UP);
                break;
                
            case OF_KEY_DOWN:
                charSelected = charSelected->getType(DOWN);
                break;
        }
    }
}

//========================================================================
bool Function::removeSelectedType (bool removeFunctions)
{
    if (removeFunctions &&
        (charSelected->getParentType() != this) &&
        (charSelected->getParentType()->getCharType() == FUNCTION))
        charSelected = charSelected->getParentType();
    
    if (charSelected->getCharType() != CHARACTER)
        return removeSelectedChar(false);
    
    return false;
}
