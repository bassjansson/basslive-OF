//
//  Function.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#ifndef Function_hpp
#define Function_hpp

#include "Type.hpp"


class Function : public Type
{
public:
    //========================================================================
     Function (char open, char type, char close, MainFunction* mf);
    ~Function ();
    
    //========================================================================
    virtual Character* getEndChar();
    virtual Character* draw (float& x, float& y, bool vertical, bool selection);
    
    //========================================================================
    string getIdentifierString();
    
protected:
    //========================================================================
    Type* identifier;
    Type* close;
};


#endif /* Function_hpp */
