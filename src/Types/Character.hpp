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

#define LEFT  0
#define RIGHT 1
#define UP    0
#define DOWN  1

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
    virtual Character* draw   (float& x, float& y, bool v);
    virtual void mousePressed (float x, float y, int button);
    virtual void keyPressed   (int key);
    
    //========================================================================
    CharType getCharType();
    Type*    getParentType();
    
    //========================================================================
    Character* getCharacter (bool dir);
    Type*      getType      (bool dir);
    Function*  getFunction  (bool dir);
    
protected:
    //========================================================================
    bool removeSelectedChar (bool b);
    
    //========================================================================
    static ofTrueTypeFont charFont;
    static float          charWidth;
    static float          charHeight;
    static Character*     charSelected;
    static int            charCursorTime;
    
    //========================================================================
    CharType charType;
    float x, y;
    
private:
    //========================================================================
    string charString;
    float  animation;
    
    //========================================================================
    Character* left;
    Character* right;
};


#endif /* Character_hpp */
