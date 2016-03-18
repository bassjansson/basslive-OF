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
     Memory();
    ~Memory();
    
    //========================================================================
    AudioSignal* getADC (int channel);
    AudioModule* getDAC ();
    
    //========================================================================
    AudioModule* addModule (const string& module, const string& ID);
    AudioBuffer* addBuffer (const string& buffer, const string& ID);
    
    //========================================================================
    AudioModule* getModule (const string& ID);
    AudioBuffer* getBuffer (const string& ID);
    
    //========================================================================
    int getNewID();
    
    //========================================================================
    Clock& getClock();
    
    //========================================================================
    void processClockAndClick();
    
private:
    //========================================================================
    sig_vec      adc;
    AudioModule* dac;
    
    //========================================================================
    vector<AudioModule*> modules;
    vector<AudioBuffer*> buffers;
    
    //========================================================================
    int idCount;
    
    //========================================================================
    Clock   clock;
    sample* click;
};


#endif /* Memory_hpp */
