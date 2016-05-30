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

#define NEWTON_SIZE 3

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
    float xOffset, yOffset;
    float zoom;
    
    ofShader shader;
    
    fftwf_complex a;
    fftwf_complex coefs[NEWTON_SIZE];
};


#endif /* BassLive_hpp */
