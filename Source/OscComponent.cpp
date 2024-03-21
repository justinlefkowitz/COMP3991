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
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorID, juce::String transposeSelectorID, juce::String detuneSelectorID, 
    juce::String phaseSelectorID, juce::String gainSelectorID)
{

    oscWaveSelector.addItemList(apvts.getParameter(waveSelectorID)->getAllValueStrings(), 1);
    addAndMakeVisible(oscWaveSelector);

    oscTranspose.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    addAndMakeVisible(oscTranspose);

    oscDetune.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    addAndMakeVisible(oscDetune);

    oscPhase.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    oscPhase.setColour(0x1001200, juce::Colours::black);
    oscPhase.setColour(0x1001310, juce::Colours::black);
    oscPhase.setColour(0x1001312, juce::Colours::purple);
    oscPhase.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    addAndMakeVisible(oscPhase);

    oscGain.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    addAndMakeVisible(oscGain);



    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorID, oscWaveSelector);
    oscTransposeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, transposeSelectorID, oscTranspose);
    oscDetuneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, detuneSelectorID, oscDetune);
    oscPhaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, phaseSelectorID, oscPhase);
    oscGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, gainSelectorID, oscGain);
   
    

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

    oscWaveSelector.setBounds(padding, padding, width / 3, height / 5);
    oscTranspose.setBounds(padding, padding + 2 *height / 5, width / 3, height / 5);
    oscDetune.setBounds(padding, padding + 3 * height / 5, width / 3, height / 5);
    oscPhase.setBounds(padding + width / 3, padding , width / 2,height - 2 * padding );
    oscGain.setBounds(padding + 5 * width / 6, padding, width / 10, height - 2 * padding);

}
