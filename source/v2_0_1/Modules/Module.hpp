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
    sample ()            { L = R = 0.0f;  };
    sample (float value) { L = R = value; };
    
    float L, R;
};

class AudioSignal;
class AudioInput;
class AudioModule;
class AudioBuffer;

typedef AudioSignal  sig;
typedef vector<sig*> sig_vec;

typedef vector<AudioSignal> SignalVector;
typedef vector<AudioInput>  InputVector;


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
    void   allocate (tick newSize);
    void deallocate ();
    
    //========================================================================
    tick size();
    tick start();
    
    //========================================================================
    float  getBeatTime();
    sample getRMS();
    sample getValue (sample pointer);
    
    //========================================================================
    virtual void processSignal (Clock& clock) {};
    
    //========================================================================
          sample& operator[] (tick pointer)
    { if (buffer) return buffer[pointer]; return value; };
    const sample& operator[] (tick pointer) const
    { if (buffer) return buffer[pointer]; return value; };
    
protected:
    //========================================================================
    rec  recording;
    tick rec_start;
    
    //========================================================================
    float beatTime;
    
private:
    //========================================================================
    sample  value;
    sample* buffer;
    tick    b_size;
};


class AudioInput
{
public:
    //========================================================================
    AudioInput (sample defaultValue);
    
    //========================================================================
    void setSignalToDefault();
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
    
    //========================================================================
    void processSignal (Clock& clock);
    
    //========================================================================
    virtual void setInputs (sig_vec& newInputs);
    
protected:
    //========================================================================
    InputVector  inputs;
    AudioSignal& output;
    
private:
    //========================================================================
    virtual void process (Clock& clock) {};
    
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
