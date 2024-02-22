#include "Synth.h"

std::vector<float> Synth::generateNullWaveTable() {

	constexpr auto WAVETABLE_LENGTH = 64;

	std::vector<float> nullWaveTable(WAVETABLE_LENGTH);

	for (auto i = 0; i < WAVETABLE_LENGTH; i++) {
		nullWaveTable[i] = 0;
	}

	return nullWaveTable;
}

std::vector<float> Synth::generateSineWaveTable() {
	
	constexpr auto WAVETABLE_LENGTH = 64;

	std::vector<float> sineWaveTable(WAVETABLE_LENGTH);

	const auto PI = std::atanf(1.f) * 4;

	for (auto i = 0; i < WAVETABLE_LENGTH; i++) {
		sineWaveTable[i] = std::sinf(2 * PI * static_cast<float>(i) / static_cast<float>(WAVETABLE_LENGTH));
	}

	return sineWaveTable;
}

std::vector<float> Synth::generateSquareWaveTable() {

	constexpr auto WAVETABLE_LENGTH = 64;

	std::vector<float> squareWaveTable(WAVETABLE_LENGTH);

	for (auto i = 0; i < WAVETABLE_LENGTH; i++) {
		squareWaveTable[i] = 2 * static_cast<int>(i / (WAVETABLE_LENGTH/2)) - 1;
	}

	return squareWaveTable;

}

std::vector<float> Synth::generateSawWaveTable() {

	constexpr auto WAVETABLE_LENGTH = 64;

	std::vector<float> sawWaveTable(WAVETABLE_LENGTH);

	for (auto i = 0; i < WAVETABLE_LENGTH; i++) {
		sawWaveTable[i] = 2 * (static_cast<float>(i) / static_cast<float>(WAVETABLE_LENGTH)) - 1;
	}

	return sawWaveTable;



}

std::vector<float> Synth::waveGenerate() {
	constexpr auto WAVETABLE_LENGTH = 64;

	std::vector<float> returnWave(WAVETABLE_LENGTH);



	for (int i = 0; i < WAVETABLE_LENGTH; i++) {
		returnWave[i] = (waveTables[0][i] + waveTables[1][i]) / 2;
	}


	return returnWave;
}




void Synth::initializeOscillators() {

	constexpr auto OSCIALLTORS_COUNT = 128;

	std::vector<float> waveTable = waveGenerate();

	oscillators.clear();
	for (auto i = 0; i < OSCIALLTORS_COUNT; i++) {
		oscillators.emplace_back(waveTable, sampleRate);
	}

}

void Synth::setTable(int osc, int wave) {

	constexpr auto OSCIALLTORS_COUNT = 128;
	waveSelect[osc] = wave;


	if (wave == 0) {
		waveTables[0] = generateNullWaveTable();
	} 
	else if (wave == 1) {
		waveTables[osc] = generateSineWaveTable();
	}
	else if (wave == 2) {
		waveTables[osc] = generateSawWaveTable();
	}
	else if (wave == 3) {
		waveTables[osc] = generateSquareWaveTable();
	}

	initializeOscillators();

}




int Synth::getOscillatorWave(int osc) {
	return waveSelect[osc];
}

void Synth::prepareToPlay(double sampleRate) {

	this->sampleRate = sampleRate;

	waveTables[0] = generateNullWaveTable();
	waveTables[1] = generateNullWaveTable();
	waveTables[2] = generateNullWaveTable();

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
