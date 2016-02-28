//
//  Editor.hpp
//  BassLive
//
//  Created by Bass Jansson on 07/12/15.
//
//

#ifndef __BassLive__Editor__
#define __BassLive__Editor__

#include "MainFunction.hpp"

#define EDITOR_WIDTH  (ofGetWidth())
#define EDITOR_HEIGHT (ofGetHeight() - FONT_SIZE * 2)


class Engine
{
public:
    //========================================================================
    void setup();
    void exit();
    void update();
    void draw();
    
    //========================================================================
    void audioOut      (sig output, tick size, int channels);
    void mousePressed  (float x, float y, int button);
    void mouseReleased (float x, float y, int button);
    void keyPressed    (int key);
    void windowResized ();
    
private:
    //========================================================================
    void newPage();
    void processClockAndClick();
    
    //========================================================================
    bool mouseIsPressed;
    
    //========================================================================
    ofxTabbedPages  tabbedPages;
    vector<MainFunction*> pages;
    
    //========================================================================
    Clock   clock;
    sample* click;
};


#endif /* defined(__BassLive__Editor__) */
