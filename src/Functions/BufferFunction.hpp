//
//  BufferFunction.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 28/02/16.
//
//

#ifndef BufferFunction_hpp
#define BufferFunction_hpp

#include "Function.hpp"


class BufferFunction : public Function
{
public:
    //========================================================================
    BufferFunction();
    
    //========================================================================
    virtual sig* compile (Memory* memory, bool record);
};


#endif /* BufferFunction_hpp */
