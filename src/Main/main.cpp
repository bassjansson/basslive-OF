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
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 2);
    settings.windowMode = OF_FULLSCREEN;
    ofCreateWindow(settings);
    
    return ofRunApp(new BassLive());
}
