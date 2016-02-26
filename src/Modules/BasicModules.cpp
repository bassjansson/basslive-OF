//
//  BasicModules.cpp
//  BassLive
//
//  Created by Bass Jansson on 16/11/15.
//
//

#include "BasicModules.h"


//========================================================================
// loop_Module
//========================================================================
loop_Module::loop_Module (string ID) : AudioModule(ID, 3, 1)
{
    buffer = NULL;
}

void loop_Module::setBuffer (AudioBuffer* buffer)
{
    this->buffer = buffer;
}

void loop_Module::process (SignalVec& inputs, SignalVec& outputs, Clock clock)
{
    if (buffer)
    {
        for (tick t = 0; t < clock.size; t++)
        {
            tick beat  = inputs[0][t] * clock.beatLength;
            tick bar   = inputs[1][t] * clock.beatLength;
            tick start = inputs[2][t] * clock.beatLength;
            
            tick pointer = ((clock[t] - buffer->getStart()) % bar - start) % beat;
            
            for (int c = 0; c < outputs.size(); c++)
                outputs[c][t] = buffer->read(pointer, c, clock);
        }
    }
}


//========================================================================
// add_Module
// mul_Module
// sub_Module
// div_Module
//========================================================================
add_Module::add_Module (string ID) : AudioModule(ID, OPERATOR_MAX_ARGS, 1) {}
mul_Module::mul_Module (string ID) : AudioModule(ID, OPERATOR_MAX_ARGS, 1) {}
sub_Module::sub_Module (string ID) : AudioModule(ID, 2, 1) {}
div_Module::div_Module (string ID) : AudioModule(ID, 2, 1) {}

void add_Module::process (SignalVec& inputs, SignalVec& outputs, Clock clock)
{
    for (tick t = 0; t < clock.size; t++)
    {
        outputs[0][t] = 0.0f;
        
        for (int c = 0; c < inputs.size(); c++)
            outputs[0][t] += inputs[c][t];
    }
}

void mul_Module::process (SignalVec& inputs, SignalVec& outputs, Clock clock)
{
    for (tick t = 0; t < clock.size; t++)
    {
        outputs[0][t] = 1.0f;
        
        for (int c = 0; c < inputs.size(); c++)
            outputs[0][t] *= inputs[c][t];
    }
}

void sub_Module::process (SignalVec& inputs, SignalVec& outputs, Clock clock)
{
    for (tick t = 0; t < clock.size; t++)
        outputs[0][t] = inputs[0][t] - inputs[1][t];
}

void div_Module::process (SignalVec& inputs, SignalVec& outputs, Clock clock)
{
    for (tick t = 0; t < clock.size; t++)
        outputs[0][t] = inputs[0][t] / inputs[1][t];
}
