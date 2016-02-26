//
//  AudioModule.cpp
//  BassLive
//
//  Created by Bass Jansson on 16/11/15.
//
//

#include "AudioModule.h"


//========================================================================
Signal::Signal (AudioModule* module)
{
    this->value  = 0.0f;
    this->buffer = NULL;
    this->b_size = 0;
    this->module = module;
}

Signal::Signal (sample value)
{
    this->value  = value;
    this->buffer = NULL;
    this->b_size = 0;
    this->module = NULL;
}

//========================================================================
void Signal::allocate (tick size)
{
    if (buffer) delete[] buffer;
    
    b_size = size;
    buffer = new sample[b_size];
    
    for (tick t = 0; t < b_size; t++)
        buffer[t] = 0.0f;
}

void Signal::deallocate()
{
    if (buffer) delete[] buffer;
}

tick Signal::size()
{
    return b_size;
}

//========================================================================
void Signal::processModule (Clock& clock)
{
    if (module) module->processModule(clock);
}


//========================================================================
AudioModule::AudioModule (string ID, int inputChannels, int outputChannels)
{
    this->AM_ID = ID;
    this->clock = -1;
    
    for (int c = 0; c < inputChannels; c++)
        inputSignals.push_back(Signal(0.0f));
    
    for (int c = 0; c < outputChannels; c++)
    {
        outputSignals.push_back(Signal(this));
        outputSignals[c].allocate(BUFFERSIZE);
    }
}

AudioModule::~AudioModule()
{
    inputSignals.clear();
    
    for (int c = 0; c < outputSignals.size(); c++)
        outputSignals[c].deallocate();
    outputSignals.clear();
}

//========================================================================
string AudioModule::getID()
{
    return AM_ID;
}

int AudioModule::getInputChannels()
{
    return inputSignals.size();
}

int AudioModule::getOutputChannels()
{
    return outputSignals.size();
}

//========================================================================
void AudioModule::setInput (Signal* input, int channel)
{
    if (channel >= 0 && channel < inputSignals.size())
        inputSignals[channel] = *input;
}

Signal* AudioModule::getInput (int channel)
{
    if (channel >= 0 && channel < inputSignals.size())
        return &inputSignals[channel];
    
    return NULL;
}

Signal* AudioModule::getOutput (int channel)
{
    if (channel >= 0 && channel < outputSignals.size())
        return &outputSignals[channel];
    
    return NULL;
}

//========================================================================
void AudioModule::processModule (Clock& clock)
{
    if (this->clock != clock.clock)
    {
        this->clock = clock.clock;
        
        for (int c = 0; c < inputSignals.size(); c++)
            inputSignals[c].processModule(clock);
        
        process(inputSignals, outputSignals, clock);
    }
}

//========================================================================
void AudioModule::process (SignalVec& inputs, SignalVec& outputs, Clock clock)
{
    
}
