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
#include "AudioModule.h"


class Type : public Character
{
public:
    //========================================================================
     Type (char c, MainFunction* mf);
    ~Type ();
    
    //========================================================================
    virtual Character* getEndChar();
    virtual Character* draw (float& x, float& y, bool vertical);
    virtual Type* process   (sig& output, Clock& clock);
    virtual void keyPressed (int key);
    virtual void trigger(){};
    
    //========================================================================
    string getTypeString();
    
protected:
    //========================================================================
    ofColor typeColor;
    string  typeString;
    sig     typeSignal;
};


#endif /* Type_hpp */
