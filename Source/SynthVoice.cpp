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
    osc.setWaveFrequency(midiNoteNumber);
    osc.reset();
    osc2.setWaveFrequency(midiNoteNumber);
    osc2.reset();

    gain.setGainDecibels(osc.getGain());
    gain2.setGainDecibels(osc2.getGain());

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

    osc.prepareToPlay(spec);
    osc2.prepareToPlay(spec);
    gain.prepare(spec);
    gain2.prepare(spec);

    filter.prepare(spec);
    filter.sampleRate = sampleRate;
    filter.reset();

    

    gain.setGainDecibels(osc.getGain());
    gain2.setGainDecibels(osc2.getGain());

    

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
    synthBuffer2.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer2.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    juce::dsp::AudioBlock<float> audioBlock2{ synthBuffer2 };
    osc.getNextAudioBlock(audioBlock);
    osc2.getNextAudioBlock(audioBlock2);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain2.process(juce::dsp::ProcessContextReplacing<float>(audioBlock2));


    

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    adsr.applyEnvelopeToBuffer(synthBuffer2, 0, synthBuffer2.getNumSamples());

    
    


    for (int i = 0; i < outputBuffer.getNumChannels(); i++) {
        


        outputBuffer.addFrom(i, startSample, synthBuffer, i, 0, numSamples);
        outputBuffer.addFrom(i, startSample, synthBuffer2, i, 0, numSamples);
        


        if (!adsr.isActive()) {
            clearCurrentNote();
        }
    }

    

    if (filter.isOn) {
        juce::dsp::AudioBlock<float> outputBlock{ outputBuffer };
        filter.process(juce::dsp::ProcessContextReplacing<float>(outputBlock));
    }

    

}






