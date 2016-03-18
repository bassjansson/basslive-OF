//
//  Character.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "Syntax.h"


ofTrueTypeFont Character::charFont;
float          Character::charWidth    = 0.0f;
float          Character::charHeight   = 0.0f;
Character*     Character::charSelected = NULL;


//========================================================================
Character::Character (char c)
{
    charType = CHAR;
    
    x = y = 0.0f;
    
    begin = end = left = right = this;
    
    charString = c;
    animation  = 0.0f;
    
    if (charSelected == NULL)
        charSelected = this;
}

//========================================================================
void Character::draw (float& x, float& y, bool vertical, bool selection, bool floating)
{
    // Init character position
    if (this->x == 0.0f) this->x = x + charWidth;
    if (this->y == 0.0f) this->y = y + charHeight * int(vertical);
    
    
    // Update input position
    if (floating)
    {
        x = this->x;
        y = this->y;
    }
    else
    {
        x += charWidth;
        y += charHeight * int(vertical);
    }
    
    if (ofGetMousePressed() && charSelected->charType != BODY)
    {
        if (charSelected == this)
        {
            x = ofGetMouseX() - charWidth  / 2;
            y = ofGetMouseY() - charHeight / 2;
        }
        else if (charSelected->end->right == this && !floating)
        {
            x = charSelected->left->x + charWidth;
            y = charSelected->left->y + charHeight * int(vertical);
        }
    }
    
    
    // Draw character
    ofPushMatrix();
    
    float factor1 = powf(1.0f - animation, 4.0f);
    float factor2 = (1.0f - factor1);
    float factor3 = animation * animation * 0.3f + 0.7f;
    
    if (charType == CHAR) factor3 *= 0.9f;
    
    ofTranslate(this->x * factor2 + ofGetWidth()  * 0.5f * factor1,
                this->y * factor2 + ofGetHeight() * 0.5f * factor1);
    ofTranslate(charWidth * 0.5f, charHeight * 0.5f);
    ofRotate(factor1 * factor1 * -45.0f);
    ofScale(factor3, factor3);
    charFont.drawString(charString,
                        -charWidth * 0.5f,
                        charHeight * 0.5f + charFont.getDescenderHeight());
    
    ofPopMatrix();
    
    
    // Draw selection
    if (selection)
    {
        ofSetColor(COLOR_SELECTION);
        ofDrawRectangle(this->x, this->y, charWidth, charHeight);
    }
    
    
    // Update animation
    if (animation >= 1.0f)
        animation  = 1.0f;
    else
        animation += 0.08f;
    
    
    // Update character position
    float factor = 0.3f;
    this->x = (1.0f - factor) * this->x + factor * x;
    this->y = (1.0f - factor) * this->y + factor * y;
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


void Character::drawCursor()
{
    ofSetColor(255);
    ofDrawRectangle(this->x + charWidth * 0.95f, this->y,
                    charWidth * 0.1f, charHeight);
}

//========================================================================
void Character::mousePressed (float x, float y, int button)
{
    if (button == OF_MOUSE_BUTTON_LEFT)
    {
        if ((x >= this->x &&
             x <  this->x + charWidth) &&
            (y >= this->y &&
             y <  this->y + charHeight))
        {
            charSelected = this;
        }
        else if (right->charType != MAIN)
        {
            right->mousePressed(x, y, button);
        }
    }
}

void Character::mouseReleased (float x, float y, int button)
{
    if (button == OF_MOUSE_BUTTON_LEFT)
    {
        if (charSelected != this &&
            charSelected->charType != MAIN &&
            (x >= this->x + charWidth * 0.5f &&
             x <  this->x + charWidth * 1.5f) &&
            (y >= this->y &&
             y <  this->y + charHeight))
        {
            add(charSelected);
        }
        else if (right->charType != MAIN)
        {
            right->mouseReleased(x, y, button);
        }
    }
}

//========================================================================
void Character::add (Character* c)
{
    // Get destination and update ends
    Character* destination;
    
    if (charType == CHAR)
    {
        Character* parent = getParentType();
        
        if (c->charType == CHAR)
        {
            if (parent->end == this)
                parent->end = c;
            
            destination = this;
        }
        else
        {
            if (parent->charType == MAIN)
                destination = parent->end->left;
            else
                destination = parent->end;
        }
    }
    else
    {
        if (c->charType == CHAR || c->charType == BODY)
        {
            if (end == this)
                end = c;
            
            destination = this;
        }
        else
        {
            if (charType == MAIN)
                destination = end->left;
            else
                destination = end;
        }
    }
    
    
    // Attach old neighbours
    c->begin->left->right = c->end->right;
    c->end->right->left   = c->begin->left;
    
    
    // Set new left and right
    c->begin->left = destination;
    c->end->right  = destination->right;
    
    
    // Update new neighbours
    c->begin->left->right = c->begin;
    c->end->right->left   = c->end;
    
    
    // Select new char
    charSelected = c;
}

void Character::remove (bool force)
{
    // Not removable
    if (!force && (charType == MAIN || charType == BODY))
        return;
    
    
    // Attach old neighbours
    begin->left->right = end->right;
    end->right->left   = begin->left;
    
    
    // Select left char
    charSelected = begin->left;
    
    
    // Delete from end to begin
    while (true)
    {
        if (end == begin)
            break;
        
        Character* c = end;
        end = end->left;
        delete c;
    }
    
    
    // Delete this
    if (charType != MAIN)
        delete this;
}

//========================================================================
Type* Character::getType (bool dir)
{
    Character* c;
    
    if (!dir)
        for (c = left; c->charType == CHAR; c = c->left);
    else
        for (c = right; c->charType == CHAR; c = c->right);
    
    return (Type*)c;
}

Function* Character::getFunction (bool dir)
{
    Character* c;
    
    if (!dir)
        for (c = left; c->charType != FUNC; c = c->left);
    else
        for (c = right; c->charType != FUNC; c = c->right);
    
    return (Function*)c;
}

//========================================================================
Character* Character::getEndChar()
{
    return end;
}

Character* Character::getLeftChar()
{
    return left;
}

Character* Character::getRightChar()
{
    return right;
}

Type* Character::getParentType()
{
    Character* c;
    
    for (c = this; c->charType == CHAR; c = c->left);
    
    return (Type*)c;
}

//========================================================================
string& Character::getCharString()
{
    return charString;
}
