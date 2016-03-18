//
//  InputType.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 29/02/16.
//
//

#ifndef InputType_hpp
#define InputType_hpp

#include "Type.hpp"


class InputType : public Type
{
public:
    //========================================================================
    InputType();
    
    //========================================================================
    virtual void keyPressed (int key);
    virtual sig* compile (Memory* memory, bool record);
};


#endif /* InputType_hpp */
