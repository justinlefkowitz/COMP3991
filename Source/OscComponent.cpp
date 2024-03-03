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
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorID, juce::String transposeSelectorID)
{

    oscWaveSelector.addItemList(apvts.getParameter(waveSelectorID)->getAllValueStrings(), 1);
    addAndMakeVisible(oscWaveSelector);

    oscTranspose.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    oscTranspose.setColour(0x1001200, juce::Colours::black);
    oscTranspose.setColour(0x1001310, juce::Colours::black);
    oscTranspose.setColour(0x1001312, juce::Colours::green);
    oscTranspose.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    addAndMakeVisible(oscTranspose);


    oscTransposeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, transposeSelectorID, oscTranspose);
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorID, oscWaveSelector);

}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
   g.fillAll(juce::Colours::purple);


}

void OscComponent::resized()
{
    auto padding = 10;
    auto height = getHeight();
    auto width = getWidth();

    oscWaveSelector.setBounds(padding, padding, width / 2, height / 5);
    oscTranspose.setBounds(width / 2 + padding, padding, width / 2, height - 2 * padding);

}
