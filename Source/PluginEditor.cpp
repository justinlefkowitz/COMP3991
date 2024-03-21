/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MIDISynthAudioProcessorEditor::MIDISynthAudioProcessorEditor (MIDISynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc (audioProcessor.apvts, "OSC", "OSCTRANS", "OSCDET", "OSCPHASE", "OSCGAIN"),
    osc2(audioProcessor.apvts, "OSC2", "OSCTRANS2", "OSCDET2", "OSCPHASE2", "OSCGAIN2"), oscScope(p.getAudioBufferQueue()),
        amp (audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE"), filter (audioProcessor.apvts,"FILTERFREQ", "FILTERRES", "FILTERTYPE", "FILTERON")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    setSize (1200, 600);
    addAndMakeVisible(osc);
    addAndMakeVisible(osc2);
    addAndMakeVisible(oscScope);
    addAndMakeVisible(amp);
    addAndMakeVisible(filter);

    setResizable(true, true);

    

    



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
    amp.setBounds(1000, 10, 400, 200);
    filter.setBounds(1000, 300, 400, 200);

    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;


    
}


