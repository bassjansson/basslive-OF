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

#define CHAR_TYPE_NUMBER '$'
#define CHAR_TYPE_MOD_ID ':'
#define CHAR_TYPE_BUF_ID '@'

#define CHAR_FUNC_MOD_OPEN  '('
#define CHAR_FUNC_MOD_CLOSE ')'
#define CHAR_FUNC_BUF_OPEN  '['
#define CHAR_FUNC_BUF_CLOSE ']'

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
    virtual Character* getEndChar();
    virtual Character* draw (float& x, float& y, bool vertical);
    virtual void drawCursor();
    
    //========================================================================
    virtual void mousePressed  (float x, float y, int button);
    virtual void mouseReleased (float x, float y, int button);
    
    //========================================================================
    Character* getCharacter (bool dir);
    Type*      getType      (bool dir);
    Function*  getFunction  (bool dir);
    
    //========================================================================
    Type*    getParentType();
    string   getCharString();
    CharType charType;
    
protected:
    //========================================================================
    bool removeSelectedChar (bool removeFunctionBodies);
    void   moveSelectedChar (Character* destination);
    
    //========================================================================
    MainFunction* mf;
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
