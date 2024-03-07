/*
  ==============================================================================

    FilterComponent.h
    Created: 6 Mar 2024 5:15:03pm
    Author:  jmast

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String attackID, juce::String decayID, juce::String sustainID, juce::String releaseID);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

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



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
