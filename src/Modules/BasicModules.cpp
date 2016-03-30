//
//  BasicModules.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 16/11/15.
//
//

#include "Modules.h"


//========================================================================
// click_Module (bpm, bpb)
//========================================================================
click_Module::click_Module (const string& ID) : AudioModule(ID)
{
    inputs.push_back(AudioInput(120.0f)); // beats per minute
    inputs.push_back(AudioInput(  4.0f)); // beats per bar
}

void click_Module::process (Clock& clock)
{
    for (tick t = 0; t < clock.size; t++)
    {
        clock.beatLength[t] = 60.0f / inputs[0][t].L * SAMPLERATE;
        clock.barLength[t]  = inputs[1][t].L * clock.beatLength[t];
        
        if (clock.beatLength[t] == 0) clock.beatLength[t] = 1;
        if (clock.barLength[t]  == 0) clock.barLength[t]  = 1;
    }
    
    // Set beat time for visual feedback
    tick clock_p = clock.size - 1;
    tick pointer = clock[clock_p] % clock.barLength[clock_p] % clock.beatLength[clock_p];
    beatTime = (float)pointer / clock.beatLength[clock_p];
}


//========================================================================
// operator_Module (operand, operand, ...)
//========================================================================
operator_Module::operator_Module (const string& ID, char op) : AudioModule(ID)
{
    this->op = op;
}

void operator_Module::setInputs (sig_vec& newInputs)
{
    if (inputs.size() >= newInputs.size())
    {
        for (int c = 0; c < inputs.size(); c++)
        {
            if (c < newInputs.size())
                inputs[c].setSignal(newInputs[c]);
            else
                inputs[c].setSignalToDefault();
        }
    }
    else
    {
        for (int c = 0; c < newInputs.size(); c++)
        {
            if (c < inputs.size())
            {
                inputs[c].setSignal(newInputs[c]);
            }
            else
            {
                switch (op)
                {
                    case '*':
                    case '/':
                        inputs.push_back(AudioInput(1.0f));
                        break;
                        
                    default:
                        inputs.push_back(AudioInput(0.0f));
                        break;
                }
                
                inputs.back().setSignal(newInputs[c]);
            }
        }
    }
}
    
void operator_Module::process (Clock& clock)
{
    if (inputs.size() > 0)
    {
        switch (op)
        {
            case '+':
                for (tick t = 0; t < clock.size; t++)
                {
                    output[t] = inputs[0][t];
                    
                    for (int c = 1; c < inputs.size(); c++)
                    {
                        output[t].L += inputs[c][t].L;
                        output[t].R += inputs[c][t].R;
                    }
                }
                break;
                
            case '-':
                for (tick t = 0; t < clock.size; t++)
                {
                    output[t] = inputs[0][t];
                    
                    for (int c = 1; c < inputs.size(); c++)
                    {
                        output[t].L -= inputs[c][t].L;
                        output[t].R -= inputs[c][t].R;
                    }
                }
                break;
                
            case '*':
                for (tick t = 0; t < clock.size; t++)
                {
                    output[t] = inputs[0][t];
                    
                    for (int c = 1; c < inputs.size(); c++)
                    {
                        output[t].L *= inputs[c][t].L;
                        output[t].R *= inputs[c][t].R;
                    }
                }
                break;
                
            case '/':
                for (tick t = 0; t < clock.size; t++)
                {
                    output[t] = inputs[0][t];
                    
                    for (int c = 1; c < inputs.size(); c++)
                    {
                        output[t].L /= inputs[c][t].L;
                        output[t].R /= inputs[c][t].R;
                    }
                }
                break;
                
            default:
                break;
        }
    }
    else
    {
        for (tick t = 0; t < clock.size; t++)
            output[t] = 0.0f;
    }
}


//========================================================================
// loop_Module (buffer, beat, bar, start)
//========================================================================
loop_Module::loop_Module (const string& ID) : AudioModule(ID)
{
    inputs.push_back(AudioInput(0.0f)); // buffer
    inputs.push_back(AudioInput(4.0f)); // beat
    inputs.push_back(AudioInput(8.0f)); // bar
    inputs.push_back(AudioInput(0.0f)); // start
}

void loop_Module::process (Clock& clock)
{
    tick bufferSize  = inputs[0].getSignal()->size();
    tick bufferStart = inputs[0].getSignal()->start();
    tick beat, bar, start;
    
    for (tick t = 0; t < clock.size; t++)
    {
        beat  = inputs[1][t].L * clock.beatLength[t];
        bar   = inputs[2][t].L * clock.beatLength[t];
        start = inputs[3][t].L * clock.beatLength[t];
        
        if (beat == 0) beat = 1;
        if (bar  == 0) bar  = 1;
        
        tick pointer = (clock[t] - bufferStart - start + bar) % bar % beat;
        
        if (pointer < bufferSize)
        {
            output[t].L = inputs[0][pointer].L;
            output[t].R = inputs[0][pointer].R;
        }
        else
        {
            output[t] = 0.0f;
        }
    }
    
    // Set beat time for visual feedback
    tick pointer = (clock[clock.size - 1] - bufferStart - start + bar) % bar % beat;
    beatTime = (float)pointer / beat;
}


