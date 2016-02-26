//
//  MainFunction.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 18/02/16.
//
//

#ifndef MainFunction_hpp
#define MainFunction_hpp

#include "ofxGuiExtended.h"

#include "Memory.h"

#include "Number.hpp"
#include "Identifier.hpp"
#include "Function.hpp"

#define FRAME_RATE 30
#define FONT_SIZE  15


class MainFunction : public Function, public ofxGuiPage
{
public:
    //========================================================================
     MainFunction (string name);
    ~MainFunction ();
    
    //========================================================================
    void mousePressed (float x, float y, int button);
    void keyPressed   (int key);
    
    //========================================================================
    bool removeTypeIfSelected();
    
    //========================================================================
    ofTrueTypeFont charFont;
    float          charWidth;
    float          charHeight;
    Character*     charSelected;
    int            charCursorTime;
    
    //========================================================================
    Memory* memory;
    
protected:
    //========================================================================
    void render();
};


#endif /* MainFunction_hpp */
