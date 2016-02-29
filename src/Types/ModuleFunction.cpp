//
//  ModuleFunction.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 28/02/16.
//
//

#include "Types.h"


//========================================================================
bool ModuleFunction::updateAudioModule()
{
    if (module) delete module;
    
    if (module_id == "loop") return module = new loop_Module();
    if (module_id == "+"   ) return module = new add_Module();
    if (module_id == "-"   ) return module = new sub_Module();
    if (module_id == "*"   ) return module = new mul_Module();
    if (module_id == "/"   ) return module = new div_Module();
    
    return module;
}

//========================================================================
ModuleFunction::ModuleFunction (MainFunction* mf)
: Function(CHAR_FUNC_MOD_OPEN,
           CHAR_TYPE_MOD_ID,
           CHAR_FUNC_MOD_CLOSE, mf)
{
    typeType = MODULE;

    module    =  NULL;
    module_id = "NULL";
}

//========================================================================
void ModuleFunction::trigger()
{
    // Update module and id
    if (module_id != getTypeString())
    {
        if (getTypeString() == "")
        {
            mf->charSelected = this;
            new Character('*', mf);
        }
        
        module_id = getTypeString();
        
        if (updateAudioModule())
            flash(COLOR_FUNC_MODULE);
    }
    
    
    // Trigger children
    Type* t = identifier;
    
    while (true)
    {
        if (t == NULL)
            break;
        
        t->trigger();
        
        if (t == close)
            break;

        t = t->getType(RIGHT);
    }
}

//========================================================================
Type* ModuleFunction::process (buf& buffer, sig& output, Clock& clock)
{
    buffer = NULL;
    output = typeSignal;
    
    
    if (typeClock != clock.clock)
    {
        typeClock = clock.clock;
        
        if (module)
        {
            inputs.clear();
            buffers.clear();
            
            Type* t = identifier->getType(RIGHT);
            
            while (true)
            {
                if (t == NULL || t == close)
                    break;
                
                sig s;
                buf b;
                
                t = t->process(b, s, clock);
                
                if (s) inputs.push_back(s);
                if (b) buffers.push_back(b);
            }
            
            module->process(inputs, buffers, output, clock);
        }
        else
        {
            for (tick t = 0; t < BUFFERSIZE; t++)
                output[t] = 0.0f;
        }
    }
    
    
    return close->getType(RIGHT);
}
