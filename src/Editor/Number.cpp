//
//  Number.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 17/02/16.
//
//

#include "MainFunction.hpp"


//========================================================================
Number::Number (MainFunction* mf) : Type(CHAR_TYPE_NUMB, mf)
{
    typeColor = ofColor(120, 109, 196);
}

//========================================================================
void Number::keyPressed (int key)
{
    if ((key > 47 && key < 58) || key == 46)
        new Character(key, mf);
}
