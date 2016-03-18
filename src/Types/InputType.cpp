//
//  InputType.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 29/02/16.
//
//

#include "Syntax.h"


//========================================================================
InputType::InputType() : Type(CHAR_TYPE_INPUT)
{
    typeType = INPUT;
}

//========================================================================
void InputType::keyPressed (int key)
{
    if (key > 47 && key < 58)
        charSelected->add(new Character(key));
}

sig* InputType::compile (Memory* memory, bool record)
{
    if (getTypeString() == "")
    {
        add(new Character('0'));
        setTypeString("0");
    }
    
    char* err;
    int channel = strtof(getTypeString().c_str(), &err);
    
    if (*err == 0)
    {
        flash(COLOR_TYPE_INPUT);
        return memory->getADC(channel);
    }
    else
    {
        flash(COLOR_ERROR);
        return NULL;
    }
}
