/*
  ==============================================================================

    FilterComponent.cpp
    Created: 20 Mar 2024 2:50:33pm
    Author:  jmast

  ==============================================================================
*/

#include "FilterComponent.h"

FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String freqID, juce::String resID, juce::String typeID, juce::String powerID) {

    freqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, freqID, freq);
    resAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, resID, res);
    typeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, typeID, type);
    powerAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, powerID, power);

    freq.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    freq.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(freq);

    res.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    res.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(res);

    type.addItemList(apvts.getParameter(typeID)->getAllValueStrings(), 1);
    type.setSelectedId(1);
    addAndMakeVisible(type);

    addAndMakeVisible(power);



}

FilterComponent::~FilterComponent() {

}

void FilterComponent::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::pink);   // clear the background

    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds(), 4);
}

void FilterComponent::resized() {

    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;

    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() - padding;
    const auto sliderStartX = 0;
    const auto sliderStartY = bounds.getHeight() / 2 - (sliderHeight / 2);

    freq.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    res.setBounds(freq.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    type.setBounds(res.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    power.setBounds(type.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);


}
