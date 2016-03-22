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
    
    this->close = new Type(close);
    this->close->charType = CLOSE;
    add(this->close);
}

//========================================================================
void Function::draw (float& x, float& y, bool vertical, bool selection, bool floating)
{
    // Draw function type
    selection = selection || charSelected == begin;
    
    Type::draw(x, y, vertical, selection, floating);
    Character* c = getType(RIGHT);
    
    float indent = x + charWidth;
    
    if (c == identifier)
    {
        c->draw(x, y, HORIZONTAL, selection, false);
        c = c->getType(RIGHT);
        
        indent = x + charWidth;
    }
    
    
    // Draw function arguments
    for (int i = 0; true; i++)
    {
        if (c == end())
        {
            c->draw(x, y, HORIZONTAL, selection, false);
            break;
        }
        
        bool v = i > 0 && (c->charType == FUNC || c->left->charType == CLOSE);
        
        if (v) x  = indent;
        else   x += charWidth;
        
        c->draw(x, y, v, selection, false);//charType == MAIN);
        c = c->end()->right;
    }
}

void Function::flash (const ofColor& color)
{
     Type::flash(color);
    close->flash(color);
}

Character* Function::end()
{
    return close;
}
