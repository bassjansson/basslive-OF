//
//  BufferFunction.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 28/02/16.
//
//

#include "Syntax.h"


//========================================================================
BufferFunction::BufferFunction() : Function(CHAR_FUNC_BUF_OPEN,
                                            CHAR_FUNC_BUF_CLOSE)
{
    typeType = BUFFER;
    
    identifier = new BufferType();
    identifier->charType = IDEN;
    add(identifier);
    
    buffer = NULL;
}

//========================================================================
void BufferFunction::drawTypeAnimation()
{
    // Draw function beat flash
    if (buffer && buffer->getBeatTime() >= 0.0f)
    {
        ofSetColor(typeColor.r, typeColor.g, typeColor.b,
                   (1.0f - buffer->getBeatTime()) * 191);
        
        ofDrawRectangle(x, y,
                        end()->x - x + charWidth,
                        end()->y - y + charHeight);
    }
    
    
    // Draw function feedback line
    float beatTime = 0.0f;
    
    if (buffer)
    {
        beatTime = buffer->getBeatTime();
        if (beatTime < 0.0f) beatTime = 0.0f;
    }
    
    float alpha  = sqrtf(1.0f - beatTime);
    float width  = identifier->end()->x - x + 1.5f * charWidth;
    float height = end()->y - y;
    
    ofSetColor(typeColor.r, typeColor.g, typeColor.b, alpha * 255);
    ofDrawRectangle(x + 0.5f * charWidth, y + charHeight,
                    width * beatTime + 1.0f, height);
}

//========================================================================
sig* BufferFunction::compile (Memory* memory, bool record)
{
    // Fill strings if empty
    if (typeString == "")
    {
                      add(new Character('b'));
        charSelected->add(new Character('u'));
        charSelected->add(new Character('f'));
        typeString = "buf";
    }
    
    if (identifier->typeString == "")
    {
        string str = "b" + ofToString(memory->getNewID());
        
        charSelected = identifier;
        
        for (int i = 0; i < strlen(str.c_str()); i++)
            charSelected->add(new Character(str.c_str()[i]));
        
        identifier->typeString = str;
    }
    
    
    // Get or add buffer
    buffer = memory->getBuffer(identifier->typeString);
    
    if (buffer == NULL)
        buffer = memory->addBuffer(typeString, identifier->typeString);
    
    
    // Set inputs of buffer, get size and record
    if (buffer)
    {
        sig_vec inputs;
        NumberType* size = NULL;
        
        for (Character* c = identifier->getType(RIGHT);
             c != end();
             c = c->end()->right)
        {
            Type* t = (Type*)c;
            
            if (size == NULL && t->typeType == NUMBER)
                size = (NumberType*)t;
            else
                inputs.push_back(t->compile(memory, record));
        }
        
        buffer->setInputs(inputs);
        inputs.clear();
        
        if (size == NULL)
        {
            identifier->end()->add(size = new NumberType());
            size->add(new Character('4'));
            size->typeString = "4";
        }
        
        size->compile(memory, record);
        
        if (record)
            buffer->record(tick(size->getValue() * memory->getClock().beatLength[0]));
        
        flash(COLOR_FUNC_BUFFER);
        return identifier->compile(memory, record);
    }
    else
    {
        flash(COLOR_ERROR);
        return NULL;
    }
}
