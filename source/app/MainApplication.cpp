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


#include "MainApplication.h"


/*========================================================================*/
void MainApplication::initialise(const String& commandLine)
{
    // Init main app components
    mainAudioProcessor = new MainAudioProcessor();
    mainGUIComponent = new MainGUIComponent(mainAudioProcessor);
    mainWindow = new MainWindow(getApplicationName(), mainGUIComponent);


    // Init audio settings
    int minAudioInputChannels = 2;
    int maxAudioInputChannels = 32;
    int minAudioOutputChannels = 2;
    int maxAudioOutputChannels = 32;
    bool showMidiInputOptions = true;
    bool showMidiOutputSelector = false;
    bool showChannelsAsStereoPairs = true;
    bool hideAdvancedOptionsWithButton = false;


    // Init audioProcessorPlayer
    audioProcessorPlayer = new AudioProcessorPlayer();
    audioProcessorPlayer->setProcessor(mainAudioProcessor);


    // Init audioDeviceManager
    audioDeviceManager = new AudioDeviceManager();
    audioDeviceManager->initialiseWithDefaultDevices(minAudioInputChannels, minAudioOutputChannels);
    audioDeviceManager->addAudioCallback(audioProcessorPlayer);


    // Init audioDeviceSelectorComponent
    audioDeviceSelectorComponent = new AudioDeviceSelectorComponent(*audioDeviceManager,
                                                                    minAudioInputChannels,
                                                                    maxAudioInputChannels,
                                                                    minAudioOutputChannels,
                                                                    maxAudioOutputChannels,
                                                                    showMidiInputOptions,
                                                                    showMidiOutputSelector,
                                                                    showChannelsAsStereoPairs,
                                                                    hideAdvancedOptionsWithButton);
    mainGUIComponent->addChildComponent(audioDeviceSelectorComponent);
    audioDeviceSelectorComponent->setCentrePosition(mainGUIComponent->getWidth()  * 0.25f,
                                                    mainGUIComponent->getHeight() * 0.25f);
    audioDeviceSelectorComponent->setSize(400, 300);
    audioDeviceSelectorComponent->setVisible(true);
}

void MainApplication::shutdown()
{
    mainGUIComponent->removeChildComponent(audioDeviceSelectorComponent);
    audioDeviceSelectorComponent = nullptr;

    audioDeviceManager->removeAudioCallback(audioProcessorPlayer);
    audioDeviceManager->closeAudioDevice();
    audioDeviceManager = nullptr;

    audioProcessorPlayer = nullptr;

    mainAudioProcessor = nullptr;
    mainGUIComponent = nullptr;
    mainWindow = nullptr;
}


/*========================================================================*/
void MainApplication::systemRequestedQuit()
{
    // This is called when the app is being asked to quit: you can ignore this
    // request and let the app carry on running, or call quit() to allow the app to close.
    quit();
}

void MainApplication::anotherInstanceStarted(const String& commandLine)
{
    // When another instance of the app is launched while this one is running,
    // this method is invoked, and the commandLine parameter tells you what
    // the other instance's command-line arguments were.
}


/*========================================================================*/
/**
 *  This macro generates the main() routine that launches the app.
 */
START_JUCE_APPLICATION(MainApplication)
