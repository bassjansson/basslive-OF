//
//  Type.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "MainFunction.hpp"


//========================================================================
Type::Type (char c, MainFunction* mf) : Character(c, mf)
{
    if (c == CHAR_FUNC_IDEN || c == CHAR_FUNC_CLOSE)
        charType = FUNCTION_BODY;
    else
        charType = TYPE;
    
    typeColor  = ofColor(255);
    typeString = "";
    typeSignal = new sample[BUFFERSIZE];
    
    for (tick t = 0; t < BUFFERSIZE; t++)
        typeSignal[t] = 0.0f;
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

        mf->charSelected = c;
        c = c->getCharacter(RIGHT);
        removeSelectedChar(false);
    }
    
    delete[] typeSignal;
}

//========================================================================
Character* Type::getEndChar()
{
    return getType(RIGHT)->getCharacter(LEFT);
}

Character* Type::draw (float& x, float& y, bool vertical)
{
    // Draw type character
    if (charType == FUNCTION || charType == FUNCTION_BODY)
        ofSetColor(255);
    else
        ofSetColor(typeColor);
    Character* c = Character::draw(x, y, vertical);
    
    // Draw type string
    typeString = "";
    while (true)
    {
        if (c == NULL)
            return NULL;
        
        if (c->getCharType() != CHARACTER)
        {
            x += mf->charWidth;
            return c;
        }
        
        ofSetColor(typeColor);
        typeString += c->getCharString();
        c = c->draw(x, y, HORIZONTAL);
    }
}

Type* Type::process (sig& output, Clock& clock)
{
    output = typeSignal;
    
    return getType(RIGHT);
}

void Type::keyPressed (int key)
{    
    if ((key > 47 && key < 58) || key == 46)
    {
        new Number(mf);
        new Character(key, mf);
    }
    else if ((key > 64 && key < 91) ||
             (key > 96 && key < 123))
    {
        new Identifier(mf);
        new Character(key, mf);
    }
}

//========================================================================
string Type::getTypeString()
{
    return typeString;
}
