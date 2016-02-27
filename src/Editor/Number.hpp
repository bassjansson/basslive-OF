//
//  Number.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 17/02/16.
//
//

#ifndef Number_hpp
#define Number_hpp

#include "Type.hpp"


class Number : public Type
{
public:
    //========================================================================
    Number (MainFunction* mf);
    
    //========================================================================
    virtual void keyPressed (int key);
    virtual void trigger();
    
private:
    //========================================================================
    sample value;
};


#endif /* Number_hpp */
