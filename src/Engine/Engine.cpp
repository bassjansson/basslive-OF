//
//  Engine.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 07/12/15.
//
//

#include "Engine.hpp"


//========================================================================
void Engine::setup()
{
    mouseIsPressed = false;
    
    // Init clock and click
    clock.clock = 0;
    clock.size  = BUFFERSIZE;
    
    clock.clockTime  = new tick[clock.size];
    clock.beatLength = new tick[clock.size];
    clock.barLength  = new tick[clock.size];
    
    click = new sample[clock.size];
    
    for (tick t = 0; t < clock.size; t++)
    {
        clock.clockTime[t]  = t;
        clock.beatLength[t] = SAMPLERATE / 2;
        clock.barLength[t]  = SAMPLERATE * 2;
        
        click[t] = sample();
    }
}

void Engine::exit()
{
    delete[] clock.clockTime;
    delete[] clock.beatLength;
    delete[] clock.barLength;
    delete[] click;
}

void Engine::update()
{
    // Temporary bugfix of mouseReleased()
    if (mouseIsPressed && !ofGetMousePressed())
        mouseReleased(ofGetMouseX(), ofGetMouseY(), OF_MOUSE_BUTTON_LEFT);
}

void Engine::draw()
{
    ofBackground(50);

    tabbedPages.draw();
}

//========================================================================
void Engine::audioIn (float* input, int size, int channels)
{
    MainFunction* mf = (MainFunction*)tabbedPages.getActiveTab();
    
    if (mf)
    {
        // Write input to ADC
        sig adc = mf->getADC(0);
        
        for (tick t = 0; t < size; t++)
        {
            adc[t].L = input[t * channels + 0];
            adc[t].R = input[t * channels + 0];
        }
    }
}

void Engine::audioOut (float* output, int size, int channels)
{    
    MainFunction* mf = (MainFunction*)tabbedPages.getActiveTab();
    
    if (mf)
    {
        // Process clock and click
        processClockAndClick();
        
        // Write DAC to output
        sig dac;
        buf dacbuf;
        
        mf->process(&dacbuf, &dac, clock);
        
        for (tick t = 0; t < size; t++)
        {
            output[t * channels + 0] = dac[t].L + click[t].L;
            output[t * channels + 1] = dac[t].R + click[t].R;
            
//            output[t * channels + 2] = click[t].L;
//            output[t * channels + 3] = click[t].R;
        }
    }
}

void Engine::mousePressed (float x, float y, int button)
{
    ((MainFunction*)tabbedPages.getActiveTab())->mousePressed(x, y, button);
    
    mouseIsPressed = true;
}

void Engine::mouseReleased (float x, float y, int button)
{
    ((MainFunction*)tabbedPages.getActiveTab())->mouseReleased(x, y, button);
    
    mouseIsPressed = false;
}

void Engine::keyPressed (int key)
{
    ((MainFunction*)tabbedPages.getActiveTab())->keyPressed(key);
    
    if (ofGetKeyPressed(OF_KEY_COMMAND) && key == 't')
        newPage();
}

void Engine::windowResized()
{
    tabbedPages.setSize(EDITOR_WIDTH, EDITOR_HEIGHT + FONT_SIZE * 2);
    
    for (int i = 0; i < pages.size(); i++)
        pages[i]->setSize(EDITOR_WIDTH, EDITOR_HEIGHT);
}

//========================================================================
void Engine::newPage()
{
    pages.push_back(new MainFunction("#" + ofToString(pages.size() + 1)));
    tabbedPages.add(pages.back());
    tabbedPages.setActiveTab(pages.size() - 1);
    windowResized();
}

void Engine::processClockAndClick()
{
    clock.clock++;
    
    tick clockStart = clock[clock.size - 1] + 1;
    
    for (tick t = 0; t < clock.size; t++)
    {
        clock.clockTime[t] = clockStart + t;
        
        float freq = clock[t] % clock.barLength[t] / clock.beatLength[t];
        if (freq < 1.0f) freq = 1000.0f;
        else freq = 500.0f;
        
        float osc = sinf(clock[t] * freq / SAMPLERATE * TWO_PI);
        
        float amp = 1.0f - float(clock[t] % clock.beatLength[t]) / SAMPLERATE * 100.0f;
        if (amp < 0.0f) amp = 0.0f;
        
        click[t].L = osc * amp * 0.5f;
        click[t].R = osc * amp * 0.5f;
    }
}
