//
//  Function.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#ifndef Function_hpp
#define Function_hpp

#include "Identifier.hpp"


class Function : public Identifier
{
public:
    //========================================================================
     Function (MainFunction* mf);
    ~Function ();
    
    //========================================================================
    virtual Character* draw (float& x, float& y, bool vertical);
    virtual void keyPressed (int key);
    
protected:
    //========================================================================
    Identifier* identifier;
    Type*       close;
};


#endif /* Function_hpp */
