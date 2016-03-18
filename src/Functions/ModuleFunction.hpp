//
//  ModuleFunction.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 28/02/16.
//
//

#ifndef ModuleFunction_hpp
#define ModuleFunction_hpp

#include "Function.hpp"


class ModuleFunction : public Function
{
public:
    //========================================================================
    ModuleFunction();
    
    //========================================================================
    virtual sig* compile (Memory* memory, bool record);
};


#endif /* ModuleFunction_hpp */
