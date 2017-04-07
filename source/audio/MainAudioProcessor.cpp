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


#include "MainAudioProcessor.h"
#include "MainGUIComponent.h"


/*========================================================================*/
MainAudioProcessor::MainAudioProcessor()
: AudioProcessor(BusesProperties().withInput( "Input", AudioChannelSet::stereo(), false)
                                 .withOutput("Output", AudioChannelSet::stereo(), false))
{

}

MainAudioProcessor::~MainAudioProcessor()
{

}


/*========================================================================*/
const String MainAudioProcessor::getName() const
{
#ifdef JucePlugin_Name
    return JucePlugin_Name;
#else
    return "";
#endif
}

bool MainAudioProcessor::acceptsMidi() const
{
    return true;
}

bool MainAudioProcessor::producesMidi() const
{
    return false;
}

double MainAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}


/*========================================================================*/
int MainAudioProcessor::getNumPrograms()
{
    return 1;
}

int MainAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MainAudioProcessor::setCurrentProgram(int index)
{

}

const String MainAudioProcessor::getProgramName(int index)
{
    return String();
}

void MainAudioProcessor::changeProgramName(int index, const String& newName)
{
    
}


/*========================================================================*/
void MainAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MainAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool MainAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void MainAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();


    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());


    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);

        // ..do something to the data...
    }
}


/*========================================================================*/
bool MainAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* MainAudioProcessor::createEditor()
{
    return new MainGUIComponent(this);
}


/*========================================================================*/
void MainAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MainAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


/*========================================================================*/
/**
 *  This creates new instances of the audio plugin.
 */
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MainAudioProcessor();
}
