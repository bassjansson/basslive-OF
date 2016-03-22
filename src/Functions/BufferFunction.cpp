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
    
    
    // Get or add module
    AudioBuffer* buffer = memory->getBuffer(identifier->typeString);
    
    if (buffer == NULL)
        buffer = memory->addBuffer(typeString, identifier->typeString);
    
    
    // Set inputs of module
    if (buffer)
    {
        int channel = 0;
        NumberType* size = NULL;
        
        for (Character* c = identifier->getType(RIGHT);
             c != end();
             c = c->end()->right)
        {
            Type* t = (Type*)c;
            
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
            identifier->end()->add(size = new NumberType());
            charSelected->add(new Character('4'));
            charSelected->add(new Character('.'));
            charSelected->add(new Character('0'));
            size->typeString = "4.0";
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
