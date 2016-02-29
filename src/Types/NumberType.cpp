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
    
    value = 0.0f;
}

//========================================================================
void NumberType::keyPressed (int key)
{
    if ((key > 47 && key < 58) || key == 46)
        new Character(key, mf);
}

void NumberType::trigger()
{
    if (getTypeString() == "")
    {
        mf->charSelected = this;
        new Character('0', mf);
        new Character('.', mf);
        new Character('0', mf);
    }
    
    char* err;
    value = strtof(getTypeString().c_str(), &err);
    
    if (*err == 0)
    {
        flash(COLOR_TYPE_NUMBER);
    }
    else
    {
        flash(COLOR_ERROR);
        value = 0.0f;
    }
    
    for (tick t = 0; t < BUFFERSIZE; t++)
        typeSignal[t] = value;
}

//========================================================================
float NumberType::getValue()
{
    return value;
}
