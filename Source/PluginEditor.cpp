/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MIDISynthAudioProcessorEditor::MIDISynthAudioProcessorEditor (MIDISynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc (audioProcessor.apvts, "OSC", "OSCTRANS"), osc2(audioProcessor.apvts, "OSC2", "OSCTRANS2"), oscScope(p.getAudioBufferQueue())
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    setSize (1200, 600);
    addAndMakeVisible(osc);
    addAndMakeVisible(osc2);
    addAndMakeVisible(oscScope);
    setResizable(true, true);

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    attAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "ATTACK", attSelect);
    decAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DECAY", decSelect);
    susAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "SUSTAIN", susSelect);
    relAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "RELEASE", relSelect);
   

    setSlider(attSelect);
    setSlider(decSelect);
    setSlider(susSelect);
    setSlider(relSelect);

    



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

    osc.setBounds(10, 10, 400, 200);
    osc2.setBounds(510, 10, 400, 200);
    oscScope.setBounds(10, 300, oscScope.getBounds().getWidth(), oscScope.getBounds().getHeight());

    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;

    /*
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() - padding;
    const auto sliderStartX = 0;
    const auto sliderStartY = bounds.getHeight() / 2 - (sliderHeight / 2);

    attSelect.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decSelect.setBounds(attSelect.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    susSelect.setBounds(decSelect.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    relSelect.setBounds(susSelect.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

    */
    
}


void MIDISynthAudioProcessorEditor::setSlider(juce::Slider& slider) {
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

}
