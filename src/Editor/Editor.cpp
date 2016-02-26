//
//  Editor.cpp
//  BassLive
//
//  Created by Bass Jansson on 07/12/15.
//
//

#include "Editor.hpp"


//========================================================================
void Editor::setup()
{
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
    
    memory = NULL;
    
    newPage();
}

void Editor::exit()
{
    for (int i = 0; i < pages.size(); i++)
        delete pages[i];
    pages.clear();
}

void Editor::update()
{
    memory = ((MainFunction*)tabbedPages.getActiveTab())->memory;
}

void Editor::draw()
{
    ofBackground(50);

    tabbedPages.draw();
}

//========================================================================
void Editor::mousePressed (float x, float y, int button)
{
    ((MainFunction*)tabbedPages.getActiveTab())->mousePressed(x, y, button);
}

void Editor::keyPressed (int key)
{
    ((MainFunction*)tabbedPages.getActiveTab())->keyPressed(key);
    
    if (ofGetKeyPressed(OF_KEY_COMMAND) && key == 't')
        newPage();
}

//========================================================================
void Editor::windowResized()
{
    tabbedPages.setSize(EDITOR_WIDTH, EDITOR_HEIGHT + FONT_SIZE * 2);
    
    for (int i = 0; i < pages.size(); i++)
        pages[i]->setSize(EDITOR_WIDTH, EDITOR_HEIGHT);
}

//========================================================================
Memory** Editor::getMemoryPointer()
{
    return &memory;
}

//========================================================================
void Editor::newPage()
{
    pages.push_back(new MainFunction("#" + ofToString(pages.size() + 1)));
    tabbedPages.add(pages.back());
    tabbedPages.setActiveTab(pages.size() - 1);
    windowResized();
}
