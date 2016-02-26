//
//  AudioEngine.h
//  BassLive
//
//  Created by Bass Jansson on 16/11/15.
//
//

#ifndef __BassLive__AudioEngine__
#define __BassLive__AudioEngine__

#include "Memory.h"


class AudioEngine
{
public:
    //========================================================================
     AudioEngine();
    ~AudioEngine();
    
    //========================================================================
    void setMemoryPointer (Memory** memory);
    
    //========================================================================
    void audioIn  (sample* input,  tick size, int channels);
    void audioOut (sample* output, tick size, int channels);
    
private:
    //========================================================================
    void processClockAndClick();
    
    //========================================================================
    Memory** memory;
    Clock    clock;
    sample*  click;
};


#endif /* defined(__BassLive__AudioEngine__) */
