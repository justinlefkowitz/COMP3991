#include "SynthOscillator.h"
#include <cmath>

SynthOscillator::SynthOscillator(std::vector<float> waveTable, double sampleRate)  {
	this->waveTable = waveTable;
	this->sampleRate = sampleRate;
}



void SynthOscillator::setFrequency(float freq) {
	indexIncrement = freq * static_cast<float>(waveTable.size()) / static_cast<float>(sampleRate);
}



float SynthOscillator::getSample() {

	const auto sample = interpolateLinearly();
	index += indexIncrement;
	index = std::fmod(index, static_cast<float>(waveTable.size()));
	return sample;
}

float SynthOscillator::interpolateLinearly() {

	const auto truncatedIndex = static_cast<int>(index);
	const auto nextIndex = (truncatedIndex + 1) % static_cast<int>(waveTable.size());
	const auto nextIndexWeight = index - static_cast<float>(truncatedIndex);
	const auto truncatedIndexWeight = 1.f - nextIndexWeight;

	return truncatedIndexWeight * waveTable[truncatedIndex] + nextIndexWeight * waveTable[nextIndex];
}

void SynthOscillator::stop() {

	index = 0.f;
	indexIncrement = 0.f;

}

bool SynthOscillator::isPlaying() {

	return indexIncrement != 0.f;

}