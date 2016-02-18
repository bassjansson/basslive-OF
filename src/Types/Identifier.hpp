//
//  Identifier.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 17/02/16.
//
//

#ifndef Identifier_hpp
#define Identifier_hpp

#include "Signal.hpp"


class Identifier : public Signal
{
public:
    //========================================================================
    Identifier (char c);
    
    //========================================================================
    virtual void keyPressed (int key);
};


#endif /* Identifier_hpp */
