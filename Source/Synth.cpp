#include "Synth.h"


std::vector<float> Synth::generateSineWaveTable() {
	
	constexpr auto WAVETABLE_LENGTH = 64;

	std::vector<float> sineWaveTable(WAVETABLE_LENGTH);

	const auto PI = std::atanf(1.f) * 4;

	for (auto i = 1; i < WAVETABLE_LENGTH; i++) {
		sineWaveTable[i] = std::sinf(2 * PI * static_cast<float>(i) / static_cast<float>(WAVETABLE_LENGTH));
	}

	return sineWaveTable;
}

void Synth::initializeOscillators() {

	constexpr auto OSCIALLTORS_COUNT = 128;

	const auto waveTable = generateSineWaveTable();

	oscillators.clear();
	for (auto i = 0; i < OSCIALLTORS_COUNT; i++) {
		oscillators.emplace_back(waveTable, sampleRate);
	}

}


void Synth::prepareToPlay(double sampleRate) {

	this->sampleRate = sampleRate;

	initializeOscillators();

}


void Synth::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {

	auto currentSample = 0;

	for (const auto midiMessage : midiMessages) {

		const auto midiEvent = midiMessage.getMessage();
		const auto midiEventSample = static_cast<int>(midiEvent.getTimeStamp());

		render(buffer, currentSample, midiEventSample);

		handleMidiEvent(midiEvent);

		currentSample = midiEventSample;


	}

	render(buffer, currentSample, buffer.getNumSamples());

}

void Synth::handleMidiEvent(const juce::MidiMessage& midiEvent) {

	if (midiEvent.isNoteOn()) {
		const auto oscillatorID = midiEvent.getNoteNumber();
		const auto freq = midiNoteNumberToFreq(oscillatorID);
		oscillators[oscillatorID].setFrequency(freq);
	} 
	
	else if (midiEvent.isNoteOff()) {
		const auto oscillatorID = midiEvent.getNoteNumber();
		oscillators[oscillatorID].stop();
	}

	else if (midiEvent.isAllNotesOff()) {
		for (auto& oscillator : oscillators) {
			oscillator.stop();
		}
	}

}

float Synth::midiNoteNumberToFreq(int noteNumber) {
	constexpr auto A4_FREQUENCY = 440.f;
	constexpr auto A4_NOTE_NUMBER = 69.f;
	constexpr auto SEMITONES_IN_OCTAVE = 12;

	return A4_FREQUENCY * std::pow(2.f, (noteNumber - A4_NOTE_NUMBER) / SEMITONES_IN_OCTAVE);
}

void Synth::render(juce::AudioBuffer<float>& buffer, int startSample, int endSample) {

	auto* firstChannel = buffer.getWritePointer(0);

	for (auto& oscillator : oscillators) {
		if (oscillator.isPlaying()) {
			for (auto sample = startSample; sample < endSample; sample++) {
				firstChannel[sample] += oscillator.getSample();
			}
		}
	}

	for (auto channel = 1; channel < buffer.getNumChannels(); channel++) {
		std::copy(firstChannel + startSample, firstChannel + endSample, buffer.getWritePointer(channel) + startSample);
	}

}
