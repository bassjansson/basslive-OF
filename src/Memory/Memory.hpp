//
//  Memory.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 16/11/15.
//
//

#ifndef Memory_hpp
#define Memory_hpp

#include "Modules.h"


class Memory
{
public:
    //========================================================================
     Memory (int inputChannels);
    ~Memory ();
    
    //========================================================================
    void audioIn  (float* input,  int size, int channels);
    void audioOut (float* output, int size, int channels);
    
    //========================================================================
    Clock& getClock();
    
    //========================================================================
    AudioSignal* getADC (int channel);
    AudioModule* getDAC ();
    
    //========================================================================
    AudioModule* getModule (const string& ID);
    AudioBuffer* getBuffer (const string& ID);
    
    //========================================================================
    AudioModule* addModule (const string& module, const string& ID);
    AudioBuffer* addBuffer (const string& buffer, const string& ID);
    
    //========================================================================
    int getNewID();
    
private:
    //========================================================================
    void processClockAndClick();
    
    //========================================================================
    Clock clock;
    sig   click;
    
    //========================================================================
    sig_vec      adc;
    AudioModule* dac;
    
    //========================================================================
    vector<AudioModule*> modules;
    vector<AudioBuffer*> buffers;
    
    //========================================================================
    int idCount;
};


#endif /* Memory_hpp */
