#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MonolizrAudioProcessorEditor  : public juce::AudioProcessorEditor,
    private juce::Slider::Listener
{
public:
    MonolizrAudioProcessorEditor (MonolizrAudioProcessor&);
    ~MonolizrAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void showSlider(
        juce::Graphics& g, 
        juce::Slider& slider, 
        juce::String name, 
        juce::String lowLabel,
        juce::String highLabel);

private:
    juce::Slider monoSlider;
    juce::Slider posiSlider;
    void initSlider(juce::Slider& monoSlider);
    void sliderValueChanged(juce::Slider* slider) override;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MonolizrAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonolizrAudioProcessorEditor)
};
