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

#define FRAME_RATE 30
#define HORIZONTAL 0
#define VERTICAL   1

class Character;
class Type;
class Function;


enum CharType
{
    CHARACTER = 0,
    TYPE,
    FUNCTION,
    FUNCTION_BODY
};


class Character
{
public:
    //========================================================================
    Character (char c);
    
    //========================================================================
    bool loadFont (const string& fileName, int fontSize);
    
    //========================================================================
    virtual Character* draw (float& x, float& y, bool v);
    
    //========================================================================
    Character* getNextChar();
    CharType   getCharType();
    bool       getNoneType();
    Type*      getParentType();
    
protected:
    //========================================================================
    void removeSelectedChar (bool b);
    void moveLeft();
    void moveRight();
    
    //========================================================================
    static ofTrueTypeFont charFont;
    static float          charWidth;
    static float          charHeight;
    static Character*     charSelected;
    static int            charCursorTime;
    
    //========================================================================
    CharType charType;
    bool     noneType;
    
private:
    //========================================================================
    string charString;
    float  animation;
    
    //========================================================================
    Character* left;
    Character* right;
};


#endif /* Character_hpp */
