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
    ofSetWindowTitle("BassLive 2.0");
    
    
    memory = new Memory(INPUT_CHANNELS);
    main   = new MainFunction(memory);
    
    
    // TODO: List devices in interface
    stream.printDeviceList();
    stream.setDeviceID(2);
    stream.setup(this, OUTPUT_CHANNELS, INPUT_CHANNELS, SAMPLERATE, BUFFERSIZE, 4);
    
    
    xOffset    = 0.0f;
    yOffset    = 0.0f;
    zoom       = 1.0f;
    zoomTarget = 1.0f;
    
    
    shader.load("shaders/newton");
    
    
    a[0]        = 1.0f;
    coefs[0][0] = ofRandom(-1.0f, 1.0f);
    coefs[1][0] = ofRandom(-1.0f, 1.0f);
    coefs[2][0] = ofRandom(-1.0f, 1.0f);
    coefs[3][0] = 0.0f;
    //coefs[4][0] = 0.0f;
    //coefs[5][0] = 0.0f;
    
    a[1]        = -0.8f;
    coefs[0][1] = ofRandom(-1.0f, 1.0f);
    coefs[1][1] = ofRandom(-1.0f, 1.0f);
    coefs[2][1] = ofRandom(-1.0f, 1.0f);
    coefs[3][1] = 0.0f;
    //coefs[4][1] = 0.0f;
    //coefs[5][1] = 0.0f;
}

void BassLive::exit()
{
    shader.unload();
    
    stream.close();
    delete main;
    delete memory;
}

void BassLive::update()
{
    // Update mouse position in main
    main->mouseX = (mouseX - xOffset) / zoom;
    main->mouseY = (mouseY - yOffset) / zoom;
    
    
    // Update zoom
    zoom = 0.9f * zoom + 0.1f * zoomTarget;
    
    
    // Update coefficients with RMS
    float RMS = main->RMS * 3.0f;
    a[0] =  0.75f + RMS;
    a[1] = -0.50f - RMS;
    coefs[NEWTON_SIZE - 1][0] = sinf(ofGetSystemTime() / 130000.0f * TWO_PI * (RMS + 1.0f));
    coefs[NEWTON_SIZE - 1][1] = cosf(ofGetSystemTime() / 170000.0f * TWO_PI * (RMS + 1.0f));
}

void BassLive::draw()
{
    // Clear background
    ofBackground(0);
    
    
    // Draw vertical grid lines
    float gridXStep = main->charWidth * zoom;
    float gridXOffset = fmodf(fabsf(xOffset), gridXStep);
    if (xOffset < 0.0f) gridXOffset = gridXStep - gridXOffset;
    for (float x = gridXOffset; x < ofGetWidth(); x += gridXStep)
    {
        ofSetColor(30, 40, 50);
        ofDrawLine(x, 0, x, ofGetHeight());
    }

    
    // Draw horizontal grid lines
    float gridYStep = main->charHeight * zoom;
    float gridYOffset = fmodf(fabsf(yOffset), gridYStep);
    if (yOffset < 0.0f) gridYOffset = gridYStep - gridYOffset;
    for (float y = gridYOffset; y < ofGetHeight(); y += gridYStep)
    {
        ofSetColor(30, 40, 50);
        ofDrawLine(0, y, ofGetWidth(), y);
    }
    
    
    // Draw newton fractal
    shader.begin();
    
    shader.setUniform1f("height"   , ofGetHeight());
    shader.setUniform2f("translate", xOffset, yOffset);
    shader.setUniform1f("zoom"     , 1.0f / zoom);
    shader.setUniform2f("a"        , a[0], a[1]);
    
    for (int i = 0; i < NEWTON_SIZE; i++)
        shader.setUniform2f("coef" + ofToString(i), coefs[i][0], coefs[i][1]);
    
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    shader.end();
    
    
    // Draw main with offset and zoom
    ofPushMatrix();
    
    ofTranslate(xOffset, yOffset);
    ofScale(zoom, zoom);
    
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
    // Send key to main
    main->keyPressed(key);
    
    
    // Zoom in/out and randomnise fractal
    if (ofGetKeyPressed(OF_KEY_COMMAND))
    {
             if (key == '=') zoomTarget *= 1.2f;
        else if (key == '-') zoomTarget /= 1.2f;
        else if (key == '/')
        {
            coefs[0][0] = ofRandom(-1.0f, 1.0f);
            coefs[1][0] = ofRandom(-1.0f, 1.0f);
            coefs[2][0] = ofRandom(-1.0f, 1.0f);
            
            coefs[0][1] = ofRandom(-1.0f, 1.0f);
            coefs[1][1] = ofRandom(-1.0f, 1.0f);
            coefs[2][1] = ofRandom(-1.0f, 1.0f);
        }
    }
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
    main->mouseReleased(main->mouseX, main->mouseY, button);
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
