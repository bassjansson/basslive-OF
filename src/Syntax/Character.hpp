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


enum CharType
{
    CHAR = 0,
    TYPE,
    FUNC,
    BODY,
    MAIN
};


class Character
{
public:
    //========================================================================
    Character (char c);
    
    //========================================================================
    virtual void draw (float& x, float& y, bool vertical, bool selection, bool floating);
    virtual void drawCursor();
    
    //========================================================================
    virtual void mousePressed  (float x, float y, int button);
    virtual void mouseReleased (float x, float y, int button);
    
    //========================================================================
    void add (Character* c);
    void remove (bool force);
    
    //========================================================================
    Type*     getType     (bool dir);
    Function* getFunction (bool dir);
    
    //========================================================================
    Character* getEndChar();
    Character* getLeftChar();
    Character* getRightChar();
    Type*      getParentType();
    
    //========================================================================
    string& getCharString();
    
    //========================================================================
    CharType charType;
    
    //========================================================================
    static ofTrueTypeFont charFont;
    static float          charWidth;
    static float          charHeight;
    static Character*     charSelected;
    
protected:
    //========================================================================
    float x, y;
    
private:
    //========================================================================
    Character *begin, *end, *left, *right;
    
    //========================================================================
    string charString;
    float  animation;
};


#endif /* Character_hpp */
