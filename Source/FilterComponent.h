/*
  ==============================================================================

    FilterComponent.h
    Created: 20 Mar 2024 2:50:33pm
    Author:  jmast

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterComponent : public juce::Component {

public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String freqID, juce::String resID, juce::String typeID, juce::String powerID);
    ~FilterComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;



private:
    juce::Slider freq;
    juce::Slider res;
    juce::ComboBox type;
    juce::ToggleButton power;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> powerAttachment;

};
