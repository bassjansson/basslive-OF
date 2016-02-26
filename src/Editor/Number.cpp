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
    typeColor = ofColor(100, 89, 176);
    
    value = 0.0f;
}

//========================================================================
void Number::keyPressed (int key)
{
    if ((key > 47 && key < 58) || key == 46)
    {
        typeColor = ofColor(100, 89, 176);
        new Character(key, mf);
    }
}

void Number::trigger()
{
    char* err;
    
    typeColor = ofColor(120, 109, 196);
    value = strtof(typeString.c_str(), &err);
    
    if (*err != 0)
    {
        typeColor = ofColor(255, 0, 0);
        value = 0.0f;
    }
    
    for (tick t = 0; t < BUFFERSIZE; t++)
        typeSignal[t] = value;
}
