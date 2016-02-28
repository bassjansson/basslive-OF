//
//  MainFunction.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 18/02/16.
//
//

#ifndef MainFunction_hpp
#define MainFunction_hpp

#include "Function.hpp"
#include "ofxGuiExtended.h"

#define FRAME_RATE 30
#define FONT_SIZE  15


class MainFunction : public Function, public ofxGuiPage
{
public:
    //========================================================================
     MainFunction (const string& id);
    ~MainFunction ();
    
    //========================================================================
    void mousePressed  (float x, float y, int button);
    void mouseReleased (float x, float y, int button);
    void keyPressed    (int key);
    
    //========================================================================
    bool removeTypeIfSelected();
    
    //========================================================================
    Function* getModuleFunction (const string& id);
    Function* getBufferFunction (const string& id);
    
    //========================================================================
    ofTrueTypeFont charFont;
    float          charWidth;
    float          charHeight;
    Character*     charSelected;
    int            charCursorTime;
    
protected:
    //========================================================================
    void render();
};


#endif /* MainFunction_hpp */
