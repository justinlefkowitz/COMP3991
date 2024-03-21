/*
  ==============================================================================

    OscData.cpp
    Created: 28 Feb 2024 12:55:40pm
    Author:  jmast

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec) {
    prepare(spec);
}



void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block) {
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::setWave(const int i) {

    switch (i) {

        //sine
    case 0:
        initialise([](float x) {return std::sin(x); });
        break;

        //saw
    case 1:
        initialise([](float x) {return x / juce::MathConstants<float>::pi; });
        break;

        //square
    case 2:
        initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });
        break;

        //triangle 
    case 3:
        initialise([](float x) {return x < 0.0f ? (-2 * x / juce::MathConstants<float>::pi) - 1 : (2 * x / juce::MathConstants<float>::pi) - 1; });
        break;

    default:
        jassertfalse;
        break;
    }

}

void OscData::setWaveFrequency(const int midiNoteNumber) {
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + transposeValue) + 
        detuneValue * (juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + transposeValue + 1) - juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + transposeValue)) / 100);
}


void OscData::setTransposeValue(const int i) {
    transposeValue = i;
}

void OscData::setDetuneValue(const int i) {
    detuneValue = i;
}

void OscData::setPhase(const double i) {
    setPhaseStart(i);
}


