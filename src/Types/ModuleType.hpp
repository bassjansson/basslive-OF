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
    ModuleType (MainFunction* mf);
    
    //========================================================================
    virtual void trigger();
};


#endif /* ModuleType_hpp */
