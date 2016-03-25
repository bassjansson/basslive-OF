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
AudioSignal::AudioSignal (sample value)
{
    this->value  = value;
    this->buffer = NULL;
    this->b_size = 1;
    
    recording = OFF;
    rec_start = 0;
}

//========================================================================
void AudioSignal::allocate (tick size)
{
    deallocate();
    
    if (size > 0)
    {
        b_size = size;
        buffer = new sample[b_size];
    }
}

void AudioSignal::deallocate()
{
    if (b_size > 1) delete[] buffer;
    
    b_size = 1;
}

//========================================================================
tick AudioSignal::size()
{
    return b_size;
}

sample AudioSignal::getRMS()
{
    if (buffer)
    {
        sample RMS = 0.0f;
        
        for (tick t = 0; t < b_size; t++)
        {
            RMS.L += buffer[t].L * buffer[t].L;
            RMS.R += buffer[t].R * buffer[t].R;
        }
        
        RMS.L = sqrtf(RMS.L / b_size);
        RMS.R = sqrtf(RMS.R / b_size);
        
        return RMS;
    }

    return value;
}


//========================================================================
// AudioInput
//========================================================================
AudioInput::AudioInput (sample defaultValue) : defaultSignal(defaultValue)
{
    signal = &defaultSignal;
}

//========================================================================
void AudioInput::setSignalToDefault()
{
    signal = &defaultSignal;
}

void AudioInput::setSignal (sig* signal)
{
    if (signal)
        this->signal = signal;
    else
        setSignalToDefault();
}

sig* AudioInput::getSignal()
{
    return signal;
}


//========================================================================
// AudioModule
//========================================================================
AudioModule::AudioModule (const string& ID) : AudioSignal(0.0f), output(*this)
{
    AM_ID = ID;
    clock = -1;
    
    allocate(BUFFERSIZE);
}

AudioModule::~AudioModule()
{
    inputs.clear();
    
    deallocate();
}

//========================================================================
const string& AudioModule::getID()
{
    return AM_ID;
}

//========================================================================
void AudioModule::processSignal (Clock& clock)
{
    if (this->clock != clock.clock)
    {
        this->clock = clock.clock;
        
        for (int c = 0; c < inputs.size(); c++)
            inputs[c].getSignal()->processSignal(clock);
        
        process(clock);
    }
}

//========================================================================
void AudioModule::setInputs (sig_vec& newInputs)
{
    for (int c = 0; c < inputs.size(); c++)
    {
        if (c < newInputs.size())
            inputs[c].setSignal(newInputs[c]);
        else
            inputs[c].setSignalToDefault();
    }
}


//========================================================================
// AudioBuffer
//========================================================================
AudioBuffer::AudioBuffer (const string& ID) : AudioModule(ID)
{
    inputs.push_back(AudioInput(0.0f));
    
    recording = OFF;
}

//========================================================================
void AudioBuffer::record (tick size)
{
    allocate(size);
    
    recording = WAIT;
}

//========================================================================
void AudioBuffer::process (Clock& clock)
{
    for (tick t = 0; t < clock.size; t++)
    {
        // TODO: check buffer latency
        if (recording == WAIT)
        {
            if (clock[t] % clock.barLength[t] < BUFFERSIZE)
            {
                rec_start = clock[t];
                recording = ON;
            }
        }
        
        if (recording == ON && clock[t] > rec_start + BUFFERSIZE)
        {
            // Get pointer
            tick pointer = clock[t] - rec_start - BUFFERSIZE;
            
            
            // Get envelope
            float envelope = 1.0f;
            
            if (pointer < FADE_SIZE)
                envelope = sqrtf(pointer / FADE_SIZE);
            
            if (size() - pointer < FADE_SIZE)
                envelope = sqrtf((size() - pointer) / FADE_SIZE);
                
                
            // Write input to output
            if (pointer < size())
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
