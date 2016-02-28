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
#include "Modules.h"


enum TypeType
{
    FUNC_CLOSE = 0,
    NUMBER,
    BUFFER,
    MODULE
};


class Type : public Character
{
public:
    //========================================================================
     Type (char c, MainFunction* mf);
    ~Type ();
    
    //========================================================================
    virtual Character* getEndChar();
    virtual Character* draw (float& x, float& y, bool vertical);
    virtual void flash (const ofColor& color);
    
    //========================================================================
    virtual void keyPressed (int key);
    virtual void trigger() {};
    
    //========================================================================
    virtual Type* process (buf& buffer, sig& output, Clock& clock);
    
    //========================================================================
    string   getTypeString();
    TypeType typeType;
    
protected:
    //========================================================================
    tick typeClock;
    sig  typeSignal;
    
    //========================================================================
    Function* funcPointer;
    
private:
    //========================================================================
    string  typeString;
    ofColor typeColor;
    float   flashFloat;
    
};


#endif /* Type_hpp */
