/*========================================================================*
 |                                                                        |
 |  This file is part of the live coding environment BassLive.            |
 |  Copyright (C) 2017 Bass Jansson.                                      |
 |                                                                        |
 |  This program is free software: you can redistribute it and/or modify  |
 |  it under the terms of the GNU General Public License as published by  |
 |  the Free Software Foundation, either version 3 of the License, or     |
 |  (at your option) any later version.                                   |
 |                                                                        |
 |  This program is distributed in the hope that it will be useful,       |
 |  but WITHOUT ANY WARRANTY; without even the implied warranty of        |
 |  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          |
 |  GNU General Public License for more details.                          |
 |                                                                        |
 |  You should have received a copy of the GNU General Public License     |
 |  along with this program. If not, see <http://www.gnu.org/licenses/>.  |
 |                                                                        |
 *========================================================================*/


#include "MainWindow.h"
#include "MainGUIComponent.h"


/*========================================================================*/
MainWindow::MainWindow(String name, Component* content)
: DocumentWindow(name, Colours::darkseagreen, DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);
    setContentOwned(content, true);
    setResizable(true, true);
    centreWithSize(getWidth(), getHeight());
    setVisible(true);
}

MainWindow::~MainWindow()
{

}


/*========================================================================*/
void MainWindow::closeButtonPressed()
{
    // This is called when the user tries to close this window. Here, we'll just
    // ask the app to quit when this happens, but you can change this to do
    // whatever you need.
    JUCEApplication::getInstance()->systemRequestedQuit();
}
