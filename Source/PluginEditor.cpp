#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MonolizrAudioProcessorEditor::MonolizrAudioProcessorEditor (MonolizrAudioProcessor& p)
    : AudioProcessorEditor (&p), 
    audioProcessor (p), 
    monoAttachment(p.parameters, p.MononessId, monoSlider),
    posiAttachment(p.parameters, p.PositionId, posiSlider),
    addiAttachment(p.parameters, p.AdditionId, addiSlider)
{
#if DEBUG
    setSize(360, 160);
#else
    setSize(360, 132);
#endif
    initSlider(monoSlider);
    initSlider(posiSlider);
    initSlider(addiSlider);

    addAndMakeVisible(label);
    label.setColour(juce::Label::textColourId, juce::Colours::black);
    label.setJustificationType(juce::Justification::centred);

#if DEBUG
    startTimer(500);
#endif
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
    slider.setTextValueSuffix(" %");
    addAndMakeVisible(slider);
}

void MonolizrAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);
    g.setColour(juce::Colours::black);
    g.setFont(12.0f);
    g.drawSingleLineText(audioProcessor.version, getWidth() / 2, 10, juce::Justification::horizontallyCentred);

    showSlider(g, monoSlider, "Mode", "Stereo", "Mono ");
    showSlider(g, posiSlider, "Balance", "   Left", "Right ");
    showSlider(g, addiSlider, "B-Gain", "  None", "Full    ");
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
    g.drawSingleLineText(name, (x1 + x2) / 2, y1 + 2, juce::Justification::horizontallyCentred);

    g.setFont(15.0f);
    g.drawSingleLineText(lowLabel, x1, y2, juce::Justification::left);

    g.setFont(15.0f);
    g.drawSingleLineText(highLabel, x2, y2, juce::Justification::right);
}

void MonolizrAudioProcessorEditor::resized()
{
    monoSlider.setBounds(10, 30, 100, 100);
    posiSlider.setBounds(130, 30, 100, 100);
    addiSlider.setBounds(250, 30, 100, 100);
    label.setBounds(10, 130, getWidth() - 20, 30);
}
