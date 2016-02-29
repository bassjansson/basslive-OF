//
//  ModuleType.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 17/02/16.
//
//

#include "Types.h"


//========================================================================
ModuleType::ModuleType (MainFunction* mf)
: Type(CHAR_TYPE_MOD_ID, mf)
{
    typeType = MODULE;
}

//========================================================================
void ModuleType::trigger()
{
    if (getTypeString() == "")
    {
        int id = mf->getNewModuleID();
        
        mf->charSelected = this;
        new Character('m', mf);
        new Character('o', mf);
        new Character('d', mf);
        new Character((id / 10) % 10 + 48, mf);
        new Character((id / 1 ) % 10 + 48, mf);
    }
    
    if (updateFunctionPointer())
        flash(COLOR_TYPE_MOD_ID);
}
