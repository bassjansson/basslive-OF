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

float Character::RMS = 0.0f;


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
    if (c != begin)
    {
        if (force || (c->charType != IDEN  &&
                      c->charType != CLOSE &&
                      c->charType != MAIN  &&
                    !(c->charType == CHAR  && charType == CLOSE)))
        {
            // Get destination
            Character* destination = begin;
            
            if (c->charType == TYPE ||
                c->charType == FUNC)
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
    if (this->y == 0.0f) this->y = y + charHeight * int(vertical);
    
    
    // Update input position
    if (floating)
    {
        x = int((this->x + charWidth  * 0.5f) / charWidth)  * charWidth;
        y = int((this->y + charHeight * 0.5f) / charHeight) * charHeight;
    }
    else
    {
        x += charWidth;
        y += charHeight * int(vertical);
    }
    
    if (ofGetMousePressed() &&
        (begin == charSelected ||
         (begin == charSelected->end()->right && !floating)))
    {
        float mouseMovement = (abs(ofGetMouseX() - ofGetPreviousMouseX()) +
                               abs(ofGetMouseY() - ofGetPreviousMouseY()));
        
        if (mouseMovement > 0)
        {
            if (begin == charSelected)
            {
                x = ofGetMouseX() - charWidth  * 0.5f;
                y = ofGetMouseY() - charHeight * 0.5f;
            }
            else
            {
                x = charSelected->left->x;
                y = charSelected->left->y;
                
                x += charWidth  * 2.0f;
                y += charHeight * int(vertical);
            }
        }
    }
    
    
    // Draw character
    ofPushMatrix();
    
    float factor1 = powf(1.0f - animation, 4.0f);
    float factor2 = (1.0f - factor1);
    
    float scaling = 1.0f + ofGetHeight() / charHeight * factor1 * 0.33f;
    
    ofTranslate(this->x * factor2 + ofGetWidth()  * 0.5f * factor1,
                this->y * factor2 + ofGetHeight() * 0.5f * factor1);
    ofTranslate(charWidth * 0.5f, charHeight * 0.5f);
    ofRotate(factor1 * 180.0f);
    ofScale(scaling, scaling);
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
    
    float mouseX = ofGetMouseX();
    float mouseY = ofGetMouseY();
    
    if ((mouseX >= this->x && mouseX < this->x + charWidth) &&
        (mouseY >= this->y && mouseY < this->y + charHeight))
    {
        ofSetColor(COLOR_SELECTION * 2);
        ofDrawRectRounded(this->x, this->y, charWidth, charHeight, charWidth * 0.25f);
    }
    
    
    // Draw fractal
    if (charType == FUNC || charType == MAIN)
        drawFractal();
    
    
    // Update animation
    if (animation >= 1.0f)
        animation  = 1.0f;
    else
        animation += 0.047f;
    
    
    // Update character position
    float factor = 0.25f;
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

void Character::drawFractal()
{
    float alpha  = (charString.c_str()[0] % 64) / 64.0f * TWO_PI;
    float length = sqrtf(powf(x - ofGetWidth()  * 0.5f, 2.0f) +
                         powf(y - ofGetHeight() * 0.5f, 2.0f)) * (RMS * 5.0f + 0.5f);
    
    float counterX = cosf(alpha) * length + ofGetWidth()  * 0.5f;
    float counterY = sinf(alpha) * length + ofGetHeight() * 0.5f;
    
    ofColor color = getParentType()->typeColor;
    
    for (Character* c = begin; c->right->charType != MAIN; c = c->getType(RIGHT))
    {
        float counterCX = -c->x + ofGetWidth();
        float counterCY = -c->y + ofGetHeight();
        
        length = sqrtf(powf(counterCX - counterX, 2.0f) +
                       powf(counterCY - counterY, 2.0f)) / ofGetWidth();
        
        float factor = powf(1.0f - length, 4.0f);
        
        ofSetColor(color.r, color.g, color.b, 100 * factor);
        ofSetLineWidth(5.0f);
        ofDrawLine(counterX,  counterY,
                   counterCX, counterCY);
    }
}

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
