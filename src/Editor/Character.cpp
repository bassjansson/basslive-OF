//
//  Character.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "MainFunction.hpp"


//========================================================================
Character::Character (char c, MainFunction* mf)
{
    this->mf = mf;
    charType = CHARACTER;
    
    charString = c;
    animation  = 0.0f;
    x = y      = 0.0f;

    if (this == mf)
    {
        left  = this;
        right = this;
    }
    else
    {
        left  = mf->charSelected;
        right = mf->charSelected->right;
        
        left->right = this;
        right->left = this;
    }
    
    mf->charSelected = this;
}

//========================================================================
Character* Character::draw (float& x, float& y, bool vertical)
{
    // Init character position
    if (this->x == 0.0f) this->x = x;
    if (this->y == 0.0f) this->y = y;
    
    
    // Update input position
    x += mf->charWidth;
    if (vertical) y += mf->charHeight;
    
    
    // Draw character
    ofPushMatrix();
    
    float factor1 = powf(1.0f - animation, 4.0f);
    float factor2 = (1.0f - factor1);
    float factor3 = animation * animation * 0.3f + 0.7f;
    
    ofTranslate(this->x * factor2 + (this->x - 100) * factor1,
                this->y * factor2);
    ofTranslate(mf->charWidth * 0.5f, mf->charHeight * 0.5f);
    ofRotate(factor1 * factor1 * -45.0f);
    ofScale(factor3, factor3);
    mf->charFont.drawString(charString, -mf->charWidth * 0.5f,
                            mf->charHeight * 0.5f + mf->charFont.getDescenderHeight());
    
    ofPopMatrix();
    
    
    // Update animation
    if (animation >= 1.0f)
        animation  = 1.0f;
    else
        animation += 0.08f;
    
    
    // Update character position
    float factor = 0.3f;
    this->x = (1.0f - factor) * this->x + factor * x;
    this->y = (1.0f - factor) * this->y + factor * y;
    
    
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
    if (right != mf && button == OF_MOUSE_BUTTON_LEFT)
    {
        if ((x >= this->x && x < this->x + mf->charWidth) &&
            (y >= this->y && y < this->y + mf->charHeight))
            mf->charSelected = this;
        else
            right->mousePressed(x, y, button);
    }
}

void Character::drawCursor()
{
    ofSetColor(255);
    ofDrawRectangle(this->x + mf->charWidth * 0.95f, this->y,
                    mf->charWidth * 0.1f, mf->charHeight);
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
bool Character::removeSelectedChar (bool removeFunctionBodies)
{
    if (mf->charSelected == this || mf->charSelected == mf)
        return false;
        
    if (!removeFunctionBodies && mf->charSelected->getCharType() == FUNCTION_BODY)
        return false;
    
    Character* c = mf->charSelected;
    
    c->left->right = c->right;
    c->right->left = c->left;
    
    mf->charSelected = c->left;
    
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
