
#include "MainApp.h"


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
    
    
    f = new Function();
    f->loadFont("fonts/Menlo-Bold.ttf", 20);
}

void MainApp::exit()
{

}

void MainApp::update()
{

}

void MainApp::draw()
{
    ofBackground(0);
    ofSetColor(255);
    float x = 50;
    float y = 50;
    f->Function::draw(x, y, VERTICAL);
}

//========================================================================
void MainApp::audioIn (float* buffer, int size, int channels)
{

}

void MainApp::audioOut (float* buffer, int size, int channels)
{
   
}

//========================================================================
void MainApp::keyPressed (int key)
{
    f->keyPressedMain(key);
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
    
}

void MainApp::mouseReleased (int x, int y, int button)
{
    
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
