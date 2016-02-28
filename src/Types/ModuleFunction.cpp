//
//  ModuleFunction.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 28/02/16.
//
//

#include "ModuleFunction.hpp"


//========================================================================
ModuleFunction::ModuleFunction (MainFunction* mf)
: Function(CHAR_FUNC_MOD_OPEN,
           CHAR_TYPE_MOD_ID,
           CHAR_FUNC_MOD_CLOSE, mf)
{
    typeType = MODULE;
    module   = NULL;
}

//========================================================================
void ModuleFunction::trigger()
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

//========================================================================
Type* ModuleFunction::process (buf& buffer, sig& output, Clock& clock)
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
