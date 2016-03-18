//
//  Type.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "Syntax.h"


//========================================================================
Type::Type (char c) : Character(c)
{
    charType = TYPE;
    typeType = CLOSE;
    
    typeString = "";
    typeColor  = COLOR_DEFAULT;
    flashFloat = 0.0f;
}

//========================================================================
void Type::draw (float& x, float& y, bool vertical, bool selection, bool floating)
{
    // Draw type character
    selection = selection || charSelected == this;
    
    if (charType == TYPE ||
        charType == MAIN ||
        getRightChar()->charType == MAIN)
        ofSetColor(typeColor);
    else
        ofSetColor(COLOR_DEFAULT);
    
    Character::draw(x, y, vertical, selection, floating);
    
    
    // Draw type string
    string str = "";
    
    for (Character* c = getRightChar();
         c->charType == CHAR;
         c = c->getRightChar())
    {
        ofSetColor(typeColor);
        c->draw(x, y, HORIZONTAL, selection, false);
        
        str += c->getCharString();
    }
    
    
    // Draw type flash
    if (flashFloat > 0.001f)
    {
        ofSetColor(typeColor.r, typeColor.g, typeColor.b, flashFloat * 191);
        ofDrawRectangle(this->x, this->y, x - this->x + charWidth, charHeight);
        
        flashFloat *= 0.95f;
    }
    
    
    // Default color if string is changed
    if (str != typeString && charType != MAIN)
        typeColor = COLOR_DEFAULT;
    
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
    if (typeType != CLOSE)
    {
        if (key > 47 && key < 58)
        {
            if (charSelected != this)
                charSelected->add(new Character(key));
        }
        else if ((key > 64 && key < 91) ||
                 (key > 96 && key < 123) ||
                 key == '+' || key == '-' ||
                 key == '*' || key == '/')
        {
            charSelected->add(new Character(key));
        }
    }
}

sig* Type::compile (Memory* memory, bool record)
{
    flash(COLOR_DEFAULT);
    
    return NULL;
}

//========================================================================
void Type::setTypeString (const string& str)
{
    typeString = str;
}

string& Type::getTypeString()
{
    return typeString;
}
