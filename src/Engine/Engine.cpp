//
//  Editor.cpp
//  BassLive
//
//  Created by Bass Jansson on 07/12/15.
//
//

#include "Engine.hpp"


//========================================================================
void Engine::setup()
{
    mouseIsPressed = false;
    
    tabbedPages.setup();
    
    tabbedPages.setDefaultBackgroundColor(ofColor(10, 12, 20));
    tabbedPages.setDefaultBorderColor(ofColor(30, 32, 40));
    tabbedPages.setDefaultHeaderBackgroundColor(ofColor(50, 52, 60));
    tabbedPages.setDefaultFillColor(ofColor(70, 72, 80));
    tabbedPages.setDefaultTextColor(ofColor(100, 156, 240));
    
    tabbedPages.loadFont("fonts/Menlo-Bold.ttf", FONT_SIZE);
    tabbedPages.setShowHeader(false);
    tabbedPages.setTabWidth(FONT_SIZE * 6);
    tabbedPages.setTabHeight(FONT_SIZE * 2);
    tabbedPages.setDefaultWidth(FONT_SIZE * 12);
    tabbedPages.setDefaultHeight(FONT_SIZE * 2);
    tabbedPages.setShape(0, 0, EDITOR_WIDTH, EDITOR_HEIGHT + FONT_SIZE * 2);
    
    newPage();
    
    // Init click and clock
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

void Engine::exit()
{
    for (int i = 0; i < pages.size(); i++)
        delete pages[i];
    pages.clear();
    
    delete[] clock.buffer;
    delete[] click;
}

void Engine::update()
{
    if (mouseIsPressed && !ofGetMousePressed())
        mouseReleased(ofGetMouseX(), ofGetMouseY(), OF_MOUSE_BUTTON_LEFT);
}

void Engine::draw()
{
    ofBackground(50);

    tabbedPages.draw();
}

//========================================================================
void Engine::audioOut (sig output, tick size, int channels)
{    
    MainFunction* mf = (MainFunction*)tabbedPages.getActiveTab();
    
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
