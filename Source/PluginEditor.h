/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OscComponent.h"
#include "Oscilloscope.h"


//==============================================================================
/**
*/
class MIDISynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MIDISynthAudioProcessorEditor (MIDISynthAudioProcessor&);
    ~MIDISynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MIDISynthAudioProcessor& audioProcessor;
    OscComponent osc;
    OscComponent osc2;

    juce::Slider attSelect;
    juce::Slider susSelect;
    juce::Slider decSelect;
    juce::Slider relSelect;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> attAttachment;
    std::unique_ptr<SliderAttachment> susAttachment;
    std::unique_ptr<SliderAttachment> decAttachment;
    std::unique_ptr<SliderAttachment> relAttachment;

    void setSlider(juce::Slider& slider);

    ScopeComponent<float> oscScope;
    AudioBufferQueue<float> audioBufferQueue;
    ScopeDataCollector<float> scopeDataCollector{ audioBufferQueue };

    



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDISynthAudioProcessorEditor)
};
