/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OscComponent.h"
#include "AmpComponent.h"
#include "FilterComponent.h"
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

    AmpComponent amp;

    FilterComponent filter;
    

    ScopeComponent<float> oscScope;
    AudioBufferQueue<float> audioBufferQueue;
    ScopeDataCollector<float> scopeDataCollector{ audioBufferQueue };

    



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDISynthAudioProcessorEditor)
};
