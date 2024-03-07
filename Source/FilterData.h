/*
  ==============================================================================

    FilterData.h
    Created: 6 Mar 2024 5:15:28pm
    Author:  jmast

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterData : public juce::ADSR {

public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setADSR(float a, float d, float s, float r);

private:
    juce::ADSR::Parameters params;



};