/*
  ==============================================================================

    FilterData.cpp
    Created: 6 Mar 2024 5:15:28pm
    Author:  jmast

  ==============================================================================
*/

#include "FilterData.h"

void FilterData::prepareToPlay(juce::dsp::ProcessSpec& spec) {



}

void FilterData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block) {

}

void FilterData::setADSR(float a, float d, float s, float r) {
    params.attack = a;
    params.decay = d;
    params.sustain = s;
    params.release = r;
    setParameters(params);
}




