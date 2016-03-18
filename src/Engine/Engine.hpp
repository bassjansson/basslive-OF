//
//  Engine.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 07/12/15.
//
//

#ifndef Engine_hpp
#define Engine_hpp

#include "MainFunction.hpp"


class Engine
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
    void keyPressed (int key);
    
    //========================================================================
    void mousePressed  (float x, float y, int button);
    void mouseReleased (float x, float y, int button);
    
private:
    //========================================================================
    Memory* memory;
    MainFunction* main;
};


#endif /* Engine_hpp */
