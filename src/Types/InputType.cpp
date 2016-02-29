//
//  InputType.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 29/02/16.
//
//

#include "Types.h"


//========================================================================
InputType::InputType (MainFunction* mf)
: Type(CHAR_TYPE_INPUT, mf)
{
    typeType = INPUT;
    
    channel = -1;
}

//========================================================================
void InputType::keyPressed (int key)
{
    if (key > 47 && key < 58)
        new Character(key, mf);
}

void InputType::trigger()
{
    if (getTypeString() == "")
    {
        mf->charSelected = this;
        new Character('0', mf);
        
        setTypeString("0");
    }
    
    char* err;
    channel = strtof(getTypeString().c_str(), &err);
    
    if (*err == 0)
    {
        flash(COLOR_TYPE_INPUT);
    }
    else
    {
        flash(COLOR_ERROR);
        channel = -1;
    }
}

//========================================================================
Type* InputType::process (buf& buffer, sig& output, Clock& clock)
{
    buffer = NULL;
    output = mf->getADC(channel);
    
    if (output == NULL) output = typeSignal;
    
    return getType(RIGHT);
}
