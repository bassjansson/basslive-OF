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

struct Clock;
class  Signal;
class  AudioModule;

typedef vector<Signal> SignalVec;


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


class Signal
{
public:
    //========================================================================
    Signal (AudioModule* module);
    Signal (sample value);
    
    //========================================================================
    void   allocate (tick size);
    void deallocate ();
    tick       size ();
    
    //========================================================================
    void processModule (Clock& clock);
    
    //========================================================================
          sample& operator[] (tick pointer)
    { if (buffer && pointer < b_size) return buffer[pointer]; else return value; };
    const sample& operator[] (tick pointer) const
    { if (buffer && pointer < b_size) return buffer[pointer]; else return value; };
    
private:
    //========================================================================
    sample       value;
    sample*      buffer;
    tick         b_size;
    AudioModule* module;
};


class AudioModule
{
public:
    //========================================================================
     AudioModule (string ID, int inputChannels, int outputChannels);
    ~AudioModule ();
    
    //========================================================================
    string getID();
    int    getInputChannels();
    int    getOutputChannels();
    
    //========================================================================
    void    setInput  (Signal* input, int channel);
    Signal* getInput  (int channel);
    Signal* getOutput (int channel);
    
    //========================================================================
    void processModule (Clock& clock);
    
private:
    //========================================================================
    virtual void process (SignalVec& inputs, SignalVec& outputs, Clock clock);
    
    //========================================================================
    string AM_ID;
    tick   clock;
    
    //========================================================================
    SignalVec inputSignals;
    SignalVec outputSignals;
};


#endif /* defined(__BassLive__AudioModule__) */
