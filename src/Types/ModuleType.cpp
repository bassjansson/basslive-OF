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
        int  id  = mf->getNewModuleID();
        char id1 = (id / 10) % 10 + 48;
        char id2 = (id / 1 ) % 10 + 48;
        
        mf->charSelected = this;
        new Character('m', mf);
        new Character('o', mf);
        new Character('d', mf);
        new Character(id1, mf);
        new Character(id2, mf);
        
        string str = "mod";
        str += id1;
        str += id2;
        setTypeString(str);
    }
    
    if (updateFunctionPointer())
        flash(COLOR_TYPE_MOD_ID);
}
