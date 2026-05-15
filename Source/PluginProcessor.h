#pragma once

#include <JuceHeader.h>

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

    const std::string MononessId = "MononessId";
    const std::string PositionId = "PositionId";

    std::string version = "v0.7.12";
    juce::AudioProcessorValueTreeState parameters;
    float m = 0, p = 0, mp = 0, min = 1, max = -1;

private:
    std::atomic<float>* mononessParameter = nullptr;
    std::atomic<float>* positionParameter = nullptr;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonolizrAudioProcessor)
};
