/*
  ==============================================================================

    OscData.h
    Created: 28 Feb 2024 12:55:40pm
    Author:  jmast

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class OscData : public juce::dsp::Oscillator<float> {

public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setWave(const int i);
    void setWaveFrequency(const int midiNoteNumber);
    


private:



};