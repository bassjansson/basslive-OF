//
//  Function.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "Syntax.h"


//========================================================================
Function::Function (char open, char close) : Type(open)
{
    charType = FUNC;
    
    identifier = NULL;
    add(this->close = new Type(close));
    this->close->charType = BODY;
}

//========================================================================
void Function::draw (float& x, float& y, bool vertical, bool selection)
{
    // Draw function type
    selection = selection || charSelected == this;
    Type::draw(x, y, vertical, selection);
    Character* c = identifier;
    if (c == NULL) c = getType(RIGHT);
    float indent = x;
    
    
    // Draw function arguments
    for (int i = 0; true; i++)
    {
        if (c == identifier)
        {
            c->draw(x, y, HORIZONTAL, selection);
            indent = x + charWidth;
        }
        else if (c == close)
        {
            c->draw(x, y, HORIZONTAL, selection);
            break;
        }
        else
        {
            if ((i > 1) &&
                (c->charType == FUNC ||
                 c->getLeftChar()->charType == BODY))
            {
                x = indent;
                c->draw(x, y, VERTICAL, selection);
            }
            else
            {
                x += charWidth;
                c->draw(x, y, HORIZONTAL, selection);
            }
        }
        
        c = c->getEndChar()->getRightChar();
    }
}
