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
    if (typeString == "")
    {
        add(new Character('0'));
        typeString = "0";
    }
    
    char* err;
    sig* adc = memory->getADC(int(strtof(typeString.c_str(), &err)));
    
    if (!*err && adc)
    {
        flash(COLOR_TYPE_INPUT);
        return adc;
    }
    else
    {
        flash(COLOR_ERROR);
        return NULL;
    }
}
