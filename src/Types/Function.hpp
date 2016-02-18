//
//  Function.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#ifndef Function_hpp
#define Function_hpp

#include "Number.hpp"
#include "Identifier.hpp"


class Function : public Identifier
{
public:
    //========================================================================
     Function();
    ~Function();
    
    //========================================================================
    virtual Character* draw (float& x, float& y, bool v);
    
    //========================================================================
    void mousePressedMain (float x, float y, int button);
    void keyPressedMain   (int key);
    
    //========================================================================
    bool removeSelectedType (bool removeFunctions);
    
private:
    //========================================================================
    Identifier* identifier;
    Type*       close;
};


#endif /* Function_hpp */
