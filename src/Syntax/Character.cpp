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

float Character::mouseX = 0.0f;
float Character::mouseY = 0.0f;

float Character::RMS = 0.0f;


//========================================================================
Character::Character (char c)
{
    charVector.push_back(this);
    
    begin = left = right = this;
    charType = CHAR;
    charString = c;
    
    x = y = 0.0f;
    xAnim = yAnim = 0.0f;
    
    animation = 0.0f;
    
    if (charSelected == NULL)
        charSelected = begin;
}

//========================================================================
void Character::add (Character* c, bool force)
{
    if (c != begin)
    {
        if (force || (c->charType != IDEN &&
                      c->charType != CLOSE &&
                      c->charType != MAIN &&
                      !(c->charType == CHAR && charType == CLOSE)))
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
    if (this->x == 0.0f) this->x = xAnim = x + charWidth;
    if (this->y == 0.0f) this->y = yAnim = y + charHeight * int(vertical);
    
    
    // Update input position
    if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT) &&
        charSelected->charType != CHAR &&
        (begin == charSelected || (begin == charSelected->end()->right && !floating)))
    {
        if (begin == charSelected)
        {
            x = mouseX - charWidth  * 0.5f;
            y = mouseY - charHeight * 0.5f;
        }
        else
        {
            x = charSelected->left->x + charWidth  * 3.0f;
            y = charSelected->left->y + charHeight * int(vertical);
        }
    }
    else
    {
        if (floating)
        {
            x = roundf(this->x / charWidth)  * charWidth;
            y = roundf(this->y / charHeight) * charHeight;
        }
        else
        {
            x += charWidth;
            y += charHeight * int(vertical);
        }
    }
    
    
    // Update character position
    this->x = x;
    this->y = y;
    
    
    // Draw character
    ofPushMatrix();
    
    float factor1 = powf(1.0f - animation, 4.0f);
    float factor2 = (1.0f - factor1);
    
    float scaling = 1.0f + ofGetHeight() / charHeight * factor1 * 0.4f;
    
    // TODO: change translate
    ofTranslate(xAnim * factor2, // + ofGetWidth()  * 0.5f * factor1,
                yAnim * factor2);// + ofGetHeight() * 0.5f * factor1);
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
        ofDrawRectangle(xAnim, yAnim, charWidth, charHeight);
    }
    
    if ((mouseX >= xAnim && mouseX < xAnim + charWidth) &&
        (mouseY >= yAnim && mouseY < yAnim + charHeight))
    {
        ofSetColor(COLOR_SELECTION * 2);
        ofDrawRectRounded(xAnim, yAnim, charWidth, charHeight, charWidth * 0.1f);
    }
    
    
    // Draw fractal
    //if (charType == FUNC || charType == MAIN)
    //    drawFractal();
    
    
    // Update character animation position
    float factor = 0.3f;
    xAnim = (1.0f - factor) * xAnim + factor * this->x;
    yAnim = (1.0f - factor) * yAnim + factor * this->y;
    
    
    // Update animation
    if (animation >= 1.0f)
        animation  = 1.0f;
    else
        animation += 0.047f;
    
    
    // Shake characters when a key is pressed
    if (RMS > 0.075f) // CHANGE THIS WHEN NEEDED
    {
        float factor = 0.04f;
        xAnim += ofRandom(-charWidth * factor, charWidth * factor);
        yAnim -= ofRandom(0.0f, charHeight * factor);
        
        animation *= 0.93f;
    }
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
        //ofSetLineWidth(5.0f);
        ofDrawLine(counterX,  counterY,
                   counterCX, counterCY);
    }
}

void Character::drawCursor (float size)
{
    ofSetColor(250, 75 + 175 * size, 75);
    ofDrawRectRounded(xAnim + charWidth * 0.5f + charWidth * size * 0.44f,
                      yAnim + charHeight,
                      charWidth * (1.0f - size * 0.88f),
                      -charHeight * size,
                      charWidth * (1.0f - size));
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
