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
     AudioBuffer (string ID);
    ~AudioBuffer ();
    
    //========================================================================
    tick getSize  ();
    tick getStart ();
    void   record (tick size);
    sample   read (tick_f pointer, int channel, Clock& clock);
    
private:
    //========================================================================
    void process (SignalVec& inputs, SignalVec& outputs, Clock clock);
    
    //========================================================================
    tick start;
    SignalVec buffers;
    enum { OFF, WAIT, ON } recording;
};


#endif /* defined(__BassLive__AudioBuffer__) */
