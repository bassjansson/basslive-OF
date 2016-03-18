//
//  ModuleFunction.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 28/02/16.
//
//

#include "Syntax.h"


//========================================================================
ModuleFunction::ModuleFunction() : Function(CHAR_FUNC_MOD_OPEN,
                                            CHAR_FUNC_MOD_CLOSE)
{
    typeType = MODULE;
    
    identifier = new ModuleType();
    identifier->charType = BODY;
    add(identifier);
}

//========================================================================
sig* ModuleFunction::compile (Memory* memory, bool record)
{
    // Fill strings if empty
    if (getTypeString() == "")
    {
        add(new Character('*'));
        setTypeString("*");
    }
    
    if (identifier->getTypeString() == "")
    {
        string str = "m" + ofToString(memory->getNewID());
        
        for (int i = 0; i < strlen(str.c_str()); i++)
            identifier->getEndChar()->add(new Character(str.c_str()[i]));
        
        identifier->setTypeString(str);
    }
    
    
    // Get or add module
    AudioModule* module = memory->getModule(identifier->getTypeString());
    
    if (module == NULL)
        module = memory->addModule(getTypeString(), identifier->getTypeString());
    
    
    // Set inputs of module
    if (module)
    {
        int channel = 0;
        
        for (Type* t = identifier->getType(RIGHT);
             t != close;
             t = t->getEndChar()->getType(RIGHT))
        {
            module->setInput(t->compile(memory, record), channel);
            channel++;
        }
        
        flash(COLOR_FUNC_MODULE);
        return identifier->compile(memory, record);
    }
    else
    {
        flash(COLOR_ERROR);
        return NULL;
    }
}
