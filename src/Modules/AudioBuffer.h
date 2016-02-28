//
//  AudioBuffer.h
//  BassLive
//
//  Created by Bass Jansson on 25/11/15.
//
//

#ifndef __BassLive__AudioBuffer__
#define __BassLive__AudioBuffer__

#include "AudioModule.h"


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
    sample read   (tick_f pointer, Clock& clock);
    
private:
    //========================================================================
    virtual void process (buf_vec& buffers,
                          sig_vec& inputs,
                          sig      output,
                          Clock    clock) {};
    
    //========================================================================
    sig  buffer;
    tick size;
    tick start;
    enum { OFF, WAIT, ON } recording;
};


#endif /* defined(__BassLive__AudioBuffer__) */
