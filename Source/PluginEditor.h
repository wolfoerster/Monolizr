/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MonolizrAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MonolizrAudioProcessorEditor (MonolizrAudioProcessor&);
    ~MonolizrAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MonolizrAudioProcessor& audioProcessor;
    juce::Slider midiVolume;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonolizrAudioProcessorEditor)
};
