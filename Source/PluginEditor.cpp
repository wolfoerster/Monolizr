#include <string>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MonolizrAudioProcessorEditor::MonolizrAudioProcessorEditor (MonolizrAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(240, 128);
    initSlider(monoSlider);
    initSlider(posiSlider);
}

MonolizrAudioProcessorEditor::~MonolizrAudioProcessorEditor()
{
}

//==============================================================================

void MonolizrAudioProcessorEditor::initSlider(juce::Slider& slider)
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
    g.setFont(12.0f);
    g.drawSingleLineText(audioProcessor.version, getWidth() - 2, 10, juce::Justification::right);

    showSlider(g, monoSlider, "Mode", "Stereo", "Mono ");
    showSlider(g, posiSlider, "Balance", "   Left", "Right ");
}

void MonolizrAudioProcessorEditor::showSlider(
    juce::Graphics& g,
    juce::Slider& slider,
    juce::String name, 
    juce::String lowLabel, 
    juce::String highLabel)
{
    auto bounds = slider.getBounds();
    const int x1 = bounds.getX();
    const int x2 = x1 + bounds.getWidth();
    const int y1 = bounds.getY();
    const int y2 = y1 + bounds.getHeight();

    g.setFont(18.0f);
    g.drawSingleLineText(name, (x1 + x2) / 2, y1 + 2, juce::Justification::centred);

    g.setFont(15.0f);
    g.drawSingleLineText(lowLabel, x1, y2, juce::Justification::left);

    g.setFont(15.0f);
    g.drawSingleLineText(highLabel, x2, y2, juce::Justification::right);
}

void MonolizrAudioProcessorEditor::resized()
{
    monoSlider.setBounds(10, 20, 100, 100);
    posiSlider.setBounds(130, 20, 100, 100);
}
