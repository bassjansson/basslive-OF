//
//  Module.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 29/02/16.
//
//

#include "Modules.h"


//========================================================================
AudioBuffer::AudioBuffer()
{
    buffer = NULL;
    size   = 0;
    start  = 0;
    
    recording = OFF;
}

AudioBuffer::~AudioBuffer()
{
    if (buffer) delete[] buffer;
}

//========================================================================
tick AudioBuffer::getSize()
{
    return size;
}

tick AudioBuffer::getStart()
{
    return start;
}

void AudioBuffer::record (tick size)
{
    buffer = new sample[size];
    for (tick t = 0; t < size; t++)
        buffer[t] = 0.0f;
    
    this->size = size;
    
    recording = WAIT;
}

sample AudioBuffer::read (tick_f pointer)
{
    if (recording != ON)
    {
        if (pointer >= 0.0f && pointer < size - 1)
        {
            tick pointer_i = tick(pointer);
            sample diff = pointer - pointer_i;
            
            return (   (1.0f - diff) * buffer[pointer_i + 0]
                    +  (       diff) * buffer[pointer_i + 1]);
        }
    }
    
    return 0.0f;
}

//========================================================================
void AudioBuffer::process (sig_vec& inputs, buf_vec& buffers, sig output, Clock clock)
{
    sig input;
    if (inputs.size() > 0)
        input = inputs[0];
    else
        input = clock.null;
    
        
    for (tick t = 0; t < BUFFERSIZE; t++)
    {
        if (recording == WAIT)
        {
            if (clock[t] % clock.barLength < SAMPLERATE / 1000)
            {
                start = clock[t] - BUFFERSIZE; // TODO
                recording = ON;
            }
        }
        
        if (recording == ON)
        {
            tick pointer = clock[t] - start;
            
            if (pointer < size)
                buffer[pointer] = input[t];
            else
                recording = OFF;
        }
    }
}
