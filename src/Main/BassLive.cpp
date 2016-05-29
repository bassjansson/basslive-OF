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
    
    xOffset = 0.0f;
    yOffset = 0.0f;
}

void BassLive::exit()
{
    stream.close();
    delete main;
    delete memory;
}

void BassLive::update()
{
    main->mouseX = mouseX - xOffset;
    main->mouseY = mouseY - yOffset;
}

void BassLive::draw()
{
    // Clear background
    ofBackground(0);
    
    
    // Get offsets
    float xOff = fmodf(xOffset + 10*ofGetWidth(),  ofGetWidth());
    float yOff = fmodf(yOffset + 10*ofGetHeight(), ofGetHeight());
    
    
    // Draw vertical grid lines
    for (int i = 0; i < ofGetWidth() / main->charWidth; i++)
    {
        float x = i * main->charWidth + fmodf(xOff, main->charWidth);
        ofSetColor(30);
        ofSetLineWidth(0.5f);
        ofDrawLine(x, 0, x, ofGetHeight());
    }
    
    float x = fmodf(xOff, ofGetWidth());
    ofSetColor(50, 0, 25);
    ofSetLineWidth(1.0f);
    ofDrawLine(x, 0, x, ofGetHeight());
    
    
    // Draw horizontal grid lines
    for (int i = 0; i < ofGetHeight() / main->charHeight; i++)
    {
        float y = i * main->charHeight + fmodf(yOff, main->charHeight);
        ofSetColor(30);
        ofSetLineWidth(0.5f);
        ofDrawLine(0, y, ofGetWidth(), y);
    }
    
    float y = fmodf(yOff, ofGetHeight());
    ofSetColor(50, 0, 25);
    ofSetLineWidth(1.0f);
    ofDrawLine(0, y, ofGetWidth(), y);
    
    
    // Draw main with offset
    ofPushMatrix();
    ofTranslate(xOffset, yOffset);
    main->draw();
    ofPopMatrix();
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
    if (button == OF_MOUSE_BUTTON_MIDDLE)
    {
        xOffset += x - ofGetPreviousMouseX();
        yOffset += y - ofGetPreviousMouseY();
    }
}

void BassLive::mousePressed (int x, int y, int button)
{
    main->mousePressed(main->mouseX, main->mouseY, button);
}

void BassLive::mouseReleased (int x, int y, int button)
{
    main->mouseReleased(x - xOffset,
                        y - yOffset, button);
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
