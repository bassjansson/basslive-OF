//
//  main.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 16/11/15.
//
//

#include "BassLive.hpp"


int main()
{
    //ofSetupOpenGL(1024, 576, OF_WINDOW);
    
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 2); //we define the OpenGL version we want to use
    //settings.width = 1024;
    //settings.height = 768;
    settings.windowMode = OF_FULLSCREEN;
    ofCreateWindow(settings);
    
    return ofRunApp(new BassLive());
}
