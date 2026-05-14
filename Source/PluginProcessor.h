#pragma once

#include <JuceHeader.h>

using namespace std::chrono;

//==============================================================================
/**
*/
class MonolizrAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MonolizrAudioProcessor();
    ~MonolizrAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    /// <summary>
    /// The amount of signal being mono in percent (0 = full stereo, 100 = full mono).
    /// </summary>
    float mononess = 0;

    /// <summary>
    /// The position of the full mono signal between -100 (full left) and +100 (full right).
    /// </summary>
    float position = 0;

    /// <summary>
    /// The additional gain of the full mono signal between 0 and 100.
    /// </summary>
    float monogain = 0;

    std::string version = "v0.7";

    float m, p, mp, mp2;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonolizrAudioProcessor)
};
