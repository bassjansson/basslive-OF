
#pragma once

#include "ofMain.h"
#include "Engine.hpp"


class MainApp : public ofBaseApp
{
public:
    //========================================================================
    void setup();
    void exit();
    void update();
    void draw();
    
    //========================================================================
    void audioIn  (float* buffer, int size, int channels);
    void audioOut (float* buffer, int size, int channels);
		
    //========================================================================
    void keyPressed  (int key);
    void keyReleased (int key);
    
    //========================================================================
    void mouseMoved    (int x, int y);
    void mouseDragged  (int x, int y, int button);
    void mousePressed  (int x, int y, int button);
    void mouseReleased (int x, int y, int button);
    
    //========================================================================
    void windowResized (int w, int h);
    void dragEvent     (ofDragInfo dragInfo);
    void gotMessage    (ofMessage msg);
    
private:
    //========================================================================
    Engine        engine;
    ofSoundStream soundStream;
};
