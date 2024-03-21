/*
  ==============================================================================

    FilterData.cpp
    Created: 20 Mar 2024 2:50:42pm
    Author:  jmast

  ==============================================================================
*/

#include "FilterData.h"


void FilterData::setFilter(float freq, float res, int type) {

    frequency = freq;
    resonance = res;
    filterType = type;


    switch (type) {
    case 0:
        *coefficients = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, freq, res);
        break;
    case 1:
        *coefficients = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, freq, res);
        break;
    case 2:
        *coefficients = *juce::dsp::IIR::Coefficients<float>::makeBandPass(sampleRate, freq, res);
        break;
    }
}





