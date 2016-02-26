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
    memory = NULL;
    
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

//========================================================================
void AudioEngine::setMemoryPointer (Memory** memory)
{
    this->memory = memory;
}

//========================================================================
void AudioEngine::audioIn (sample* input, tick size, int channels)
{
    if (memory)
    if (*memory)
    {
        // Write input to ADC
        for (int c = 0; c < 2; c++)//(int c = CHANNEL_INPUT; c < CHANNEL_CLICK; c++)
        {
            Signal& adc = *(*memory)->getADC()->getOutput(c);// - CHANNEL_INPUT);
            
            for (tick t = 0; t < size; t++)
                adc[t] = input[t * channels + c];
        }
    }
}

void AudioEngine::audioOut (sample* output, tick size, int channels)
{
    if (memory)
    if (*memory)
    {
        // Process clock and click
        processClockAndClick();
        
        // Process buffers
        (*memory)->processBuffers(clock);
        
        // Process DAC
        (*memory)->getDAC()->processModule(clock);
        
        // Write click to output
//        for (int c = 2; c < 4; c++)//(int c = CHANNEL_CLICK; c < CHANNEL_OUTPUT; c++)
//        {
//            for (tick t = 0; t < size; t++)
//                output[t * channels + c] = click[t];
//        }
        
        // Write DAC to output
        for (int c = 0; c < 2; c++)//(int c = CHANNEL_OUTPUT; c < CHANNEL_SIZE; c++)
        {
            Signal& dac = *(*memory)->getDAC()->getInput(c);// - CHANNEL_OUTPUT);
            
            for (tick t = 0; t < size; t++)
                output[t * channels + c] = dac[t] + click[t];
        }
    }
}

//========================================================================
void AudioEngine::processClockAndClick()
{
    clock.clock++;
    
    if (memory)
    if (*memory)
    {
        clock.beatLength = (*memory)->getBeatLength();
        clock.barLength  = (*memory)->getBarLength();
    }
    
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
