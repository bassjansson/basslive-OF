//
//  Function.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "Types.h"


//========================================================================
Function::Function (char open, char type, char close, MainFunction* mf)
: Type(open, mf)
{
    charType = FUNCTION;
    
    
    if (type == CHAR_TYPE_MOD_ID)
        identifier = new ModuleType(mf);
    else if (type == CHAR_TYPE_BUF_ID)
        identifier = new BufferType(mf);
    else
        identifier = new Type(type, mf);

    this->close = new Type(close, mf);
    
    
    identifier->charType  = FUNCTION_BODY;
    this->close->charType = FUNCTION_BODY;
    
    
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
Character* Function::getEndChar()
{
    return close;
}

Character* Function::draw (float& x, float& y, bool vertical, bool selection)
{
    // Draw function type
    selection = selection || mf->charSelected == this;
    Character* c = Type::draw(x, y, vertical, selection);
    float indent = x;
    
    
    // Draw function arguments
    for (int i = 0; true; i++)
    {
        if (c == NULL)
            return NULL;
        
        if (c == close)
        {
            x -= mf->charWidth;
            return c->draw(x, y, HORIZONTAL, selection);
        }
        
        if (c == identifier)
        {
            x -= mf->charWidth;
            c = c->draw(x, y, HORIZONTAL, selection);
            indent = x;
        }
        else
        {
            if ((i > 1) &&
                (c->charType == FUNCTION ||
                 c->getCharacter(LEFT)->charType == FUNCTION_BODY))
            {
                x = indent;
                c = c->draw(x, y, VERTICAL, selection);
            }
            else
            {
                c = c->draw(x, y, HORIZONTAL, selection);
            }
        }
    }
}

//========================================================================
string Function::getIdentifierString()
{
    return identifier->getTypeString();
}
