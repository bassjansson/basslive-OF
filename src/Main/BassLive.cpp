//
//  BassLive.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 16/11/15.
//
//

#include "BassLive.hpp"

#define INPUT_CHANNELS  18
#define OUTPUT_CHANNELS 6


//========================================================================
void BassLive::setup()
{
    // OF setup
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofSetFrameRate(FRAME_RATE);
    ofSetVerticalSync(true);
    ofSetEscapeQuitsApp(false);
    ofSetWindowShape(ofGetScreenWidth() - 150, ofGetScreenHeight() - 150);
    ofSetWindowPosition(75, 75);
    ofSetWindowTitle("BassLive 2.0");
    
    memory = new Memory(INPUT_CHANNELS);
    main   = new MainFunction(memory);
    
    // TODO: List devices in interface
    stream.printDeviceList();
    stream.setDeviceID(2);
    stream.setup(this, OUTPUT_CHANNELS, INPUT_CHANNELS, SAMPLERATE, BUFFERSIZE, 4);
}

void BassLive::exit()
{
    stream.close();
    delete main;
    delete memory;
}

void BassLive::update()
{

}

void BassLive::draw()
{
    ofBackground(0);
    main->draw();
}

//========================================================================
void BassLive::audioIn (float* input, int size, int channels)
{
    memory->audioIn(input, size, channels);
}

void BassLive::audioOut (float* output, int size, int channels)
{
    memory->audioOut(output, size, channels);
}

//========================================================================
void BassLive::keyPressed (int key)
{
    main->keyPressed(key);
}

void BassLive::keyReleased (int key)
{

}

//========================================================================
void BassLive::mouseMoved (int x, int y)
{
    
}

void BassLive::mouseDragged (int x, int y, int button)
{
    
}

void BassLive::mousePressed (int x, int y, int button)
{
    main->mousePressed(x, y, button);
}

void BassLive::mouseReleased (int x, int y, int button)
{
    main->mouseReleased(x, y, button);
}

//========================================================================
void BassLive::windowResized (int w, int h)
{
    
}

void BassLive::dragEvent (ofDragInfo dragInfo)
{
    
}

void BassLive::gotMessage (ofMessage msg)
{
    
}
