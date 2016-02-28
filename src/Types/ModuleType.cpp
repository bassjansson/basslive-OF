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
    funcPointer = mf->getModuleFunction(getTypeString());
    
    if (funcPointer) flash(ofColor(121, 182, 77));
}
