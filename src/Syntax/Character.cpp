//
//  Character.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "Syntax.h"


ofTrueTypeFont Character::charFont;
float          Character::charWidth  = 0.0f;
float          Character::charHeight = 0.0f;
CharVector     Character::charVector;
Character*     Character::charSelected;


//========================================================================
Character::Character (char c)
{
    charVector.push_back(this);
    
    begin = left = right = this;
    charType = CHAR;
    charString = c;
    
    x = y = 0.0f;
    
    animation = 0.0f;
    
    if (charSelected == NULL)
        charSelected = begin;
}

//========================================================================
void Character::add (Character* c, bool force)
{
    if (force || (c->charType != IDEN  &&
                  c->charType != CLOSE &&
                  c->charType != MAIN))
    {
        // Get destination
        Character* destination = begin;
        
        if (c->charType != CHAR &&
            c->charType != IDEN &&
            c->charType != CLOSE)
        {
            Type* parent = getParentType();
            
            if (parent->charType == MAIN)
                destination = parent->end()->left;
            else
                destination = parent->end();
        }
        
        
        // Move c to destination
        if (c != destination)
        {
            // Get end of c
            Character* c__end = c->end();
            
            
            // Attach old neighbours
            c->begin->left->right = c__end->right;
            c__end->right->left   = c->begin->left;
            
            
            // Set new left and right
            c->begin->left = destination->begin;
            c__end->right  = destination->right;
            
            
            // Update new neighbours
            c->begin->left->right = c->begin;
            c__end->right->left   = c__end;
            
            
            // Select c
            charSelected = c;
        }
    }
}

void Character::remove (bool force)
{
    if (force || (charType != IDEN  &&
                  charType != CLOSE &&
                  charType != MAIN))
    {
        // Get end
        Character* c_end = end();
        
        
        // Attach old neighbours
        begin->left->right = c_end->right;
        c_end->right->left = begin->left;
        
        
        // Select left char
        charSelected = begin->left;
        
        
        // Delete from end to begin
        Character* c = c_end;
        while (c != begin)
        {
            c = c->left;
            delete c->right;
        }
        
        
        // Delete this character
        if (charType != MAIN)
            delete begin;
    }
}

//========================================================================
void Character::draw (float& x, float& y, bool vertical, bool selection, bool floating)
{
    // Init character position
    if (this->x == 0.0f) this->x = x + charWidth;
    if (this->y == 0.0f) this->y = y + charHeight;
    
    
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
    
    if (ofGetMousePressed())
    {
        if (charSelected == begin)
        {
            x = ofGetMouseX() - charWidth  / 2;
            y = ofGetMouseY() - charHeight / 2;
        }
        else if (!floating && charSelected->end()->right == begin)
        {
            x = charSelected->left->x + charWidth * 2;
            y = charSelected->left->y;
        }
    }
    
    
    // Draw character
    ofPushMatrix();
    
    float factor1 = powf(1.0f - animation, 4.0f);
    float factor2 = (1.0f - factor1);
    float factor3 = animation * animation * 0.3f + 0.7f;
    
    if (charType != CHAR) factor3 *= 1.1f;
    
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
    
    
    // Draw fractal
    //drawFractal(charString.c_str()[0] % 64 / 64.0f * TWO_PI,
    //            this->x + charWidth / 2.0f, this->y + charHeight / 2.0f, 200.0f);
    
    
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

//void Character::drawFractal (float alpha, float x, float y, float length)
//{
//    if (right->charType != MAIN && length > 10.0f)
//    {
//        alpha += charString.c_str()[0] % 64 / 64.0f * TWO_PI;
//        
//        float newX = x + cosf(alpha) * length;
//        float newY = y - sinf(alpha) * length;
//        
//        ofColor c = getParentType()->typeColor;
//        float factor = powf(1.0f - length * 0.005f, 1.0f);
//        ofSetColor(c.r * factor, c.g * factor, c.b, factor * 127);
//        ofSetLineWidth(1.0f);
//        ofDrawLine(x, y, newX, newY);
//        
//        newX += cosf(alpha) * 1.0f;
//        newY -= sinf(alpha) * 1.0f;
//        
//        length *= 0.9f; //sqrtf(powf(x - this->x, 2.0f) + powf(y - this->y, 2.0f));
//        
//        right->drawFractal(alpha, newX, newY, length);
//    }
//}

void Character::drawCursor()
{
    ofSetColor(255);
    ofDrawRectangle(this->x + charWidth * 0.95f, this->y,
                    charWidth * 0.1f, charHeight);
}

Character* Character::end()
{
    return begin;
}

//========================================================================
Type* Character::getParentType()
{
    Character* c;
    
    for (c = begin; c->charType == CHAR; c = c->left);
    
    return (Type*)c;
}

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
