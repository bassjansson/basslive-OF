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
    charType = CHARACTER;
    x = y = 0.0f;
    
    charString = c;
    animation  = 0.0f;
    
    if (charSelected == NULL)
    {
        left         = this;
        right        = this;
        charSelected = this;
    }
    else
    {
        left  = charSelected;
        right = charSelected->right;
        
        left->right  = this;
        right->left  = this;
        charSelected = this;
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
    // Init character position
    if (this->x == 0.0f) this->x = x;
    if (this->y == 0.0f) this->y = y;
    
    
    // Update input position
    x += charWidth;
    if (v) y += charHeight;
    
    
    // Update character position
    float factor = 0.3f;
    this->x = (1.0f - factor) * this->x + factor * x;
    this->y = (1.0f - factor) * this->y + factor * y;
    
    
    // Draw character
    ofPushMatrix();
    
    float factor1 = powf(1.0f - animation, 4.0f);
    float factor2 = (1.0f - factor1);
    float factor3 = animation * animation * 0.3f + 0.7f;
    
    ofTranslate(this->x * factor2 + (this->x - 100) * factor1,
                this->y * factor2);
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
            ofDrawRectangle(this->x + charWidth * 0.95f, this->y,
                            charWidth * 0.1f, charHeight);
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

void Character::mousePressed (float x, float y, int button)
{
    if (charSelected != this && button == OF_MOUSE_BUTTON_LEFT)
    {
        if ((x >= this->x && x < this->x + charWidth) &&
            (y >= this->y && y < this->y + charHeight))
            charSelected = this;
        else
            right->mousePressed(x, y, button);
    }
}

void Character::keyPressed (int key)
{
    if (key > 47 && key < 58)
    {
        new Number();
    }
    else if ((key > 64 && key < 91) ||
             (key > 96 && key < 123))
    {
        new Identifier('$');
    }
}

//========================================================================
CharType Character::getCharType()
{
    return charType;
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
Character* Character::getCharacter (bool dir)
{
    if (!dir) return left;
    else      return right;
}

Type* Character::getType (bool dir)
{
    Character* c;
    if (!dir) c = left;
    else      c = right;
    
    while (true)
    {
        if (c == NULL)
            return NULL;
        
        if (c->getCharType() != CHARACTER)
            return (Type*)c;
        
        if (!dir) c = c->left;
        else      c = c->right;
    }
}

Function* Character::getFunction (bool dir)
{
    Character* c;
    if (!dir) c = left;
    else      c = right;
    
    while (true)
    {
        if (c == NULL)
            return NULL;
        
        if (c->getCharType() == FUNCTION)
            return (Function*)c;
        
        if (!dir) c = c->left;
        else      c = c->right;
    }
}

//========================================================================
bool Character::removeSelectedChar (bool b)
{
    if (!b)
        if (charSelected == this || charSelected->getCharType() == FUNCTION_BODY)
            return false;
    
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
    
    return true;
}
