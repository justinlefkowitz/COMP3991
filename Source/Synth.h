#pragma once
#include "JuceHeader.h"
#include "SynthOscillator.h"


class Synth {

public: 
	void prepareToPlay(double sampleRate);
	void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);


private:
	void initializeOscillators();
	std::vector<float> generateSineWaveTable();
	void handleMidiEvent(const juce::MidiMessage& midiEvent);
	float midiNoteNumberToFreq(int noteNumber);
	void render(juce::AudioBuffer<float>& buffer, int startSample, int endSample);

	std::vector<SynthOscillator> oscillators;
	double sampleRate;

};