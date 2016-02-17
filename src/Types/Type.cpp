//
//  Type.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "Type.hpp"


//========================================================================
Type::Type (char c) : Character(c)
{
    if (c == ':' || c == ')')
        charType = FUNCTION_BODY;
    else
        charType = TYPE;
    
    noneType = false;
    
    typeColor = ofColor(255);
}

Type::~Type()
{
    Character* c = getNextChar();
    
    while (true)
    {
        if (c == NULL)
            break;
        
        if (c->getCharType() != CHARACTER)
            break;

        charSelected = c;
        c = c->getNextChar();
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
            return c;
        
        ofSetColor(typeColor);
        c = c->draw(x, y, HORIZONTAL);
    }
}

void Type::keyPressed (int key)
{
    
}
