//
//  Memory.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 16/11/15.
//
//

#include "Memory.h"


//========================================================================
Memory::Memory()
{
    modules.push_back(new AudioModule("adc", 0, 2));//0, CHANNEL_CLICK - CHANNEL_INPUT));
    modules.push_back(new AudioModule("dac", 2, 0));//CHANNEL_SIZE - CHANNEL_OUTPUT, 0));
    
    beatLength = SAMPLERATE / 2;
    barLength  = beatLength * 4;
    
    sidCount = 0;
}

Memory::~Memory()
{
    for (int m = 0; m < modules.size(); m++)
        delete modules[m];
    modules.clear();
    
    for (int b = 0; b < buffers.size(); b++)
        delete buffers[b];
    buffers.clear();
}

//========================================================================
AudioModule* Memory::getADC()
{
    return modules[0];
}

AudioModule* Memory::getDAC()
{
    return modules[1];
}

//========================================================================
AudioModule* Memory::getAudioModule (string ID)
{
    for (int m = 0; m < modules.size(); m++)
        if (modules[m]->getID() == ID)
            return modules[m];
    
    return NULL;
}

void Memory::addAudioModule (AudioModule* module)
{
    modules.push_back(module);
}

//========================================================================
AudioBuffer* Memory::getAudioBuffer (string ID)
{
    for (int b = 0; b < buffers.size(); b++)
        if (buffers[b]->getID() == ID)
            return buffers[b];

    return NULL;
}

void Memory::addAudioBuffer (AudioBuffer* buffer)
{
    buffers.push_back(buffer);
}

void Memory::processBuffers (Clock& clock)
{
    for (int b = 0; b < buffers.size(); b++)
        buffers[b]->processModule(clock);
}

//========================================================================
void Memory::setBeatsPerMinute (beat bpm)
{
    beatLength = 60.0f / bpm * SAMPLERATE;
}

void Memory::setBeatsPerBar (beat bpb)
{
    barLength = bpb * beatLength;
}

//========================================================================
tick Memory::getBeatLength()
{
    return beatLength;
}

tick Memory::getBarLength()
{
    return barLength;
}

//========================================================================
string Memory::getNewSID()
{
    string sid = "id" + ofToString(sidCount);
    sidCount++;
    return sid;
}
