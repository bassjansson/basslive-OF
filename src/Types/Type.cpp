//
//  Type.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "Type.hpp"
#include "Number.hpp"


//========================================================================
Type::Type (char c) : Character(c)
{
    if (c == ':' || c == ')')
        charType = FUNCTION_BODY;
    else
        charType = TYPE;
    
    typeColor = ofColor(255);
}

Type::~Type()
{
    Character* c = getCharacter(RIGHT);
    
    while (true)
    {
        if (c == NULL)
            break;
        
        if (c->getCharType() != CHARACTER)
            break;

        charSelected = c;
        c = c->getCharacter(RIGHT);
        removeSelectedChar(false);
    }
}

//========================================================================
Character* Type::draw (float& x, float& y, bool v)
{
    // Draw type character
    if (charType == FUNCTION || charType == FUNCTION_BODY)
        ofSetColor(255);
    else
        ofSetColor(typeColor);
    Character* c = Character::draw(x, y, v);
    
    // Draw type string
    while (true)
    {
        if (c == NULL)
            return NULL;
        
        if (c->getCharType() != CHARACTER)
        {
            x += charWidth;
            return c;
        }
        
        ofSetColor(typeColor);
        c = c->draw(x, y, HORIZONTAL);
    }
}
