/*
  ==============================================================================

    OscComponent.cpp
    Created: 28 Feb 2024 1:08:30pm
    Author:  jmast

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorID)
{

    oscWaveSelector.addItemList(apvts.getParameter(waveSelectorID)->getAllValueStrings(), 1);
    addAndMakeVisible(oscWaveSelector);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorID, oscWaveSelector);

}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);


}

void OscComponent::resized()
{
    oscWaveSelector.setBounds(0, 0, 90, 20);

}
