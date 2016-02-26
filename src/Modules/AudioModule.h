//
//  AudioModule.h
//  BassLive
//
//  Created by Bass Jansson on 16/11/15.
//
//

#ifndef __BassLive__AudioModule__
#define __BassLive__AudioModule__

#include "ofMain.h"

#define SAMPLERATE 48000
#define BUFFERSIZE 256

#define CHANNEL_INPUT  0
#define CHANNEL_CLICK  5
#define CHANNEL_OUTPUT 6
#define CHANNEL_SIZE   16

typedef u_long tick;
typedef float  tick_f;
typedef float  sample;
typedef float  beat;

typedef sample* sig;
typedef vector<sig> sig_vec;


struct Clock
{
    //========================================================================
    tick  clock;
    tick* buffer;
    tick  size;
    
    //========================================================================
    tick beatLength;
    tick barLength;
    
    //========================================================================
    const tick& operator[] (tick pointer) const { return buffer[pointer]; };
};


class AudioModule
{
public:
    //========================================================================
    virtual void process (sig_vec& inputs, sig output, Clock clock) {};
};


#endif /* defined(__BassLive__AudioModule__) */
