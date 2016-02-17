//
//  Name.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 17/02/16.
//
//

#include "Name.hpp"

//========================================================================
Name::Name (char c) : Signal(c)
{
    typeColor = ofColor(131, 192, 87);
}

//========================================================================
void Name::keyPressed (int key)
{
    if ((key > 47 && key < 58) ||
        (key > 64 && key < 91) ||
        (key > 96 && key < 123))
        new Character(key);
}
