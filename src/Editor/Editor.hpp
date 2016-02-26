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


class Editor
{
public:
    //========================================================================
    void setup();
    void exit();
    void update();
    void draw();
    
    //========================================================================
    void mousePressed (float x, float y, int button);
    void keyPressed   (int key);
    
    //========================================================================
    void windowResized();
    
    //========================================================================
    Memory** getMemoryPointer();
    
private:
    //========================================================================
    void newPage();
    
    //========================================================================
    ofxTabbedPages  tabbedPages;
    vector<MainFunction*> pages;
    
    //========================================================================
    Memory* memory;
};


#endif /* defined(__BassLive__Editor__) */
