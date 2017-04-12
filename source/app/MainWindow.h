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


#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include "JuceHeader.h"


class MainWindow : public DocumentWindow
{
public:
    /*====================================================================*/
    MainWindow(String title, Component* contentOwned);

    /*====================================================================*/
    void closeButtonPressed() override;

private:
    /*====================================================================*/
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};


#endif /* MAIN_WINDOW_H_INCLUDED */
