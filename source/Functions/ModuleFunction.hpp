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
    virtual void drawTypeAnimation();
    virtual sig* compile (Memory* memory, bool record);
    
private:
    //========================================================================
    AudioModule* module;
};


#endif /* ModuleFunction_hpp */
