//
//  BasicModules.h
//  BassLive
//
//  Created by Bass Jansson on 16/11/15.
//
//

#ifndef __BassLive__BasicModules__
#define __BassLive__BasicModules__

#include "AudioModule.h"
#include "AudioBuffer.h"

#define OPERATOR_MAX_ARGS 5


//========================================================================
// loop_Module
//========================================================================
class loop_Module : public AudioModule
{
public:
    loop_Module (string ID);
    void setBuffer (AudioBuffer* buffer);
    
private:
    void process (SignalVec& inputs, SignalVec& outputs, Clock clock);
    AudioBuffer* buffer;
};


//========================================================================
// add_Module
// mul_Module
// sub_Module
// div_Module
//========================================================================
class add_Module : public AudioModule
{
public:    add_Module (string ID);
private: void process (SignalVec& inputs, SignalVec& outputs, Clock clock);
};

class mul_Module : public AudioModule
{
public:    mul_Module (string ID);
private: void process (SignalVec& inputs, SignalVec& outputs, Clock clock);
};

class sub_Module : public AudioModule
{
public:    sub_Module (string ID);
private: void process (SignalVec& inputs, SignalVec& outputs, Clock clock);
};

class div_Module : public AudioModule
{
public:    div_Module (string ID);
private: void process (SignalVec& inputs, SignalVec& outputs, Clock clock);
};


#endif /* defined(__BassLive__BasicModules__) */
