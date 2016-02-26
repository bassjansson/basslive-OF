//
//  Identifier.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 17/02/16.
//
//

#ifndef Identifier_hpp
#define Identifier_hpp

#include "Type.hpp"


class Identifier : public Type
{
public:
    //========================================================================
    Identifier (char c, MainFunction* mf);
    Identifier (MainFunction* mf);
    
    //========================================================================
    virtual void keyPressed (int key);
};


#endif /* Identifier_hpp */
