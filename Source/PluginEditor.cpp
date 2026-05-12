#include <string>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MonolizrAudioProcessorEditor::MonolizrAudioProcessorEditor (MonolizrAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(240, 132);
    InitSlider(monoSlider);
    InitSlider(posiSlider);
}

MonolizrAudioProcessorEditor::~MonolizrAudioProcessorEditor()
{
}

//==============================================================================

void MonolizrAudioProcessorEditor::InitSlider(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    slider.setPopupDisplayEnabled(true, false, this);
    slider.setValue(0.0);

    if (&slider == &monoSlider)
    {
        slider.setTextValueSuffix(" %");
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

    LabelSlider(g, monoSlider, "Mononess", "Stereo", "Mono ");
    LabelSlider(g, posiSlider, "Balance", "   Left", "Right ");
}

void MonolizrAudioProcessorEditor::LabelSlider(
    juce::Graphics& g,
    juce::Slider& slider,
    juce::String name, 
    juce::String lowLabel, 
    juce::String highLabel)
{
    auto bounds = slider.getBounds();
    const int x = bounds.getX();
    const int y = bounds.getY();
    const int w = bounds.getWidth();
    const int h = bounds.getHeight();

    g.setFont(18.0f);
    g.drawText(name, x, y - 15, w, h, juce::Justification::centredTop, 1);

    g.setFont(14.0f);
    g.drawText(lowLabel, x, y, w, h, juce::Justification::bottomLeft, 1);
    g.drawText(highLabel, x, y, w, h, juce::Justification::bottomRight, 1);
}

void MonolizrAudioProcessorEditor::resized()
{
    monoSlider.setBounds(10, 20, 100, 100);
    posiSlider.setBounds(130, 20, 100, 100);
}
