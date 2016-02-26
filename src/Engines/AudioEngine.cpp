//
//  AudioEngine.cpp
//  BassLive
//
//  Created by Bass Jansson on 16/11/15.
//
//

#include "AudioEngine.h"


//========================================================================
AudioEngine::AudioEngine()
{
    clock.clock = 0;
    clock.size  = BUFFERSIZE;
    
    clock.beatLength = SAMPLERATE / 2;
    clock.barLength  = clock.beatLength * 4;

    clock.buffer = new   tick[clock.size];
    click        = new sample[clock.size];
    
    for (tick t = 0; t < clock.size; t++)
    {
        clock.buffer[t] = t;
        click[t] = 0.0f;
    }    
}

AudioEngine::~AudioEngine()
{
    delete[] clock.buffer;
    delete[] click;
}

void AudioEngine::audioOut (MainFunction* mf, sig output, tick size, int channels)
{
    if (mf)
    {
        // Process clock and click
        processClockAndClick();
        
        // Write DAC to output
        sig dac;
        mf->process(dac, clock);
        for (int c = 0; c < channels; c++)
            for (tick t = 0; t < size; t++)
                output[t * channels + c] = dac[t] + click[t];
    }
}

//========================================================================
void AudioEngine::processClockAndClick()
{
    clock.clock++;
    
//    clock.beatLength = (*memory)->getBeatLength();
//    clock.barLength  = (*memory)->getBarLength();
    
    tick clockStart = clock[clock.size - 1] + 1;
    
    for (tick t = 0; t < clock.size; t++)
    {
        clock.buffer[t] = clockStart + t;
        
        sample freq = clock[t] % clock.barLength / clock.beatLength;
        if (freq < 1.0f) freq = 1000.0f;
        else freq = 500.0f;
        
        sample osc = sinf(clock[t] * freq / SAMPLERATE * TWO_PI);
        
        sample amp = 1.0f - sample(clock[t] % clock.beatLength) / SAMPLERATE * 100.0f;
        if (amp < 0.0f) amp = 0.0f;
        
        click[t] = osc * amp * 0.5f;
    }
}
