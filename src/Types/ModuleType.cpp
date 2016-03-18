//
//  ModuleType.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 17/02/16.
//
//

#include "Syntax.h"


//========================================================================
ModuleType::ModuleType() : Type(CHAR_TYPE_MOD_ID)
{
    typeType = MODULE;
}

//========================================================================
sig* ModuleType::compile (Memory* memory, bool record)
{
    AudioModule* module = memory->getModule(getTypeString());
    
    if (module)
    {
        flash(COLOR_TYPE_MOD_ID);
        return module->getOutput();
    }
    else
    {
        flash(COLOR_ERROR);
        return NULL;
    }
}
