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
    //ofSetWindowShape(ofGetScreenWidth() - 150, ofGetScreenHeight() - 150);
    //ofSetWindowPosition(75, 75);
    ofSetWindowTitle("BassLive 2.0");
    
    memory = new Memory(INPUT_CHANNELS);
    main   = new MainFunction(memory);
    
    // TODO: List devices in interface
    stream.printDeviceList();
    stream.setDeviceID(2);
    stream.setup(this, OUTPUT_CHANNELS, INPUT_CHANNELS, SAMPLERATE, BUFFERSIZE, 4);
    
    xOffset = 0.0f;
    yOffset = 0.0f;
    zoom = 1.0f; //2*M_PI;
    
    shader.load("shaders/newton");
    
    a[0]        = 1.0f;
    coefs[0][0] = ofRandom(-1.0f, 1.0f);
    coefs[1][0] = ofRandom(-1.0f, 1.0f);
    coefs[2][0] = 0.0f;
    //coefs[3][0] = 0.0f;
    //coefs[4][0] = 0.0f;
    //coefs[5][0] = 0.0f;
    
    a[1]        = -0.8f;
    coefs[0][1] = ofRandom(-1.0f, 1.0f);
    coefs[1][1] = ofRandom(-1.0f, 1.0f);
    coefs[2][1] = 0.0f;
    //coefs[3][1] = 0.0f;
    //coefs[4][1] = 0.0f;
    //coefs[5][1] = 0.0f;
}

void BassLive::exit()
{
    stream.close();
    delete main;
    delete memory;
    
    shader.unload();
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
    
    
    // Draw vertical grid lines
    for (int i = 0; i < ofGetWidth() / main->charWidth; i++)
    {
        float x = i * main->charWidth + fmodf(xOffset, main->charWidth);
        ofSetColor(64);
        ofSetLineWidth(0.5f);
        ofDrawLine(x, 0, x, ofGetHeight());
    }
    
    ofSetColor(64, 0, 32);
    ofSetLineWidth(1.0f);
    ofDrawLine(xOffset, 0, xOffset, ofGetHeight());
    
    
    // Draw horizontal grid lines
    for (int i = 0; i < ofGetHeight() / main->charHeight; i++)
    {
        float y = i * main->charHeight + fmodf(yOffset, main->charHeight);
        ofSetColor(64);
        ofSetLineWidth(0.5f);
        ofDrawLine(0, y, ofGetWidth(), y);
    }
    
    ofSetColor(64, 0, 32);
    ofSetLineWidth(1.0f);
    ofDrawLine(0, yOffset, ofGetWidth(), yOffset);
    
    
    // Draw newton fractal
    float RMS = main->RMS * 3.0f;
    a[0] =  0.75f + RMS;
    a[1] = -0.50f - RMS;
    coefs[2][0] = sinf(ofGetSystemTime() / 130000.0f * TWO_PI);
    coefs[2][1] = cosf(ofGetSystemTime() / 170000.0f * TWO_PI);
    
    shader.begin();
    
    shader.setUniform2f("dimensions", ofGetHeight(), ofGetHeight());
    shader.setUniform2f("translate" ,
                        -xOffset * zoom * 2.0f / ofGetHeight(),
                         yOffset * zoom * 2.0f / ofGetHeight());
    shader.setUniform1f("zoom"      , zoom);
    shader.setUniform2f("a"         , a[0], a[1]);
    
    for (int i = 0; i < NEWTON_SIZE; i++)
        shader.setUniform2f("coef" + ofToString(i), coefs[i][0], coefs[i][1]);
    
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    shader.end();
    
    
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
    if (button == OF_MOUSE_BUTTON_RIGHT)
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
