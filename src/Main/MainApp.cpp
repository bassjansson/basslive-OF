
#include "MainApp.hpp"


//========================================================================
void MainApp::setup()
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
    
    engine.setup();
    
    // TODO: List devices in interface
    soundStream.printDeviceList();
    soundStream.setDeviceID(6);
    soundStream.setup(this, 2, 2, SAMPLERATE, BUFFERSIZE, 4);
}

void MainApp::exit()
{
    soundStream.close();
    
    engine.exit();
}

void MainApp::update()
{
    engine.update();
}

void MainApp::draw()
{
    engine.draw();
}

//========================================================================
void MainApp::audioIn (float* buffer, int size, int channels)
{
    engine.audioIn(buffer, size, channels);
}

void MainApp::audioOut (float* buffer, int size, int channels)
{
    engine.audioOut(buffer, size, channels);
}

//========================================================================
void MainApp::keyPressed (int key)
{
    engine.keyPressed(key);
}

void MainApp::keyReleased (int key)
{

}

//========================================================================
void MainApp::mouseMoved (int x, int y)
{
    
}

void MainApp::mouseDragged (int x, int y, int button)
{
    
}

void MainApp::mousePressed (int x, int y, int button)
{
    engine.mousePressed(x, y, button);
}

void MainApp::mouseReleased (int x, int y, int button)
{
    engine.mouseReleased(x, y, button);
}

//========================================================================
void MainApp::windowResized (int w, int h)
{
    
}

void MainApp::dragEvent (ofDragInfo dragInfo)
{
    
}

void MainApp::gotMessage (ofMessage msg)
{
    
}
