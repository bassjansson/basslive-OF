//
//  Test.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 13/01/16.
//
//

#include "Test.h"


ofTrueTypeFont Character::charFont;
float          Character::charWidth  = 0.0f;
float          Character::charHeight = 0.0f;


//========================================================================
Character::Character()
{
    charString = "";
    size = 0.0f;
    time = 0;
}

Character::Character (char c)
{
    charString = c;
    size = 0.0f;
    time = 0;
}

//========================================================================
float Character::getWidth()
{
    return charWidth;
}

float Character::getHeight()
{
    return charHeight;
}

//========================================================================
bool Character::loadFont (const string& fileName, int fontSize)
{
    if (charFont.load(fileName, fontSize))
    {
        charWidth  = charFont.stringWidth("X");
        charHeight = charFont.stringHeight("Xgj{|");
        
        return true;
    }
    
    return false;
}

void Character::setChar (char c)
{
    charString = c;
    size = 0.0f;
}

void Character::resetTime()
{
    time = 0;
}

void Character::draw (float x, float y, bool cursor)
{
    ofPushMatrix();
    ofTranslate(x + charWidth * 0.5f, y + charHeight * 0.5f);
    ofRotate(size * size * size * 360.0f);
    ofScale(size, size);
    ofSetColor(255, 255, 255, 255 * size);
    charFont.drawString(charString, -charWidth * 0.5f,
                        charHeight * 0.5f + charFont.getDescenderHeight());
    ofPopMatrix();
    
    if (cursor && time < 15)
    {
        ofSetColor(255);
        ofDrawRectangle(x, y, charWidth * 0.05f, charHeight);
    }
    
    size = size * 0.8f + 0.2f;
    time = (time + 1) % 30;
}


//========================================================================
String::String()
{
    charVector.push_back(Character());
    position = charVector.begin();
}

//========================================================================
void String::keyPressed (int key)
{
    position->resetTime();
    
    if (key > 31 && key < 127)
    {
        position = charVector.insert(position, Character(key));
        position++;
    }
    else
    {
        switch (key)
        {
            case OF_KEY_LEFT:
                position--;
                break;
                
            case OF_KEY_RIGHT:
                position++;
                break;
                
            case OF_KEY_BACKSPACE:
                position--;
                position = charVector.erase(position);
                break;
                
            default:
                break;
        }
    }
}

void String::draw (float x, float y)
{
    for (vector<Character>::iterator i = charVector.begin(); i < charVector.end(); i++)
    {
        i->draw(x, y, i == position);
        x += i->getWidth();
    }
}
