//
//  Number.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 17/02/16.
//
//

#include "Types.h"


//========================================================================
NumberType::NumberType (MainFunction* mf)
: Type(CHAR_TYPE_NUMBER, mf)
{
    typeType = NUMBER;
}

//========================================================================
void NumberType::keyPressed (int key)
{
    if ((key > 47 && key < 58) || key == 46)
        new Character(key, mf);
}

void NumberType::trigger()
{
    char* err;
    float value = strtof(getTypeString().c_str(), &err);
    
    if (*err == 0)
    {
        flash(ofColor(120, 109, 196));
    }
    else
    {
        flash(ofColor(255, 0, 0));
        value = 0.0f;
    }
    
    for (tick t = 0; t < BUFFERSIZE; t++)
        typeSignal[t] = value;
}
