/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MIDISynthAudioProcessorEditor::MIDISynthAudioProcessorEditor (MIDISynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    setSize (400, 300);
    setResizable(true, true);

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    attAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "ATTACK", attSelect);
    decAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DECAY", decSelect);
    susAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "SUSTAIN", susSelect);
    relAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "RELEASE", relSelect);
    oscAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelect);

    setSlider(attSelect);
    setSlider(decSelect);
    setSlider(susSelect);
    setSlider(relSelect);

    oscSelect.addItemList(audioProcessor.apvts.getParameter("OSC")->getAllValueStrings(), 1);
    addAndMakeVisible(oscSelect);


}

MIDISynthAudioProcessorEditor::~MIDISynthAudioProcessorEditor()
{
}

//==============================================================================
void MIDISynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
 

}

void MIDISynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

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

    oscSelect.setBounds(10, 10, 100, 50);

    
}


void MIDISynthAudioProcessorEditor::setSlider(juce::Slider& slider) {
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

}
