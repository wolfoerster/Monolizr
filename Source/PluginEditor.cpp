/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include <string>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MonolizrAudioProcessorEditor::MonolizrAudioProcessorEditor (MonolizrAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (360, 200);

    monoSlider.setSliderStyle(juce::Slider::LinearBar);
    monoSlider.setRange(0.0, 100.0, 1.0);
    monoSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    monoSlider.setPopupDisplayEnabled(true, false, this);
    monoSlider.setTextValueSuffix(" %");
    monoSlider.setValue(0.0);

    addAndMakeVisible(&monoSlider);
    monoSlider.addListener(this);
}

MonolizrAudioProcessorEditor::~MonolizrAudioProcessorEditor()
{
}

//==============================================================================
void MonolizrAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    audioProcessor.mononess = (float)monoSlider.getValue();
}

void MonolizrAudioProcessorEditor::paint (juce::Graphics& g)
{
    // fill the whole window white
    g.fillAll(juce::Colours::white);
    // set the current drawing colour to black
    g.setColour(juce::Colours::black);
    // set the font size and draw text to the screen
    g.setFont(15.0f);
    g.drawFittedText("Amount of Mono", 0, 0, getWidth(), 30, juce::Justification::centred, 1);

    std::string str = std::to_string(audioProcessor.numChannels);
    g.drawFittedText(str, 0, 130, getWidth(), 30, juce::Justification::centred, 1);
}

void MonolizrAudioProcessorEditor::resized()
{
    monoSlider.setBounds(10, 30, getWidth() - 20, 20);
}