//========================================================================
// crush_Module (input, bitdepth)
//========================================================================
crush_Module::crush_Module (const string& ID) : AudioModule(ID)
{
    inputs.push_back(AudioInput(0.0f)); // input
    inputs.push_back(AudioInput(8.0f)); // bitdepth
}

void crush_Module::process (Clock& clock)
{
    for (tick t = 0; t < clock.size; t++)
    {
        float crushL = inputs[1][t].L;
        float crushR = inputs[1][t].R;
        
        output[t].L = int(inputs[0][t].L * crushL) / crushL;
        output[t].R = int(inputs[0][t].R * crushR) / crushR;
    }
}


//========================================================================
// comp_Module (input, sidechain, attack, release)
//========================================================================
comp_Module::comp_Module (const string& ID) : AudioModule(ID)
{
    inputs.push_back(AudioInput(0.0f));      // input
    inputs.push_back(AudioInput(0.0f));      // sidechain
    inputs.push_back(AudioInput(0.001f));    // attack
    inputs.push_back(AudioInput(0.000001f)); // release
    
    targetRMS  = 0.0f;
    currentRMS = 0.0f;
}

void comp_Module::process (Clock& clock)
{
    // Get sidechain RMS
    sample sidechainRMS = inputs[1].getSignal()->getRMS();
    
    
    // Walk samples
    for (tick t = 0; t < clock.size; t++)
    {
        // Update target RMS
        float factor = (float)t / clock.size;
        targetRMS.L = (1.0f - factor) * targetRMS.L + factor * sidechainRMS.L;
        targetRMS.R = (1.0f - factor) * targetRMS.R + factor * sidechainRMS.R;
        
        
        // Get attack and release
        sample attack  = inputs[2][t];
        sample release = inputs[3][t];
        
        
        // Update current RMS
        if (targetRMS.L >= currentRMS.L)
            currentRMS.L = (1.0f - attack.L)  * currentRMS.L + attack.L  * targetRMS.L;
        else
            currentRMS.L = (1.0f - release.L) * currentRMS.L + release.L * targetRMS.L;
        
        if (targetRMS.R >= currentRMS.R)
            currentRMS.R = (1.0f - attack.R)  * currentRMS.R + attack.R  * targetRMS.R;
        else
            currentRMS.R = (1.0f - release.R) * currentRMS.R + release.R * targetRMS.R;
        
        
        // Clip current RMS
        if (currentRMS.L > 1.0f) currentRMS.L = 1.0f;
        if (currentRMS.R > 1.0f) currentRMS.R = 1.0f;
        
        
        // Compress input to output
        output[t].L = inputs[0][t].L * (1.0f - currentRMS.L);
        output[t].R = inputs[0][t].R * (1.0f - currentRMS.R);
    }
}


//========================================================================
// pitch_Module (input, pitch)
//========================================================================
pitch_Module::pitch_Module (const string& ID) : AudioModule(ID), buffer(0.0f)
{
    inputs.push_back(AudioInput(0.0f)); // input
    inputs.push_back(AudioInput(1.0f)); // pitch
    
    buffer.allocate(SAMPLERATE);
    
    pointer = 0;
    phasor  = 0.0f;
}

pitch_Module::~pitch_Module()
{
    buffer.deallocate();
}

void pitch_Module::process (Clock& clock)
{
    // Walk samples
    for (tick t = 0; t < clock.size; t++)
    {
        // Get frequency
        float pitch  = (inputs[1][t].L + inputs[1][t].R) / 2.0f;
        float window = sqrtf(0.5f / pitch) * 0.1f;
        float freq   = (-pitch + 1.0f) / window;
        
        
        // Update phasor
        phasor.L = fmodf(phasor.L + 1.0f + freq / SAMPLERATE, 1.0f);
        phasor.R = fmodf(phasor.L + 0.5f, 1.0f);
        
        
        // Get delay
        sample delay;
        delay.L = fmodf(pointer - phasor.L * window * SAMPLERATE + buffer.size(), buffer.size());
        delay.R = fmodf(pointer - phasor.R * window * SAMPLERATE + buffer.size(), buffer.size());
        
        
        // Get envelope
        sample envelope;
        envelope.L = sqrtf(fabsf(fabsf(phasor.L * 2.0f - 1.0f) - 1.0f));
        envelope.R = sqrtf(fabsf(fabsf(phasor.R * 2.0f - 1.0f) - 1.0f));
        
        
        // Write input to buffer
        buffer[pointer] = inputs[0][t];
        
        
        // Write buffer to output
        sample value = buffer.getValue(delay);
        value.L *= envelope.L;
        value.R *= envelope.R;
        output[t].L = value.L + value.R * envelope.R;
        output[t].R = value.R + value.L * envelope.L;
        
       
        // Update buffer pointer
        pointer = (pointer + 1) % buffer.size();
    }
}
