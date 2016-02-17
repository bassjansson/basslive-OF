//
//  Function.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#ifndef Function_hpp
#define Function_hpp

#include "Name.hpp"
#include "Number.hpp"


class Function : public Name
{
public:
    //========================================================================
     Function();
    ~Function();
    
    //========================================================================
    Character* draw (float& x, float& y, bool v);
    //void keyPressed (int key);
    
    //========================================================================
    void keyPressedMain (int key);
    
private:
    //========================================================================
    Name* identifier;
    Type* close;
};


#endif /* Function_hpp */
