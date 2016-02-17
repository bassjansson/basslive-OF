//
//  Function.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "Function.hpp"


//========================================================================
Function::Function() : Name('(')
{
    charType = FUNCTION;
    noneType = true;
    
    identifier = new Name(':');
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
            return c->draw(x, y, HORIZONTAL);
        
        if (c == identifier)
        {
            c = c->draw(x, y, HORIZONTAL);
            indent = x + charWidth;
        }
        else
        {
            x = indent;
            c = c->draw(x, y, i > 1);
        }
    }
}

//void Function::keyPressed (int key)
//{
//    
//}

//========================================================================
void Function::keyPressedMain (int key)
{
    charCursorTime = 0;
    
    if (key > 31 && key < 127 && charSelected != close)
    {
        switch (key)
        {
            case '(':
                if (!charSelected->getNoneType()) new Function();
                break;
                
            case '$':
                if (!charSelected->getNoneType()) new Name(key);
                break;
                
            case '#':
                if (!charSelected->getNoneType()) new Number();
                break;
                
            default:
                Type* t = charSelected->getParentType();
                if (t) t->keyPressed(key);
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
                
            case OF_KEY_LEFT:
                moveLeft();
                break;
                
            case OF_KEY_RIGHT:
                moveRight();
                break;
                
            default:
                break;
        }
    }
}
