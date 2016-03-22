//
//  BasicModules.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 16/11/15.
//
//

#include "Modules.h"


//========================================================================
// click_Module
//========================================================================
click_Module::click_Module (const string& ID) : AudioModule(ID, 2)
{
    
}

void click_Module::process (Clock& clock)
{
    for (tick t = 0; t < clock.size; t++)
    {
        clock.beatLength[t] = 60.0f / inputs[0][t].L * SAMPLERATE;
        clock.barLength[t]  = inputs[1][t].L * clock.beatLength[t];
    }
}


//========================================================================
// operator_Module
//========================================================================
operator_Module::operator_Module (const string& ID, char op) : AudioModule(ID, MAX_NUM_INPUTS)
{
    this->op = op;
}
    
void operator_Module::process (Clock& clock)
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


//========================================================================
// loop_Module
//========================================================================
loop_Module::loop_Module (const string& ID) : AudioModule(ID, 4)
{
   
}

void loop_Module::process (Clock& clock)
{
    for (tick t = 0; t < clock.size; t++)
    {
        tick beat  = tick(inputs[1][t].L * clock.beatLength[t]) + 1;
        tick bar   = tick(inputs[2][t].L * clock.beatLength[t]) + 1;
        tick start = tick(inputs[3][t].L * clock.beatLength[t]);
        
        tick pointer = ((clock[t] - inputs[0].start()) % bar - start) % beat;
        
        if (pointer < inputs[0].size())
        {
            output[t].L = inputs[0][pointer].L;
            output[t].R = inputs[0][pointer].R;
        }
        else
        {
            output[t] = sample();
        }
    }
}
