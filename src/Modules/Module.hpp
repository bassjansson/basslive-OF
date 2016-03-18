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
typedef float  tick_f;
typedef float  beat;

struct sample
{
    float L, R;
    sample() { L = R = 0.0f; };
};

class AudioSignal;
class AudioModule;
class AudioBuffer;

typedef AudioSignal sig;
typedef vector<sig> sig_vec;


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
    AudioSignal (AudioModule* module);
    AudioSignal (sample value);
    
    //========================================================================
    tick       size ();
    tick      start ();
    void      start (tick start);
    void   allocate (tick size);
    void deallocate ();
    
    //========================================================================
    void processModule (Clock& clock);
    
    //========================================================================
          sample& operator[] (tick pointer)
    { if (buffer) return buffer[pointer]; else return value; };
    const sample& operator[] (tick pointer) const
    { if (buffer) return buffer[pointer]; else return value; };
    
private:
    //========================================================================
    sample       value;
    sample*      buffer;
    tick         b_size;
    tick         b_start;
    AudioModule* module;
};


class AudioModule
{
public:
    //========================================================================
     AudioModule (const string& ID, int channels);
    ~AudioModule ();
    
    //========================================================================
    void    setInput  (sig* input, int channel);
    sig*    getOutput ();
    string& getID     ();
    
    //========================================================================
    void processModule (Clock& clock);
    
protected:
    //========================================================================
    sig_vec inputs;
    sig     output;
    
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
    
    //========================================================================
    enum { OFF, WAIT, ON } recording;
};


#endif /* Module_hpp */
