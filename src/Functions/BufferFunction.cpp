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
    
    recordFlashTime = 0;
    recordFlashBeat = FRAME_RATE / 2.0f;
}

//========================================================================
void BufferFunction::drawTypeAnimation()
{
    if (buffer && buffer->recording == ON)
    {
        float alpha = 1.0f - fmodf(recordFlashTime, recordFlashBeat) / recordFlashBeat;
        
        ofSetColor(COLOR_RECORD.r,
                   COLOR_RECORD.g,
                   COLOR_RECORD.b, alpha * 191);
        
        ofDrawRectangle(x, y, end()->x + charWidth  - x,
                              end()->y + charHeight - y);
        
        recordFlashTime++;
    }
}

//========================================================================
sig* BufferFunction::compile (Memory* memory, bool record)
{
    // Get record flash interval
    float beatLength = memory->getClock().beatLength[0];
    recordFlashBeat  = FRAME_RATE * beatLength / SAMPLERATE;
    
    
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
        {
            buffer->record(tick(size->getValue() * memory->getClock().beatLength[0]));
            recordFlashTime = 0;
        }
        
        flash(COLOR_FUNC_BUFFER);
        return identifier->compile(memory, record);
    }
    else
    {
        flash(COLOR_ERROR);
        return NULL;
    }
}
