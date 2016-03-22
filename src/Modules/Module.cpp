//
//  Module.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 29/02/16.
//
//

#include "Modules.h"


//========================================================================
// AudioSignal
//========================================================================
AudioSignal::AudioSignal (AudioModule* module)
{
    value  = sample();
    buffer = NULL;
    b_size = 0;
    
    this->module = module;
}

AudioSignal::AudioSignal (sample value)
{
    this->value = value;
    
    buffer = NULL;
    b_size = 0;
    module = NULL;
}

//========================================================================
tick AudioSignal::size()
{
    return b_size;
}

tick AudioSignal::start()
{
    return b_start;
}

void AudioSignal::start (tick start)
{
    b_start = start;
}

void AudioSignal::allocate (tick size)
{
    if (buffer) delete[] buffer;
    
    b_size = size;
    buffer = new sample[b_size];
    
    for (tick t = 0; t < b_size; t++)
        buffer[t] = sample();
}

void AudioSignal::deallocate()
{
    if (buffer) delete[] buffer;
    
    b_size = 0;
}

//========================================================================
void AudioSignal::processModule (Clock& clock)
{
    if (module) module->processModule(clock);
}


//========================================================================
// AudioModule
//========================================================================
AudioModule::AudioModule (const string& ID, int channels) : output(this)
{
    for (tick t = 0; t < channels; t++)
        inputs.push_back(AudioSignal(sample()));
    
    output.allocate(BUFFERSIZE);
    
    AM_ID = ID;
    clock = -1;
}

AudioModule::~AudioModule()
{
    inputs.clear();
    output.deallocate();
}

//========================================================================
void AudioModule::setInput (sig* input, int channel)
{
    if (channel >= 0 && channel < inputs.size())
    {
        if (input == NULL)
            inputs[channel] = AudioSignal(sample());
        else
            inputs[channel] = *input;
    }
}

sig* AudioModule::getOutput()
{
    return &output;
}

string& AudioModule::getID()
{
    return AM_ID;
}

//========================================================================
void AudioModule::processModule (Clock& clock)
{
    if (this->clock != clock.clock)
    {
        this->clock = clock.clock;
        
        for (tick t = 0; t < inputs.size(); t++)
            inputs[t].processModule(clock);
        
        process(clock);
    }
}


//========================================================================
// AudioBuffer
//========================================================================
AudioBuffer::AudioBuffer (const string& ID) : AudioModule(ID, 1)
{
    recording = OFF;
}

//========================================================================
void AudioBuffer::record (tick size)
{
    output.allocate(size);
    
    recording = WAIT;
}

//========================================================================
void AudioBuffer::process (Clock& clock)
{
    for (tick t = 0; t < clock.size; t++)
    {
        if (recording == WAIT)
        {
            if ((clock[t] + BUFFERSIZE) % clock.barLength[t] < BUFFERSIZE)
            {
                output.start(clock[t]);
                
                recording = ON;
            }
        }
        
        if (recording == ON)
        {
            // Get pointer
            tick pointer = clock[t] - output.start();
            
            
            // Get envelope
            float envelope = 1.0f;
            
            if (pointer < FADE_SIZE)
                envelope = sqrtf(pointer / FADE_SIZE);
            
            if (output.size() - pointer < FADE_SIZE)
                envelope = sqrtf((output.size() - pointer) / FADE_SIZE);
                
                
            // Write input to output
            if (pointer < output.size())
            {
                output[pointer].L = inputs[0][t].L * envelope;
                output[pointer].R = inputs[0][t].R * envelope;
            }
            else
            {
                recording = OFF;
            }
        }
    }
}
