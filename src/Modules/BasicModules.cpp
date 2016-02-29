//
//  BasicModules.cpp
//  BassLive
//
//  Created by Bass Jansson on 16/11/15.
//
//

#include "Modules.h"


//========================================================================
// loop_Module
//========================================================================
void loop_Module::process (sig_vec& inputs, buf_vec& buffers, sig output, Clock clock)
{
    if (buffers.size() > 0)
    {
        buf buffer = buffers[0];
        sig beats, bars, starts;
        beats = bars = starts = clock.null;
        
        if (inputs.size() > 0)
        {
            beats = inputs[0];
            
            if (inputs.size() > 1)
            {
                bars = inputs[1];
                
                if (inputs.size() > 2)
                {
                    starts = inputs[2];
                }
            }
        }
        
        for (tick t = 0; t < BUFFERSIZE; t++)
        {
            tick beat  = beats[t]  * clock.beatLength;
            tick bar   = bars[t]   * clock.beatLength;
            tick start = starts[t] * clock.beatLength;
            
            tick pointer = ((clock[t] - buffer->getStart()) % bar - start) % beat;
            
            output[t] = buffer->read(pointer);
        }
    }
    else
    {
        for (tick t = 0; t < BUFFERSIZE; t++)
            output[t] = 0.0f;
    }
}


//========================================================================
// add_Module
// sub_Module
// mul_Module
// div_Module
//========================================================================
void add_Module::process (sig_vec& inputs, buf_vec& buffers, sig output, Clock clock)
{
    for (tick t = 0; t < BUFFERSIZE; t++)
    {
        output[t] = 0.0f;
        
        for (int c = 0; c < inputs.size(); c++)
            output[t] += inputs[c][t];
    }
}

void sub_Module::process (sig_vec& inputs, buf_vec& buffers, sig output, Clock clock)
{
    for (tick t = 0; t < BUFFERSIZE; t++)
    {
        output[t] = 0.0f;
        
        for (int c = 0; c < inputs.size(); c++)
            output[t] -= inputs[c][t];
    }
}

void mul_Module::process (sig_vec& inputs, buf_vec& buffers, sig output, Clock clock)
{
    for (tick t = 0; t < BUFFERSIZE; t++)
    {
        output[t] = 1.0f;
        
        for (int c = 0; c < inputs.size(); c++)
            output[t] *= inputs[c][t];
    }
}

void div_Module::process (sig_vec& inputs, buf_vec& buffers, sig output, Clock clock)
{
    for (tick t = 0; t < BUFFERSIZE; t++)
    {
        output[t] = 1.0f;
        
        for (int c = 0; c < inputs.size(); c++)
            output[t] /= inputs[c][t];
    }
}
