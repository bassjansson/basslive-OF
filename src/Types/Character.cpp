//
//  Character.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "Character.hpp"
#include "Function.hpp"


ofTrueTypeFont Character::charFont;
float          Character::charWidth = 0.0f;
float          Character::charHeight = 0.0f;
Character*     Character::charSelected = NULL;
int            Character::charCursorTime = 0;


//========================================================================
Character::Character (char c)
{
    charType   = CHARACTER;
    charString = c;
    animation  = 0.0f;
    
    if (charSelected == NULL)
    {
        left         = this;
        right        = this;
        charSelected = this;
        noneType     = false;
    }
    else
    {
        left  = charSelected;
        right = charSelected->right;
        
        left->right  = this;
        right->left  = this;
        charSelected = this;
        noneType     = left->noneType;
    }
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
//========================================================================
Character* Character::draw (float& x, float& y, bool v)
{
    // Update position
    x += charWidth;
    if (v) y += charHeight;
    
    
    // Draw char
    ofPushMatrix();
    
    float factor1 = powf(1.0f - animation, 4.0f);
    float factor2 = (1.0f - factor1);
    float factor3 = animation * animation * 0.3f + 0.7f;
    
    ofTranslate(x * factor2 + (x - 100) * factor1,
                y * factor2);
    ofTranslate(charWidth * 0.5f, charHeight * 0.5f);
    ofRotate(factor1 * factor1 * -45.0f);
    ofScale(factor3, factor3);
    charFont.drawString(charString, -charWidth * 0.5f,
                        charHeight * 0.5f + charFont.getDescenderHeight());
    
    ofPopMatrix();
    
    
    // Update animation
    if (animation >= 1.0f)
        animation  = 1.0f;
    else
        animation += 0.08f;
    
    
    // Draw cursor
    if (charSelected == this)
    {
        if (charCursorTime < FRAME_RATE / 2)
        {
            ofSetColor(255);
            ofDrawRectangle(x + charWidth * 0.95f, y, charWidth * 0.1f, charHeight);
        }
        
        charCursorTime = (charCursorTime + 1) % FRAME_RATE;
    }
    
    
    // Return next character
    return right;
}

/*
 // Ronddraaiende letters:
 
 ofTranslate(x + charWidth * 0.5f, y + charHeight * 0.5f);
 ofRotate(animation * animation * animation * 360.0f);
 ofScale(animation, animation);
 ofSetColor(255, 255, 255, 255 * animation);
 charFont.drawString(charString, -charWidth * 0.5f,
                     charHeight * 0.5f + charFont.getDescenderHeight());
 */

//========================================================================
Character* Character::getNextChar()
{
    return right;
}

CharType Character::getCharType()
{
    return charType;
}

bool Character::getNoneType()
{
    return noneType;
}

Type* Character::getParentType()
{
    Character* c = this;
    
    while (true)
    {
        if (c == NULL)
            return NULL;
        
        if (c->getCharType() != CHARACTER)
            return (Type*)c;
        
        c = c->left;
    }
}

//========================================================================
void Character::removeSelectedChar (bool b)
{
    if (!b)
        if (charSelected == this || charSelected->getCharType() == FUNCTION_BODY)
            return;
    
    Character* c = charSelected;
    
    c->left->right = c->right;
    c->right->left = c->left;
    
    charSelected = c->left;
    
    switch (c->getCharType())
    {
        case CHARACTER:
            delete c;
            break;
            
        case TYPE:
        case FUNCTION_BODY:
            delete (Type*)c;
            break;
            
        case FUNCTION:
            delete (Function*)c;
            break;
    }
}

void Character::moveLeft()
{
    charSelected = charSelected->left;
}

void Character::moveRight()
{
    charSelected = charSelected->right;
}
