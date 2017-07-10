//
//  NumberType.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 17/02/16.
//
//

#ifndef NumberType_hpp
#define NumberType_hpp

#include "Type.hpp"


class NumberType : public Type
{
public:
    //========================================================================
    NumberType();
    
    //========================================================================
    virtual void keyPressed (int key);
    virtual sig* compile (Memory* memory, bool record);
    
    //========================================================================
    float getValue();
    
private:
    //========================================================================
    sig* value; // TODO: fix allocation error, fixed???
};


#endif /* NumberType_hpp */
