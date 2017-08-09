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
void BassLiveApp::setup()
{
    // OF setup
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofSetVerticalSync(true);
    ofSetEscapeQuitsApp(false);
    ofSetFrameRate(FRAME_RATE);
    ofSetWindowTitle(WINDOW_TITLE);
    ofSetDataPathRoot(DATA_PATH_ROOT);
    
    
    memory = new Memory(INPUT_CHANNELS);
    main   = new MainFunction(memory);
    
    
    // TODO: List devices in interface
    stream.printDeviceList();
    stream.setDeviceID(2);
    stream.setup(this, OUTPUT_CHANNELS, INPUT_CHANNELS, SAMPLERATE, BUFFERSIZE, 4);
    
    
    sideBarWidth = main->charWidth * 10.0f; // TODO: should be a define
    xOffset = sideBarWidth;
    yOffset = 0.0f;
    zoom = 1.0f;
    zoomTarget = 1.0f;
    
    
    sideBarFont.load("fonts/menlo-bold.ttf", FONT_SIZE / 2);
    shader.load("shaders/newton");


    // Testing the new core
    BassLive::Node<float> node1, node2;

    node1.value() = 0.5f;
    node2.value() = 0.25f;

    node1.connectTo(node2);

    cout << "Node 2 value: " << node1.getValueOfConnectedNode(0) << endl;
}

void BassLiveApp::exit()
{
    shader.unload();
    
    stream.close();
    delete main;
    delete memory;
}

void BassLiveApp::update()
{
    // Update mouse position in main
    main->mouseX = (mouseX - xOffset) / zoom;
    main->mouseY = (mouseY - yOffset) / zoom;
    
    
    // Update zoom
    zoom = 0.9f * zoom + 0.1f * zoomTarget;
}

void BassLiveApp::draw()
{
    // Clear background
    ofBackground(0);
    
    
    // Draw vertical grid lines
    float gridXStep = main->charWidth * zoom;
    float gridXOffset = fmodf(fabsf(xOffset), gridXStep);
    if (xOffset < 0.0f) gridXOffset = gridXStep - gridXOffset;
    gridXOffset = fmodf(gridXOffset - fmodf(sideBarWidth, gridXStep) + gridXStep, gridXStep);
    
    for (float x =  gridXOffset  + sideBarWidth;
               x <  ofGetWidth() - sideBarWidth;
               x += gridXStep)
    {
        ofSetColor(50, 50, 50); // TODO: should be a define
        ofDrawLine(x, 0, x, ofGetHeight());
    }

    
    // Draw horizontal grid lines
    float gridYStep = main->charHeight * zoom;
    float gridYOffset = fmodf(fabsf(yOffset), gridYStep);
    if (yOffset < 0.0f) gridYOffset = gridYStep - gridYOffset;
    
    for (float y =  gridYOffset;
               y <  ofGetHeight();
               y += gridYStep)
    {
        ofSetColor(30, 50, 70); // TODO: should be a define
        ofDrawLine(sideBarWidth, y, ofGetWidth() - sideBarWidth, y);
    }
    
    
    // Draw newton fractal
    shader.begin();
    
    shader.setUniform1f("height"   , ofGetHeight());
    shader.setUniform2f("translate", xOffset, yOffset);
    shader.setUniform1f("zoom"     , 2.0f / zoom);
    shader.setUniform2f("a"        , main->a[0], main->a[1]);
    
    for (int i = 0; i < NEWTON_SIZE; i++)
        shader.setUniform2f("coef" + ofToString(i), main->coefs[i][0], main->coefs[i][1]);
    
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    shader.end();
    
    
    // Draw main with offset and zoom
    ofPushMatrix();
    
    ofTranslate(xOffset, yOffset);
    ofScale(zoom, zoom);
    
    main->draw();
    
    ofPopMatrix();
    
    
    // Draw module strings
    float xPos = 0.0f;
    float yPos = 0.0f;
    ofSetColor(80, 110, 140, 50); // TODO: should be a define
    ofDrawRectangle(xPos, yPos, sideBarWidth, ofGetHeight());
    
    yPos += main->charHeight * 0.875f;
    ofSetColor(140, 170, 200, 230); // TODO: should be a define
    ofDrawLine(xPos, yPos, xPos + sideBarWidth, yPos);
    
    xPos += main->charWidth  * 0.5f;
    yPos -= main->charHeight * 0.125f;
    sideBarFont.drawString("Modules in memory:", xPos, yPos);
    
    yPos += main->charHeight * 0.75f;
    StringVector& moduleStrings = memory->getModuleStrings();
    
    for (int m = 0; m < moduleStrings.size(); ++m)
    {
        ofSetColor(110, 140, 170, 200); // TODO: should be a define
        sideBarFont.drawString(moduleStrings[moduleStrings.size() - m - 1], xPos, yPos);
        yPos += main->charHeight * 0.5f;
    }
    
    
    // Draw buffer strings
    xPos = ofGetWidth() - sideBarWidth;
    yPos = 0.0f;
    ofSetColor(140, 80, 110, 50); // TODO: should be a define
    ofDrawRectangle(xPos, yPos, sideBarWidth, ofGetHeight());
    
    yPos += main->charHeight * 0.875f;
    ofSetColor(200, 140, 170, 230); // TODO: should be a define
    ofDrawLine(xPos, yPos, xPos + sideBarWidth, yPos);
    
    xPos += main->charWidth  * 0.5f;
    yPos -= main->charHeight * 0.125f;
    sideBarFont.drawString("Buffers in memory:", xPos, yPos);
    
    yPos += main->charHeight * 0.75f;
    StringVector& bufferStrings = memory->getBufferStrings();
    
    for (int b = 0; b < bufferStrings.size(); ++b)
    {
        ofSetColor(170, 110, 140, 200); // TODO: should be a define
        sideBarFont.drawString(bufferStrings[bufferStrings.size() - b - 1], xPos, yPos);
        yPos += main->charHeight * 0.5f;
    }
}

//========================================================================
void BassLiveApp::audioIn (float* input, int size, int channels)
{
    memory->audioIn(input, size, channels);
}

void BassLiveApp::audioOut (float* output, int size, int channels)
{
    memory->audioOut(output, size, channels);
}

//========================================================================
void BassLiveApp::keyPressed (int key)
{
    // Send key to main
    main->keyPressed(key);
    
    
    // Zoom in/out with cmd plus/min
    if (ofGetKeyPressed(OF_KEY_COMMAND))
    {
             if (key == '=') zoomTarget *= 1.2f;
        else if (key == '-') zoomTarget /= 1.2f;
    }
}

void BassLiveApp::keyReleased (int key)
{

}

//========================================================================
void BassLiveApp::mouseMoved (int x, int y)
{
    
}

void BassLiveApp::mouseDragged (int x, int y, int button)
{
    if (button == OF_MOUSE_BUTTON_RIGHT)
    {
        xOffset += x - ofGetPreviousMouseX();
        yOffset += y - ofGetPreviousMouseY();
    }
}

void BassLiveApp::mousePressed (int x, int y, int button)
{
    main->mousePressed(main->mouseX, main->mouseY, button);
}

void BassLiveApp::mouseReleased (int x, int y, int button)
{
    main->mouseReleased(main->mouseX, main->mouseY, button);
}

//========================================================================
void BassLiveApp::windowResized (int w, int h)
{
    
}

void BassLiveApp::dragEvent (ofDragInfo dragInfo)
{
    
}

void BassLiveApp::gotMessage (ofMessage msg)
{
    
}
