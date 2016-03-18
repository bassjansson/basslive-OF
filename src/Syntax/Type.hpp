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
    virtual void draw  (float& x, float& y, bool vertical, bool selection);
    virtual void flash (const ofColor& color);
    
    //========================================================================
    virtual void keyPressed (int key);
    virtual sig* compile (Memory* memory, bool record);
    
    //========================================================================
    void    setTypeString (const string& str);
    string& getTypeString ();
    
    //========================================================================
    TypeType typeType;
    
private:
    //========================================================================
    string  typeString;
    ofColor typeColor;
    float   flashFloat;
};


#endif /* Type_hpp */
