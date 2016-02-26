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
    typeColor = ofColor(131, 192, 87);
}

Identifier::Identifier (MainFunction* mf) : Type(CHAR_TYPE_IDEN, mf)
{
    typeColor = ofColor(131, 192, 87);
}

//========================================================================
void Identifier::keyPressed (int key)
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
