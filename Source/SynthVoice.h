/*
  ==============================================================================

    SynthVoice.h
    Created: 18 Feb 2024 5:49:17pm
    Author:  jmast

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice {


 public:

     bool canPlaySound(juce::SynthesiserSound* sound) override;
     void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
     void stopNote(float velocity, bool allowTailOff) override;
     void controllerMoved(int controllerNumber, int newControllerValue) override;
     void pitchWheelMoved(int newPitchWheelValue) override;

     void prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels);
     void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

     void updateADSR(const float attack, const float sustain, const float decay, const float release);
     void updateWave(int wave);

 private:
     juce::dsp::ProcessSpec spec;
     juce::AudioBuffer<float> synthBuffer;

     juce::dsp::Oscillator<float> osc{ [](float x) {return x < 0.0f ? -1.0f : 1.0f; }, 200 };
     juce::dsp::Gain<float> gain;

     juce::ADSR adsr;
     juce::ADSR::Parameters adsrParameters;

     bool isPrepared = false;



};