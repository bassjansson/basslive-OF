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
    NumberType (MainFunction* mf);
    
    //========================================================================
    virtual void keyPressed (int key);
    virtual void trigger();
    
    //========================================================================
    float getValue();
    
private:
    //========================================================================
    float value;
};


#endif /* NumberType_hpp */
