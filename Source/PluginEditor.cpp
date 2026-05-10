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
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 200);

    midiVolume.setSliderStyle(juce::Slider::LinearBarVertical);
    midiVolume.setRange(0.0, 100.0, 1.0);
    midiVolume.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    midiVolume.setPopupDisplayEnabled(true, false, this);
    midiVolume.setTextValueSuffix(" Volume");
    midiVolume.setValue(1.0);

    addAndMakeVisible(&midiVolume);
    midiVolume.addListener(this);
}

MonolizrAudioProcessorEditor::~MonolizrAudioProcessorEditor()
{
}

//==============================================================================
void MonolizrAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    audioProcessor.noteOnVel = (float)midiVolume.getValue();
}

void MonolizrAudioProcessorEditor::paint (juce::Graphics& g)
{
    // fill the whole window white
    g.fillAll(juce::Colours::white);
    // set the current drawing colour to black
    g.setColour(juce::Colours::black);
    // set the font size and draw text to the screen
    g.setFont(15.0f);
    g.drawFittedText("Midi Volume", 0, 0, getWidth(), 30, juce::Justification::centred, 1);

    //std::string str = std::to_string(audioProcessor.noteOnVel);
    //g.drawFittedText(str, 0, 30, getWidth(), 30, juce::Justification::centred, 1);
}

void MonolizrAudioProcessorEditor::resized()
{
    midiVolume.setBounds(40, 30, 20, getHeight() - 60);
}
