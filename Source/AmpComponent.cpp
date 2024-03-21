/*
  ==============================================================================

    FilterComponent.cpp
    Created: 6 Mar 2024 5:15:03pm
    Author:  jmast

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AmpComponent.h"

//==============================================================================
AmpComponent::AmpComponent(juce::AudioProcessorValueTreeState& apvts, juce::String attackID, juce::String decayID, juce::String sustainID, juce::String releaseID)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    attAttachment = std::make_unique<SliderAttachment>(apvts, attackID, attSelect);
    decAttachment = std::make_unique<SliderAttachment>(apvts, decayID, decSelect);
    susAttachment = std::make_unique<SliderAttachment>(apvts, sustainID, susSelect);
    relAttachment = std::make_unique<SliderAttachment>(apvts, releaseID, relSelect);


    setSlider(attSelect);
    setSlider(decSelect);
    setSlider(susSelect);
    setSlider(relSelect);



}

AmpComponent::~AmpComponent()
{
}

void AmpComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colours::olivedrab);   // clear the background

    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component


}

void AmpComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;

    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() - padding;
    const auto sliderStartX = 0;
    const auto sliderStartY = bounds.getHeight() / 2 - (sliderHeight / 2);

    attSelect.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decSelect.setBounds(attSelect.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    susSelect.setBounds(decSelect.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    relSelect.setBounds(susSelect.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);




}

void AmpComponent::setSlider(juce::Slider& slider) {
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

}
