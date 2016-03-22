//
//  Character.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#ifndef Character_hpp
#define Character_hpp

#include "ofMain.h"

class Character;
class Type;
class Function;

typedef vector<Character*> CharVector;


enum CharType
{
    CHAR = 0,
    TYPE,
    FUNC,
    IDEN,
    CLOSE,
    MAIN
};


class Character
{
public:
    //========================================================================
    Character (char c);
    
    //========================================================================
    void add (Character* c, bool force = true);
    void remove (bool force = false);
    
    //========================================================================
    virtual void draw (float& x, float& y, bool vertical, bool selection, bool floating);
    virtual void drawFractal();
    virtual void drawCursor();
    virtual Character* end();
    
    //========================================================================
    Type*     getParentType ();
    Type*     getType       (bool dir);
    Function* getFunction   (bool dir);
    
    //========================================================================
    static ofTrueTypeFont charFont;
    static float          charWidth;
    static float          charHeight;
    static CharVector     charVector;
    static Character*     charSelected;
    
    static float RMS;
    
    //========================================================================
    Character *begin, *left, *right;
    CharType charType;
    string charString;
    
    //========================================================================
    float x, y;
    
private:
    //========================================================================
    float animation;
};


#endif /* Character_hpp */
