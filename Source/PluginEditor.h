#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MonolizrAudioProcessorEditor  : public juce::AudioProcessorEditor,
    private juce::Slider::Listener, public juce::Timer
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

    void timerCallback() override
    {
        std::ostringstream oss;
        oss << str(audioProcessor.min, 3) << ", "
            << str(audioProcessor.max, 3) << ", "
            << audioProcessor.numSamples << ", m:"
            << str(audioProcessor.m, 2) << ", p:"
            << str(audioProcessor.p, 2) << ", mp:"
            << str(audioProcessor.mp, 2) << ", mp2:"
            << str(audioProcessor.mp2, 4);

        label.setText(oss.str(), juce::NotificationType::dontSendNotification);
    }

private:
    juce::Slider monoSlider;
    juce::Slider posiSlider;
    juce::Label label;
    void initSlider(juce::Slider& monoSlider);
    void sliderValueChanged(juce::Slider* slider) override;

    std::string str(double a, int precision = 6) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision) << a;
        return oss.str();
    }

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MonolizrAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonolizrAudioProcessorEditor)
};
