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


#include "MainGUIComponent.h"
#include "MainAudioProcessor.h"


/*========================================================================*/
MainGUIComponent::MainGUIComponent(AudioProcessor* processor)
: AudioProcessorEditor(processor), audioProcessor(processor)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 600);
}

MainGUIComponent::~MainGUIComponent()
{

}


/*========================================================================*/
void MainGUIComponent::paint (Graphics& g)
{
    g.fillAll(Colours::black);

    g.setColour(Colours::white);
    g.setFont(32.0f);
    g.drawFittedText("Welcome to the world BassLive!", getLocalBounds(), Justification::centred, 1);
}

void MainGUIComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
