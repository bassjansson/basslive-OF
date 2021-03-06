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
    //virtual void drawFractal(); // TODO: move fractal to type
    virtual void drawCursor (float size); // Fancy cursor?
    virtual Character* end();
    
    //========================================================================
    Type*     getParentType ();
    Type*     getType       (bool dir);
    Function* getFunction   (bool dir);
    
    //========================================================================
    static ofTrueTypeFont charFont;
    static float          charWidth;
    static float          charHeight;
    static CharVector     charVector; // TODO: better memory managment
    static Character*     charSelected;
    
    static float mouseX, mouseY;
    
    static float RMS;
    
    //========================================================================
    Character *begin, *left, *right; // TODO: should not be public
    CharType charType;
    string charString;
    
    //========================================================================
    float x, y;
    float xAnim, yAnim;
    
private:
    //========================================================================
    float animation;
};


#endif /* Character_hpp */
