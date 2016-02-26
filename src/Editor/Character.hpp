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

#define HORIZONTAL 0
#define VERTICAL   1

#define LEFT  0
#define RIGHT 1
#define UP    0
#define DOWN  1

#define CHAR_TYPE_NUMB  '#'
#define CHAR_TYPE_IDEN  '$'
#define CHAR_FUNC_IDEN  ':'
#define CHAR_FUNC_OPEN  '('
#define CHAR_FUNC_CLOSE ')'

class Character;
class Type;
class Function;
class MainFunction;


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
    Character (char c, MainFunction* mf);
    
    //========================================================================
    virtual Character* draw   (float& x, float& y, bool vertical);
    virtual void mousePressed (float x, float y, int button);
    virtual void drawCursor   ();
    
    //========================================================================
    Character* getCharacter (bool dir);
    Type*      getType      (bool dir);
    Function*  getFunction  (bool dir);
    
    //========================================================================
    CharType getCharType();
    Type*    getParentType();
    
protected:
    //========================================================================
    bool removeSelectedChar (bool removeFunctionBodies);
    
    //========================================================================
    MainFunction* mf;
    CharType charType;
    
    //========================================================================
    Character* left;
    Character* right;
    
private:
    //========================================================================
    string charString;
    float  animation;
    float  x, y;
};


#endif /* Character_hpp */
