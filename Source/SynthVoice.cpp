/*
  ==============================================================================

    SynthVoice.cpp
    Created: 18 Feb 2024 5:49:17pm
    Author:  jmast

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*> (sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    
    if (!allowTailOff || !adsr.isActive()) {
        clearCurrentNote();
    }
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels)
{
    adsr.setSampleRate(sampleRate);

    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numOutputChannels;

    osc.prepare(spec);
    gain.prepare(spec);

    gain.setGainLinear(0.2f);
    


    isPrepared = true;
}




void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    if (!isVoiceActive()) {
        return;
    }

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());


    for (int i = 0; i < outputBuffer.getNumChannels(); i++) {
        outputBuffer.addFrom(i, startSample, synthBuffer, i, 0, numSamples);

        if (!adsr.isActive()) {
            clearCurrentNote();
        }
    }
}


void SynthVoice::updateADSR(const float attack, const float decay, const float sustain, const float release) {
    adsrParameters.attack = attack;
    adsrParameters.decay = decay;
    adsrParameters.sustain = sustain;
    adsrParameters.release = release;

    adsr.setParameters(adsrParameters);
}

void SynthVoice::updateWave(int wave) {

    switch (wave) {

        //sine
    case (0):
        osc.initialise([](float x) {return std::sin(x); });

        //saw
    case (1):
        osc.initialise([](float x) {return x / juce::MathConstants<float>::pi; });

        //square
    case (2):
        osc.initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });

    
    default:
        jassertfalse;
        break;
    }


}



