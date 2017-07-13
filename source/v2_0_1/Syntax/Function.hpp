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
    Function (char open, char close);
    
    //========================================================================
    virtual void draw (float& x, float& y, bool vertical, bool selection, bool floating);
    virtual void flash (const ofColor& color);
    virtual Character* end();
    
    //========================================================================
    virtual void copyTo (Character* c);
    
protected:
    //========================================================================
    Type* identifier;
    
private:
    //========================================================================
    Type* close;
};


#endif /* Function_hpp */
