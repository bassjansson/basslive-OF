//
//  MainFunction.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 18/02/16.
//
//

#ifndef MainFunction_hpp
#define MainFunction_hpp

#include "ModuleFunction.hpp"
#include "ofxGuiExtended.h"


class MainFunction : public ModuleFunction, public ofxGuiPage
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
    char getNewModuleID();
    char getNewBufferID();
    
    //========================================================================
    tick getBeatLength();
    tick getBarLength();
    
    //========================================================================
    ofTrueTypeFont charFont;
    float          charWidth;
    float          charHeight;
    Character*     charSelected;
    
protected:
    //========================================================================
    void render();
    bool removeTypeIfSelected();
    
private:
    //========================================================================
    int moduleIDCounter;
    int bufferIDCounter;
    
    //========================================================================
    tick beatLength;
    tick barLength;
    tick cursorTime;
};


#endif /* MainFunction_hpp */
