//
//  Number.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 17/02/16.
//
//

#ifndef Number_hpp
#define Number_hpp

#include "Signal.hpp"


class Number : public Signal
{
public:
    //========================================================================
    Number();
    
    //========================================================================
    virtual void keyPressed (int key);
};


#endif /* Number_hpp */
