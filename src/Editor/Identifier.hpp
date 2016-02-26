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
    virtual Type* process    (sig& output, Clock& clock);
    virtual void  keyPressed (int key);
    virtual void  trigger    ();
    
private:
    //========================================================================
    Function* value;
};


#endif /* Identifier_hpp */
