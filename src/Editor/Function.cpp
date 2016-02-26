//
//  Function.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "MainFunction.hpp"


//========================================================================
Function::Function (MainFunction* mf) : Identifier(CHAR_FUNC_OPEN, mf)
{
    charType = FUNCTION;
    
    typeColor = ofColor(0, 160, 190);
    
    identifier = new Identifier(CHAR_FUNC_IDEN, mf);
    close      = new Type(CHAR_FUNC_CLOSE, mf);
    
    mf->charSelected = this;
}

Function::~Function()
{
    mf->charSelected = identifier;
    removeSelectedChar(true);
    
    mf->charSelected = close;
    removeSelectedChar(true);
}

//========================================================================
Character* Function::draw (float& x, float& y, bool vertical)
{
    // Draw function type
    Character* c = Type::draw(x, y, vertical);
    float indent = x;
    
    // Draw function arguments
    for (int i = 0; true; i++)
    {
        if (c == NULL)
            return NULL;
        
        if (c == close)
        {
            x -= mf->charWidth;
            return c->draw(x, y, HORIZONTAL);
        }
        
        if (c == identifier)
        {
            x -= mf->charWidth;
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

void Function::keyPressed (int key)
{
    if (key > 47 && key < 58)
    {
        if (mf->charSelected != this)
            new Character(key, mf);
    }
    else if ((key > 64 && key < 91) ||
             (key > 96 && key < 123))
    {
        new Character(key, mf);
    }
}
