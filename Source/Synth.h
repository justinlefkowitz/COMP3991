#pragma once
#include "JuceHeader.h"
#include "SynthOscillator.h"


class Synth {

public: 
	void prepareToPlay(double sampleRate);
	void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);

	void setTable(int osc, int wave);
	int getOscillatorWave(int osc);


private:
	
	std::vector<float> generateNullWaveTable();
	std::vector<float> generateSineWaveTable();
	std::vector<float> generateSquareWaveTable();
	std::vector<float> generateSawWaveTable();

	void initializeOscillators();
	std::vector<float> waveGenerate();

	void handleMidiEvent(const juce::MidiMessage& midiEvent);
	float midiNoteNumberToFreq(int noteNumber);
	void render(juce::AudioBuffer<float>& buffer, int startSample, int endSample);

	std::vector<float> waveTables[3];
	int waveSelect[3];
	float intensities[3];



	std::vector<SynthOscillator> oscillators;
	double sampleRate;

};