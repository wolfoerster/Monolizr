#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MonolizrAudioProcessor::MonolizrAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       )
{
}

MonolizrAudioProcessor::~MonolizrAudioProcessor()
{
}

//==============================================================================
const juce::String MonolizrAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MonolizrAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MonolizrAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MonolizrAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MonolizrAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MonolizrAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MonolizrAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MonolizrAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MonolizrAudioProcessor::getProgramName (int index)
{
    return {};
}

void MonolizrAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MonolizrAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MonolizrAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool MonolizrAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // Only stereo in / stereo out is supported.
    return layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo()
        && layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

//==============================================================================
bool MonolizrAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MonolizrAudioProcessor::createEditor()
{
    return new MonolizrAudioProcessorEditor (*this);
}

//==============================================================================
void MonolizrAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MonolizrAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MonolizrAudioProcessor();
}

/// <summary>
/// This is the core method to modify the stereo signal.
/// </summary>
void MonolizrAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    jassert(buffer.getNumChannels() == 2);

    //--- mix channels according parameter 'mononess' (0 .. 100)
    const float amount = mononess / 200.0f; // from 0.0 to 0.5
    const int numSamples = buffer.getNumSamples();
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    for (int i = 0; i < numSamples; ++i)
    {
        const float left = leftChannel[i];
        const float right = rightChannel[i];

        leftChannel[i] = left * (1 - amount) + right * amount;
        rightChannel[i] = right * (1 - amount) + left * amount;
    }

    //--- for full stereo we're done
    if (mononess < 1)
        return;

    //--- for full mono move signal to parameter 'position' (-100 (L) .. +100 (R))
    //--- else move to center gradually
    const float m = mononess / 100.0f; // from 0.0 to 1.0
    const float p = position / 100.0f; // from -1.0 to +1.0
    const float mm = m * m;
    const float mp = m * p;

    if (p < 0) // to the left
    {
        for (int i = 0; i < numSamples; ++i)
        {
            leftChannel[i] *= (1 + mm);
            rightChannel[i] *= (1 + mp);
        }
    }
    else
    {
        for (int i = 0; i < numSamples; ++i)
        {
            leftChannel[i] *= (1 - mp);
            rightChannel[i] *= (1 + mm);
        }
    }
}
