//
//  BufferType.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 28/02/16.
//
//

#ifndef BufferType_hpp
#define BufferType_hpp

#include "Type.hpp"


class BufferType : public Type
{
public:
    //========================================================================
    BufferType();
    
    //========================================================================
    virtual sig* compile (Memory* memory, bool record);
};


#endif /* BufferType_hpp */
