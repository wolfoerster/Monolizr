#include <string>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MonolizrAudioProcessorEditor::MonolizrAudioProcessorEditor (MonolizrAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (360, 200);
    InitSlider(monoSlider);
    InitSlider(posiSlider);
}

MonolizrAudioProcessorEditor::~MonolizrAudioProcessorEditor()
{
}

//==============================================================================

void MonolizrAudioProcessorEditor::InitSlider(juce::Slider& slider)
{
    //slider.setSliderStyle(juce::Slider::LinearBar);
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    slider.setPopupDisplayEnabled(true, false, this);
    slider.setTextValueSuffix(" %");
    slider.setValue(0.0);

    if (&slider == &monoSlider)
    {
        slider.setRange(0.0, 100.0, 1.0);
    }
    else
    {
        slider.setRange(-100.0, 100.0, 1.0);
    }

    addAndMakeVisible(slider);
    slider.addListener(this);
}

void MonolizrAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &monoSlider)
        audioProcessor.mononess = (float)monoSlider.getValue();
    else
        audioProcessor.position = (float)posiSlider.getValue();
}

void MonolizrAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);
    g.setColour(juce::Colours::black);
    g.setFont(15.0f);
    //g.drawFittedText("Mononess", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
    //g.drawFittedText("Balance", 0, 60, getWidth(), 30, juce::Justification::centred, 1);

    std::string str = std::to_string(audioProcessor.maxSample);
    //g.drawFittedText(str, 0, 130, getWidth(), 30, juce::Justification::centred, 1);
}

void MonolizrAudioProcessorEditor::resized()
{
    monoSlider.setBounds(10, 30, 100, 100);
    posiSlider.setBounds(150, 30, 100, 100);
}
