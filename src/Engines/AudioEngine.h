//
//  AudioEngine.h
//  BassLive
//
//  Created by Bass Jansson on 16/11/15.
//
//

#ifndef __BassLive__AudioEngine__
#define __BassLive__AudioEngine__

#include "MainFunction.hpp"


class AudioEngine
{
public:
    //========================================================================
     AudioEngine();
    ~AudioEngine();
    
    //========================================================================
    void audioOut (MainFunction* mf, sig output, tick size, int channels);
    
private:
    //========================================================================
    void processClockAndClick();
    
    //========================================================================
    Clock   clock;
    sample* click;
};


#endif /* defined(__BassLive__AudioEngine__) */
