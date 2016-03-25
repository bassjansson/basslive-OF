//
//  Module.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 29/02/16.
//
//

#ifndef Module_hpp
#define Module_hpp

#include "ofMain.h"

typedef u_long tick;
enum rec { OFF, WAIT, ON };

struct sample
{
    sample (float value) { L = R = value; };
    
    float L, R;
};

class AudioSignal;
class AudioInput;
class AudioModule;
class AudioBuffer;

typedef AudioSignal sig;
typedef vector<AudioInput> InputVector;


struct Clock
{
    //========================================================================
    tick clock;
    tick size;
    
    //========================================================================
    tick* clockTime;
    tick* beatLength;
    tick* barLength;
    
    //========================================================================
    const tick& operator[] (tick pointer) const { return clockTime[pointer]; };
};


class AudioSignal
{
public:
    //========================================================================
    AudioSignal (sample value);
    
    //========================================================================
    tick size();
    tick start();
    rec  recording();
    
    //========================================================================
    virtual sample getRMS();
    virtual void   processSignal();
    
    //========================================================================
    virtual       sample& operator[] (tick pointer)       { return value; };
    virtual const sample& operator[] (tick pointer) const { return value; };

protected:
    //========================================================================
    tick signalSize;
    tick signalStart;
    rec  signalRecording;
    
private:
    //========================================================================
    sample value;
};


class AudioInput
{
public:
    //========================================================================
    AudioInput (sig* defaultSignal);
    
    //========================================================================
    void setToDefaultSignal();
    void setSignal (sig* signal);
    sig* getSignal ();
    
    //========================================================================
    const sample& operator[] (tick pointer) const { return (*signal)[pointer]; };
    
private:
    //========================================================================
    sig* defaultSignal;
    sig* signal;
};


class AudioModule : public AudioSignal
{
public:
    //========================================================================
     AudioModule (const string& ID);
    ~AudioModule ();
    
    //========================================================================
    const string& getID();
    InputVector&  getInputs();
    
    //========================================================================
    virtual sample getRMS();
    virtual void   processSignal();
    
    //========================================================================
    virtual       sample& operator[] (tick pointer)       { return output[pointer]; };
    virtual const sample& operator[] (tick pointer) const { return output[pointer]; };
    
protected:
    //========================================================================
    InputVector inputs;
    sample*     output;
    
private:
    //========================================================================
    virtual void process (Clock& clock);
    
    //========================================================================
    string AM_ID;
    tick   clock;
};


class AudioBuffer : public AudioModule
{
public:
    //========================================================================
    AudioBuffer (const string& ID);
    
    //========================================================================
    virtual void record (tick size);
    
private:
    //========================================================================
    virtual void process (Clock& clock);
};


#endif /* Module_hpp */
