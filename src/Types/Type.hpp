//
//  Type.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#ifndef Type_hpp
#define Type_hpp

#include "Character.hpp"


class Type : public Character
{
public:
    //========================================================================
     Type (char c);
    ~Type ();
    
    //========================================================================
    virtual Character* draw (float& x, float& y, bool v);
    virtual void keyPressed (int key);
    
protected:
    //========================================================================
    ofColor typeColor;
};


#endif /* Type_hpp */
