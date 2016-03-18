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
    identifier->charType = BODY;
    add(identifier);
}

//========================================================================
sig* BufferFunction::compile (Memory* memory, bool record)
{
    // Fill strings if empty
    if (getTypeString() == "")
    {
                      add(new Character('b'));
        charSelected->add(new Character('u'));
        charSelected->add(new Character('f'));
        setTypeString("buf");
    }
    
    if (identifier->getTypeString() == "")
    {
        string str = "b" + ofToString(memory->getNewID());
        
        for (int i = 0; i < strlen(str.c_str()); i++)
            identifier->getEndChar()->add(new Character(str.c_str()[i]));
        
        identifier->setTypeString(str);
    }
    
    
    // Get or add module
    AudioBuffer* buffer = memory->getBuffer(identifier->getTypeString());
    
    if (buffer == NULL)
        buffer = memory->addBuffer(getTypeString(), identifier->getTypeString());
    
    
    // Set inputs of module
    NumberType* size = NULL;
    
    if (buffer)
    {
        int channel = 0;
        
        for (Type* t = identifier->getType(RIGHT);
             t != close;
             t = t->getEndChar()->getType(RIGHT))
        {
            if (size == NULL && t->typeType == NUMBER)
            {
                size = (NumberType*)t;
            }
            else
            {
                buffer->setInput(t->compile(memory, record), channel);
                channel++;
            }
        }
        
        if (size == NULL)
        {
            identifier->getEndChar()->add(size = new NumberType());
            charSelected->add(new Character('4'));
            charSelected->add(new Character('.'));
            charSelected->add(new Character('0'));
            size->setTypeString("4.0");
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
