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
    ModuleFunction (MainFunction* mf);
    
    //========================================================================
    virtual void trigger();
    
    //========================================================================
    virtual Type* process (buf& buffer, sig& output, Clock& clock);
    
private:
    //========================================================================
    AudioModule* module;
    buf_vec buffers;
    sig_vec inputs;
};


#endif /* ModuleFunction_hpp */
