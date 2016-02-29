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

typedef float sample;
typedef sample* sig;
typedef vector<sig> sig_vec;

class   AudioBuffer;
typedef AudioBuffer* buf;
typedef vector<buf> buf_vec;


struct Clock
{
    //========================================================================
    tick  clock;
    tick* buffer;
    sig   null;
    
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
    virtual void process (sig_vec& inputs,
                          buf_vec& buffers,
                          sig      output,
                          Clock    clock) {};
};


class AudioBuffer : public AudioModule
{
public:
    //========================================================================
     AudioBuffer();
    ~AudioBuffer();
    
    //========================================================================
    tick getSize  ();
    tick getStart ();
    void record   (tick size);
    sample read   (tick_f pointer);
    
    //========================================================================
    virtual void process (sig_vec& inputs,
                          buf_vec& buffers,
                          sig      output,
                          Clock    clock);
    
private:
    //========================================================================
    sig  buffer;
    tick size;
    tick start;
    enum { OFF, WAIT, ON } recording;
};


#endif /* Module_hpp */
