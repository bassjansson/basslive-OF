//
//  Name.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 17/02/16.
//
//

#ifndef Name_hpp
#define Name_hpp

#include "Signal.hpp"


class Name : public Signal
{
public:
    //========================================================================
    Name (char c);
    
    //========================================================================
    virtual void keyPressed (int key);
};


#endif /* Name_hpp */
