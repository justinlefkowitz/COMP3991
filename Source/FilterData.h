/*
  ==============================================================================

    FilterData.h
    Created: 20 Mar 2024 2:50:42pm
    Author:  jmast

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterData : public juce::dsp::IIR::Filter<float> {

public:

    void setFilter(float freq, float res, int type);

    int sampleRate;
    bool isOn;

private:

    float frequency;
    float resonance;
    int filterType;
    
};
