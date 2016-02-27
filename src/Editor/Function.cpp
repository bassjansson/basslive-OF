//
//  Function.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#include "MainFunction.hpp"


//========================================================================
Function::Function (MainFunction* mf) : Type(CHAR_FUNC_OPEN, mf)
{
    charType  = FUNCTION;
    
    identifier = new Identifier(CHAR_FUNC_IDEN, mf);
    close      = new Type(CHAR_FUNC_CLOSE, mf);
    mf->charSelected = this;
    
    module = NULL;
    clock  = -1;
    am_id  = "";
}

Function::~Function()
{
    mf->charSelected = identifier;
    removeSelectedChar(true);
    
    mf->charSelected = close;
    removeSelectedChar(true);
}

//========================================================================
Character* Function::getEndChar()
{
    return close;
}

Character* Function::draw (float& x, float& y, bool vertical)
{
    // Draw function type
    Character* c = Type::draw(x, y, vertical);
    float indent = x;
    
    // Draw function arguments
    for (int i = 0; true; i++)
    {
        if (c == NULL)
            return NULL;
        
        if (c == close)
        {
            x -= mf->charWidth;
            return c->draw(x, y, HORIZONTAL);
        }
        
        if (c == identifier)
        {
            x -= mf->charWidth;
            c = c->draw(x, y, HORIZONTAL);
            indent = x;
        }
        else
        {
            if ((i > 1) &&
                (c->getCharType() == FUNCTION ||
                 c->getCharacter(LEFT)->getCharType() == FUNCTION_BODY))
            {
                x = indent;
                c = c->draw(x, y, VERTICAL);
            }
            else
            {
                c = c->draw(x, y, HORIZONTAL);
            }
        }
    }
}

Type* Function::process (sig& output, Clock& clock)
{
    output = typeSignal;
    
    if (this->clock != clock.clock)
    {
        this->clock = clock.clock;
        
        if (module)
        {
            Type* t = identifier->getType(RIGHT);
            inputs.clear();
            
            while (true)
            {
                if (t == NULL || t == close)
                    break;
                
                sig s;
                t = t->process(s, clock);
                inputs.push_back(s);
            }
            
            module->process(inputs, output, clock);
        }
        else
        {
            for (tick t = 0; t < BUFFERSIZE; t++)
                output[t] = 0.0f;
        }
    }
    
    return close->getType(RIGHT);
}

void Function::keyPressed (int key)
{
    if (key > 47 && key < 58)
    {
        if (mf->charSelected != this)
        {
            typeColor = ofColor(255);
            new Character(key, mf);
        }
    }
    else if ((key > 64 && key < 91) ||
             (key > 96 && key < 123))
    {
        typeColor = ofColor(255);
        new Character(key, mf);
    }
}

void Function::trigger()
{
    if (am_id != typeString)
    {
        am_id = typeString;
        
        if (module) delete module;
        
        module = mf->getNewModuleWithID(am_id);
        
        if (module) typeColor = ofColor(0, 160, 190);
    }
    
    Type* t = identifier;
    
    while (true)
    {
        if (t == NULL || t == close)
            break;
        
        t->trigger();
        t = t->getType(RIGHT);
    }
}
