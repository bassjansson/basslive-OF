//
//  PercentType.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 31/03/16.
//
//

#ifndef PercentType_hpp
#define PercentType_hpp

#include "Type.hpp"


class PercentType : public Type
{
public:
    //========================================================================
    PercentType();
    
    //========================================================================
    virtual void keyPressed (int key);
    virtual sig* compile (Memory* memory, bool record);
    
    //========================================================================
    float getValue();
    
private:
    //========================================================================
    Character* percent;
    sig* value; // TODO: fix allocation error, fixed???
};

#endif /* PercentType_hpp */
