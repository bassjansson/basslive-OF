//
//  Number.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 17/02/16.
//
//

#include "Number.hpp"


//========================================================================
Number::Number() : Signal('#')
{
    typeColor = ofColor(120, 109, 196);
}

//========================================================================
void Number::keyPressed (int key)
{
    if (key == 46 || (key > 47 && key < 58))
        new Character(key);
}
