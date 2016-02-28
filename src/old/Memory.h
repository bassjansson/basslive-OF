//
//  Memory.h
//  BassLive
//
//  Created by Bass Jansson on 16/11/15.
//
//

#ifndef __BassLive__Memory__
#define __BassLive__Memory__

#include "Modules.h"


class Memory
{
public:
    //========================================================================
     Memory();
    ~Memory();
    
    //========================================================================
    AudioModule* getADC();
    AudioModule* getDAC();
    
    //========================================================================
    AudioModule* getAudioModule (string ID);
    void         addAudioModule (AudioModule* module);
    
    //========================================================================
    AudioBuffer* getAudioBuffer (string ID);
    void         addAudioBuffer (AudioBuffer* buffer);
    void         processBuffers (Clock& clock);
    
    //========================================================================
    void setBeatsPerMinute (beat bpm);
    void setBeatsPerBar    (beat bpb);
    
    //========================================================================
    tick getBeatLength();
    tick getBarLength();
    
    //========================================================================
    string getNewSID();
    
private:
    //========================================================================
    vector<AudioModule*> modules;
    vector<AudioBuffer*> buffers;
    
    //========================================================================
    tick beatLength;
    tick barLength;
    
    //========================================================================
    u_long sidCount;
};


#endif /* defined(__BassLive__Memory__) */
