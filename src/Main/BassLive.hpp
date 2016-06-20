//
//  BassLive.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 16/11/15.
//
//

#ifndef BassLive_hpp
#define BassLive_hpp

#include "Syntax.h"

#define NEWTON_SIZE 4

class BassLive : public ofBaseApp
{
public:
    //========================================================================
    void setup();
    void exit();
    void update();
    void draw();
    
    //========================================================================
    void audioIn  (float* input,  int size, int channels);
    void audioOut (float* output, int size, int channels);
		
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
    Memory*       memory;
    MainFunction* main;
    ofSoundStream stream;
    
    //========================================================================
    float sideBarWidth;
    float xOffset, yOffset;
    float zoom, zoomTarget;
    
    //========================================================================
    ofTrueTypeFont sideBarFont;
    ofShader shader;
    
    //========================================================================
    float a[2];
    float coefs[NEWTON_SIZE][2];
};


#endif /* BassLive_hpp */
