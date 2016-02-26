//
//  AudioBuffer.cpp
//  BassLive
//
//  Created by Bass Jansson on 25/11/15.
//
//

#include "AudioBuffer.h"


//========================================================================
AudioBuffer::AudioBuffer (string ID) : AudioModule(ID, 1, 0)
{
    start = 0;
    
    for (int c = 0; c < 1; c++)
        buffers.push_back(Signal(0.0f));
    
    recording = OFF;
}

AudioBuffer::~AudioBuffer()
{
    for (int c = 0; c < buffers.size(); c++)
        buffers[c].deallocate();
    buffers.clear();
}

//========================================================================
tick AudioBuffer::getSize()
{
    return buffers[0].size();
}

tick AudioBuffer::getStart()
{
    return start;
}

void AudioBuffer::record (tick size)
{
    for (int c = 0; c < buffers.size(); c++)
        buffers[c].allocate(size);
    
    recording = WAIT;
}

sample AudioBuffer::read (tick_f pointer, int channel, Clock& clock)
{
    if (recording != ON)
    {
        if (channel >= 0 && channel < buffers.size())
        {
            if (pointer >= 0.0f && pointer < getSize() - 1)
            {
                tick pointer_i = tick(pointer);
                sample diff = pointer - pointer_i;
                
                return (   (1.0f - diff) * buffers[channel][pointer_i + 0]
                        +  (       diff) * buffers[channel][pointer_i + 1]);
            }
        }
    }
    
    return 0.0f;
}

//========================================================================
void AudioBuffer::process (SignalVec& inputs, SignalVec& outputs, Clock clock)
{
    for (tick t = 0; t < clock.size; t++)
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
            
            if (pointer < getSize())
                for (int c = 0; c < buffers.size(); c++)
                    buffers[c][pointer] = inputs[c][t];
            else
                recording = OFF;
        }
    }
}
