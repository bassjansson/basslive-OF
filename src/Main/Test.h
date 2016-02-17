//
//  Test.h
//  BassLive 2.0
//
//  Created by Bass Jansson on 13/01/16.
//
//

#ifndef Test_hpp
#define Test_hpp

#include "ofMain.h"


class Character
{
public:
    //========================================================================
    Character ();
    Character (char c);
    
    //========================================================================
    float getWidth();
    float getHeight();
    
    //========================================================================
    bool loadFont (const string& fileName, int fontSize);
    void setChar  (char c);
    void resetTime();
    void draw     (float x, float y, bool cursor);
    
private:
    //========================================================================
    static ofTrueTypeFont charFont;
    static float          charWidth;
    static float          charHeight;
    
    //========================================================================
    string charString;
    float  size;
    int    time;
};


class String
{
public:
    //========================================================================
    String();
    
    //========================================================================
    void keyPressed (int key);
    void draw (float x, float y);
    
private:
    //========================================================================
    vector<Character> charVector;
    vector<Character>::iterator position;
};


#endif /* Test_hpp */
