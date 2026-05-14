#pragma once

#include <chrono>
#include <fstream>
#include <string>
#include <stdexcept>
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
    /// The amount of signal being mono in percent (0 = stereo, 100 = mono).
    /// </summary>
    float mononess = 0;

    /// <summary>
    /// The position of the mono signal between -100 (full left) and +100 (full right).
    /// </summary>
    float position = 0;

    std::string version = "v0.5";

private:
    const std::string filename = "c:\\temp\\monolizr.log";

    void log(double m, double p)
    {
        auto mm = m * m;
        auto mp = m * p;
        auto now = toString(system_clock::now());

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(6) << now << ", m:" << m << ", mm:" << mm << ", p:" << p << ", mp:" << mp;
        auto text = oss.str();

        std::ofstream file(filename, std::ios::app);
        if (file.is_open())
        {
            file << text << '\n';
            file.close();
        }
    }

    std::string toString(const std::chrono::system_clock::time_point& tp) {
        std::time_t t = std::chrono::system_clock::to_time_t(tp);
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&t), "%H:%M:%S");
        return oss.str();
    }

    steady_clock::time_point t0 = steady_clock::now();

    bool secondsPassed(double limit)
    {
        auto t1 = steady_clock::now();
        auto diff = duration_cast<seconds>(t1 - t0).count();

        if (diff > limit)
        {
            t0 = t1;
            return true;
        }

        return false;
    }

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MonolizrAudioProcessor)
};
