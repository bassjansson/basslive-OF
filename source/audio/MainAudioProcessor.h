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


#ifndef MAIN_AUDIO_PROCESSOR_H_INCLUDED
#define MAIN_AUDIO_PROCESSOR_H_INCLUDED

#include "JuceHeader.h"


class MainAudioProcessor : public AudioProcessor
{
public:
    /*====================================================================*/
     MainAudioProcessor();
    ~MainAudioProcessor();

    /*====================================================================*/
    const String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    /*====================================================================*/
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
    void changeProgramName(int index, const String& newName) override;

    /*====================================================================*/
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    void processBlock(AudioSampleBuffer& audioSampleBuffer, MidiBuffer& midiBuffer) override;

    /*====================================================================*/
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    /*====================================================================*/
    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:
    /*====================================================================*/


    /*====================================================================*/
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainAudioProcessor)
};


#endif /* MAIN_AUDIO_PROCESSOR_H_INCLUDED */
