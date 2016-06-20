//
//  Memory.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 16/11/15.
//
//

#include "Syntax.h"


//========================================================================
AudioModule* Memory::addModule (const string& module, const string& ID)
{
    AudioModule* m = NULL;
    
         if (module == "click") m = new    click_Module(ID);
    else if (module == "+")     m = new operator_Module(ID, '+');
    else if (module == "-")     m = new operator_Module(ID, '-');
    else if (module == "*")     m = new operator_Module(ID, '*');
    else if (module == "/")     m = new operator_Module(ID, '/');
    else if (module == "loop")  m = new     loop_Module(ID);
    else if (module == "crush") m = new    crush_Module(ID);
    else if (module == "comp")  m = new     comp_Module(ID);
    else if (module == "pitch") m = new    pitch_Module(ID);
    else if (module == "delay") m = new    delay_Module(ID);
    else if (module == "pan")   m = new      pan_Module(ID);
    //else if (module == "vocod") m = new    vocod_Module(ID);
    
    if (m)
    {
        modules.push_back(m);
        moduleStrings.push_back(module + CHAR_TYPE_MOD_ID + ID);
    }
    
    return m;
}

AudioBuffer* Memory::addBuffer (const string& buffer, const string& ID)
{
    AudioBuffer* b = NULL;
    
    if (buffer == "buf") b = new AudioBuffer(ID);
    
    if (b)
    {
        buffers.push_back(b);
        bufferStrings.push_back(buffer + CHAR_TYPE_BUF_ID + ID);
    }
    
    return b;
}

//========================================================================
Memory::Memory (int inputChannels) : click(sample())
{
    // Init clock and click
    clock.clock = 0;
    clock.size  = BUFFERSIZE;
    
    clock.clockTime  = new tick[clock.size];
    clock.beatLength = new tick[clock.size];
    clock.barLength  = new tick[clock.size];
    
    for (tick t = 0; t < clock.size; t++)
    {
        clock.clockTime[t]  = t;
        clock.beatLength[t] = SAMPLERATE / 2;
        clock.barLength[t]  = SAMPLERATE * 2;
    }
    
    click.allocate(clock.size);
    
    
    // Init ADC and DAC
    for (int c = 0; c < inputChannels; c++)
    {
        adc.push_back(new AudioSignal(0.0f));
        adc[c]->allocate(clock.size);
    }
    
    dac = new operator_Module("dac", '+');
    
    
    // Init ID count
    moduleIDCount = 0;
    bufferIDCount = 0;
}

Memory::~Memory()
{
    // Delete clock and click
    delete[] clock.clockTime;
    delete[] clock.beatLength;
    delete[] clock.barLength;
    
    click.deallocate();
    
    
    // Delete ADC and DAC
    for (int c = 0; c < adc.size(); c++)
        adc[c]->deallocate();
    adc.clear();
    
    delete dac;
    
    
    // Delete modules and buffers
    for (int m = 0; m < modules.size(); m++)
        delete modules[m];
    modules.clear();
    
    for (int b = 0; b < buffers.size(); b++)
        delete buffers[b];
    buffers.clear();
    
    
    // Clear module and buffer strings
    moduleStrings.clear();
    bufferStrings.clear();
}

//========================================================================
void Memory::audioIn (float* input, int size, int channels)
{
    // Write input to ADC
    for (int c = 0; c < adc.size() && c < channels; c++)
        for (tick t = 0; t < clock.size && t < size; t++)
            (*adc[c])[t].L = (*adc[c])[t].R = input[t * channels + c] * 0.5f;
}

void Memory::audioOut (float* output, int size, int channels)
{
    // Process clock and click
    processClockAndClick();
    
    
    // Process DAC
    dac->processSignal(clock);
    
    
    // Write DAC to output
    switch (channels)
    {
        case 0:
            break;
            
        case 1:
            for (tick t = 0; t < clock.size && t < size; t++)
            {
                output[t * channels + 0] = (*dac)[t].L + click[t].L;
            }
            break;
            
        case 2:
            for (tick t = 0; t < clock.size && t < size; t++)
            {
                output[t * channels + 0] = (*dac)[t].L + click[t].L;
                output[t * channels + 1] = (*dac)[t].R + click[t].R;
            }
            break;
            
        case 3:
            for (tick t = 0; t < clock.size && t < size; t++)
            {
                output[t * channels + 0] = (*dac)[t].L;
                output[t * channels + 1] = (*dac)[t].R;
                output[t * channels + 2] = (*dac)[t].L + click[t].L;
            }
            break;
            
        default:
            for (tick t = 0; t < clock.size && t < size; t++)
            {
                output[t * channels + 0] = (*dac)[t].L;
                output[t * channels + 1] = (*dac)[t].R;
                output[t * channels + 2] = (*dac)[t].L + click[t].L;
                output[t * channels + 3] = (*dac)[t].R + click[t].R;
            }
            break;
    }
}

//========================================================================
Clock& Memory::getClock()
{
    return clock;
}

//========================================================================
AudioSignal* Memory::getADC (int channel)
{
    if (channel >= 0 && channel < adc.size())
        return adc[channel];
    
    return NULL;
}

AudioModule* Memory::getDAC()
{
    return dac;
}

//========================================================================
AudioModule* Memory::getModule (const string& ID)
{
    for (int m = 0; m < modules.size(); m++)
        if (modules[m]->getID() == ID)
            return modules[m];
    
    return NULL;
}

AudioBuffer* Memory::getBuffer (const string& ID)
{
    for (int b = 0; b < buffers.size(); b++)
        if (buffers[b]->getID() == ID)
            return buffers[b];
    
    return NULL;
}

//========================================================================
StringVector& Memory::getModuleStrings()
{
    return moduleStrings;
}

StringVector& Memory::getBufferStrings()
{
    return bufferStrings;
}

//========================================================================
int Memory::getNewModuleID()
{
    return moduleIDCount++;
}

int Memory::getNewBufferID()
{
    return bufferIDCount++;
}

//========================================================================
void Memory::processClockAndClick()
{
    clock.clock++;
    
    tick clockStart = clock[clock.size - 1] + 1;
    
    for (tick t = 0; t < clock.size; t++)
    {
        clock.clockTime[t] = clockStart + t;
        
        tick barClock = clock[t] % clock.barLength[t];
        
        float freq = barClock / clock.beatLength[t];
        if (freq < 1.0f) freq = 1000.0f;
        else             freq = 500.0f;
        
        float osc = sinf(clock[t] * freq / SAMPLERATE * TWO_PI);
        
        float amp = 1.0f - float(barClock % clock.beatLength[t]) / SAMPLERATE * 100.0f;
        if (amp < 0.0f) amp = 0.0f;
        
        click[t].L = osc * amp * 0.25f;
        click[t].R = osc * amp * 0.25f;
    }
}
