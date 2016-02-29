//
//  Character.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "Types.h"


//========================================================================
Character::Character (char c, MainFunction* mf)
{
    charType = CHARACTER;
    
    this->mf = mf;
    x = y = 0.0f;
    
    charString = c;
    animation  = 0.0f;

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
Character* Character::getEndChar()
{
    return this;
}

Character* Character::draw (float& x, float& y, bool vertical, bool selection)
{
    // Init character position
    if (this->x == 0.0f) this->x = x;
    if (this->y == 0.0f) this->y = y;
    
    
    // Update input position
    x += mf->charWidth;
    if (vertical) y += mf->charHeight;
    
    if (this == mf)
    {
        x = this->x;
        y = this->y;
    }
    
    if (mf->charSelected->charType != FUNCTION_BODY)
    {
        if (ofGetMousePressed() && mf->charSelected == this)
        {
            x = ofGetMouseX() - mf->charWidth  / 2;
            y = ofGetMouseY() - mf->charHeight / 2;
        }
        else if (ofGetMousePressed() && mf->charSelected->getEndChar()->right == this)
        {
            x = mf->charSelected->left->x + mf->charWidth;
            y = mf->charSelected->left->y;
        }
    }
    
    
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
    
    
    // Draw selection
    if (selection || mf->charSelected == this)
    {
        ofSetColor(COLOR_SELECTION);
        ofDrawRectangle(x, y, mf->charWidth * 2, mf->charHeight);
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

void Character::drawCursor()
{
    ofSetColor(255);
    ofDrawRectangle(this->x + mf->charWidth * 0.95f, this->y,
                    mf->charWidth * 0.1f, mf->charHeight);
}

//========================================================================
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

void Character::mouseReleased (float x, float y, int button)
{
    if (right != mf && button == OF_MOUSE_BUTTON_LEFT)
    {
        if (mf->charSelected != this &&
            (x >= this->x && x < this->x + mf->charWidth) &&
            (y >= this->y && y < this->y + mf->charHeight))
            moveSelectedChar(this);
        else
            right->mouseReleased(x, y, button);
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
        
        if (c->charType != CHARACTER)
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
        
        if (c->charType == FUNCTION)
            return (Function*)c;
        
        if (!dir) c = c->left;
        else      c = c->right;
    }
}

//========================================================================
Type* Character::getParentType()
{
    Character* c = this;
    
    while (true)
    {
        if (c == NULL)
            return NULL;
        
        if (c->charType != CHARACTER)
            return (Type*)c;
        
        c = c->left;
    }
}

string Character::getCharString()
{
    return charString;
}

//========================================================================
bool Character::removeSelectedChar (bool removeFunctionBodies)
{
    if (mf->charSelected == this || mf->charSelected == mf)
        return false;
        
    if (!removeFunctionBodies && mf->charSelected->charType == FUNCTION_BODY)
        return false;
    
    Character* c = mf->charSelected;
    
    c->left->right = c->right;
    c->right->left = c->left;
    
    mf->charSelected = c->left;
    
    switch (c->charType)
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

void Character::moveSelectedChar (Character* destination)
{
    if (mf->charSelected->getParentType() == mf ||
        mf->charSelected->charType == FUNCTION_BODY ||
        destination->getParentType() == mf ||
        (mf->charSelected->charType == CHARACTER &&
         destination->getCharString() == ")"))
        return;
    
    Character* begin = mf->charSelected;
    Character* end   = begin->getEndChar();
    
    begin->left->right = end->right;
    end->right->left   = begin->left;
    
    begin->left = destination;
    end->right  = destination->right;
    
    begin->left->right = begin;
    end->right->left   = end;
}
