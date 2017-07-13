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
#include "Memory.hpp"


enum TypeType
{
    NO_TYPE = 0,
    NUMBER,
    PERCENT,
    INPUT,
    MODULE,
    BUFFER
};


class Type : public Character
{
public:
    //========================================================================
    Type (char c);
    
    //========================================================================
    virtual void draw (float& x, float& y, bool vertical, bool selection, bool floating);
    virtual void flash (const ofColor& color);
    virtual Character* end();
    
    //========================================================================
    virtual void drawTypeAnimation() {};
    virtual void keyPressed (int key);
    virtual sig* compile (Memory* memory, bool record);
    
    //========================================================================
    virtual void copyTo (Character* c);
    
    //========================================================================
    TypeType typeType;
    ofColor typeColor;
    string typeString;
    
private:
    //========================================================================
    float flashValue;
};


#endif /* Type_hpp */
