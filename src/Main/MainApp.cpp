
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
    
    editor.setup();
    
    // TODO: List devices in interface
    soundStream.printDeviceList();
    soundStream.setDeviceID(7);
    soundStream.setup(this, 2, 2, SAMPLERATE, BUFFERSIZE, 4);
}

void MainApp::exit()
{
    soundStream.close();
    
    editor.exit();
}

void MainApp::update()
{
    editor.update();
}

void MainApp::draw()
{
    editor.draw();
}

//========================================================================
void MainApp::audioIn (float* buffer, int size, int channels)
{
    //editor.audioIn(buffer, size, channels);
}

void MainApp::audioOut (float* buffer, int size, int channels)
{
    editor.audioOut(buffer, size, channels);
}

//========================================================================
void MainApp::keyPressed (int key)
{
    editor.keyPressed(key);
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
    editor.mousePressed(x, y, button);
}

void MainApp::mouseReleased (int x, int y, int button)
{
    editor.mouseReleased(x, y, button);
}

//========================================================================
void MainApp::windowResized (int w, int h)
{
    editor.windowResized();
}

void MainApp::dragEvent (ofDragInfo dragInfo)
{
    
}

void MainApp::gotMessage (ofMessage msg)
{
    
}
