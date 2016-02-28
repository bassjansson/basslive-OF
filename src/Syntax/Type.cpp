//
//  Type.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "Types.h"


//========================================================================
Type::Type (char c, MainFunction* mf)
: Character(c, mf)
{
    charType = TYPE;
    typeType = FUNC_CLOSE;
    
    typeClock  = -1;
    typeSignal = new sample[BUFFERSIZE];
    for (tick t = 0; t < BUFFERSIZE; t++)
        typeSignal[t] = 0.0f;
    
    funcPointer = NULL;
    
    typeString = "";
    typeColor  = ofColor(255);
    flashFloat = 0.0f;
}

Type::~Type()
{
    Character* c = getCharacter(RIGHT);
    
    while (true)
    {
        if (c == NULL)
            break;
        
        if (c->charType != CHARACTER)
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
    ofSetColor(255);
    Character* c = Character::draw(x, y, vertical);
    
    
    // Draw type string
    string str = "";
    while (true)
    {
        if (c == NULL)
            return NULL;
        
        if (c->charType != CHARACTER)
        {
            x += mf->charWidth;
            return c;
        }
        
        ofSetColor(typeColor);
        str += c->getCharString();
        c = c->draw(x, y, HORIZONTAL);
    }
    
    
    // Draw type flash
    ofSetColor(typeColor.r, typeColor.g, typeColor.b, flashFloat * 127);
    ofDrawRectangle(this->x, this->y, x - this->x, mf->charHeight);
    flashFloat *= 0.5f;
    
    
    // Default color if string is changed
    if (str != typeString)
        typeColor = ofColor(255);
    typeString = str;
}

void Type::flash (const ofColor& color)
{
    typeColor  = color;
    flashFloat = 1.0f;
}

//========================================================================
void Type::keyPressed (int key)
{
    if (typeType != FUNC_CLOSE)
    {
        if (key > 47 && key < 58)
        {
            if (mf->charSelected != this)
                new Character(key, mf);
        }
        else if ((key > 64 && key < 91) ||
                 (key > 96 && key < 123))
        {
            new Character(key, mf);
        }
    }
}

//========================================================================
Type* Type::process (buf& buffer, sig& output, Clock& clock)
{
    output = typeSignal;
    
    if (funcPointer) funcPointer->process(buffer, output, clock);
    
    return getType(RIGHT);
}

//========================================================================
string Type::getTypeString()
{
    return typeString;
}
