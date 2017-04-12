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
#include "MainAudioProcessor.h"
#include "MainWindow.h"


/*========================================================================*/
void MainApplication::initialise(const String& commandLine)
{
    // Init audio processor
    mainAudioProcessor = new MainAudioProcessor();


    // Init main window
    mainDocumentWindow = new MainWindow(getApplicationName() + " " +
                                        getApplicationVersion(),
                                        mainAudioProcessor->createEditor());


    // Init audio processor player
    audioProcessorPlayer = new AudioProcessorPlayer();
    audioProcessorPlayer->setProcessor(mainAudioProcessor);


    // Init audio device manager
    audioDeviceManager = new AudioDeviceManager();
    audioDeviceManager->initialiseWithDefaultDevices(2, 2);
    audioDeviceManager->addAudioCallback(audioProcessorPlayer);
}

void MainApplication::shutdown()
{
    audioDeviceManager = nullptr;
    audioProcessorPlayer = nullptr;

    mainDocumentWindow = nullptr;
    mainAudioProcessor = nullptr;
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


/*====================================================================*/
void MainApplication::openAudioDeviceSettingsDialog()
{
    // Init audio settings
    int minAudioInputChannels = 2;
    int maxAudioInputChannels = 32;
    int minAudioOutputChannels = 2;
    int maxAudioOutputChannels = 32;
    bool showMidiInputOptions = true;
    bool showMidiOutputSelector = false;
    bool showChannelsAsStereoPairs = true;
    bool hideAdvancedOptionsWithButton = false;


    // Init audioDeviceSelectorComponent
    AudioDeviceSelectorComponent* audioDeviceSelectorComponent;
    audioDeviceSelectorComponent = new AudioDeviceSelectorComponent(*audioDeviceManager,
                                                                    minAudioInputChannels,
                                                                    maxAudioInputChannels,
                                                                    minAudioOutputChannels,
                                                                    maxAudioOutputChannels,
                                                                    showMidiInputOptions,
                                                                    showMidiOutputSelector,
                                                                    showChannelsAsStereoPairs,
                                                                    hideAdvancedOptionsWithButton);
    //audioDeviceSelectorComponent->setSize(400, 300);
    audioDeviceSelectorComponent->setVisible(true);


    // Init I/O settings dialog window
    DialogWindow::LaunchOptions dialogWindowLaunchOptions;
    dialogWindowLaunchOptions.dialogTitle = "I/O Settings";
    dialogWindowLaunchOptions.dialogBackgroundColour = Colours::grey;
    dialogWindowLaunchOptions.content.setOwned(audioDeviceSelectorComponent);
    dialogWindowLaunchOptions.componentToCentreAround = mainDocumentWindow;
    dialogWindowLaunchOptions.escapeKeyTriggersCloseButton = false;
    dialogWindowLaunchOptions.useNativeTitleBar = true;
    dialogWindowLaunchOptions.resizable = false;
    dialogWindowLaunchOptions.useBottomRightCornerResizer = false;
    dialogWindowLaunchOptions.launchAsync();
}


/*========================================================================*/
/** This macro generates the main() routine that launches the app. */
START_JUCE_APPLICATION(MainApplication)
