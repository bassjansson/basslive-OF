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
    InputType (MainFunction* mf);
    
    //========================================================================
    virtual void keyPressed (int key);
    virtual void trigger();
    
    //========================================================================
    virtual Type* process (buf& buffer, sig& output, Clock& clock);
    
private:
    //========================================================================
    int channel;
};


#endif /* InputType_hpp */
