/*
  ==============================================================================

    OscComponent.h
    Created: 28 Feb 2024 1:08:30pm
    Author:  jmast

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorID, juce::String transposeSelectorID, juce::String detuneSelectorID,
        juce::String phaseSelectorID);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::ComboBox oscWaveSelector;
    juce::Slider oscTranspose;
    juce::Slider oscDetune;
    juce::Slider oscPhase;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscTransposeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscDetuneAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscPhaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
