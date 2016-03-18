//
//  ModuleType.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 17/02/16.
//
//

#ifndef ModuleType_hpp
#define ModuleType_hpp

#include "Type.hpp"


class ModuleType : public Type
{
public:
    //========================================================================
    ModuleType();

    //========================================================================
    virtual sig* compile (Memory* memory, bool record);
};


#endif /* ModuleType_hpp */
