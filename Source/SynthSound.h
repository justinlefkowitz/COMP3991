/*
  ==============================================================================

    SynthSound.h
    Created: 18 Feb 2024 5:49:44pm
    Author:  jmast

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {

public:

    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }

};