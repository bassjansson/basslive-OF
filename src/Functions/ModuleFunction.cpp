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
    identifier->charType = IDEN;
    add(identifier);
}

//========================================================================
sig* ModuleFunction::compile (Memory* memory, bool record)
{
    // Fill strings if empty
    if (typeString == "")
    {
        add(new Character('*'));
        typeString = "*";
    }
    
    if (identifier->typeString == "")
    {
        string str = "m" + ofToString(memory->getNewID());
        
        charSelected = identifier;
        
        for (int i = 0; i < strlen(str.c_str()); i++)
            charSelected->add(new Character(str.c_str()[i]));
        
        identifier->typeString = str;
    }
    
    
    // Get or add module
    AudioModule* module = memory->getModule(identifier->typeString);
    
    if (module == NULL)
        module = memory->addModule(typeString, identifier->typeString);
    
    
    // Set inputs of module
    if (module)
    {
        int channel = 0;
        
        for (Character* c = identifier->getType(RIGHT);
             c != end();
             c = c->end()->right)
        {
            Type* t = (Type*)c;
            
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
