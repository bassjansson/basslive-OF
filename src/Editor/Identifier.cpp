//
//  Identifier.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 17/02/16.
//
//

#include "MainFunction.hpp"


//========================================================================
Identifier::Identifier (char c, MainFunction* mf) : Type(c, mf)
{
    value = NULL;
}

Identifier::Identifier (MainFunction* mf) : Type(CHAR_TYPE_IDEN, mf)
{
    value = NULL;
}

//========================================================================
Type* Identifier::process (sig& output, Clock& clock)
{
    output = typeSignal;
    
    if (value) value->process(output, clock);
    
    return getType(RIGHT);
}

void Identifier::keyPressed (int key)
{
    if (key > 47 && key < 58)
    {
        if (mf->charSelected != this)
        {
            typeColor = ofColor(255);
            new Character(key, mf);
        }
    }
    else if ((key > 64 && key < 91) ||
             (key > 96 && key < 123))
    {
        typeColor = ofColor(255);
        new Character(key, mf);
    }
}

void Identifier::trigger()
{
    value = mf->getFunctionWithID(typeString);
    
    if (value) typeColor = ofColor(121, 182, 77);
}
