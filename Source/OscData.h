/*
  ==============================================================================

    OscData.h
    Created: 28 Feb 2024 12:55:40pm
    Author:  jmast

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MyOscillator.h"


class OscData : public juce::dsp::MyOscillator<float> {

public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setWave(const int i);
    void setWaveFrequency(const int midiNoteNumber);
    void setTransposeValue(const int i);
    void setDetuneValue(const int i);
    void setPhase(const double i);
    void setGain(const float i) { gainInDecibles = i; };
    float getGain() const { return gainInDecibles; };

private:
    int transposeValue;
    int detuneValue;
    float gainInDecibles = -12.0;
};