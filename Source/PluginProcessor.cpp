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
    return false;
}

bool MonolizrAudioProcessor::producesMidi() const
{
    return false;
}

bool MonolizrAudioProcessor::isMidiEffect() const
{
    return false;
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
    juce::ignoreUnused(index);
}

const juce::String MonolizrAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused(index);
    return {};
}

void MonolizrAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused(index);
    juce::ignoreUnused(newName);
}

//==============================================================================
void MonolizrAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(sampleRate);
    juce::ignoreUnused(samplesPerBlock);
    min = 1;
    max = -1;
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
    return true;
}

juce::AudioProcessorEditor* MonolizrAudioProcessor::createEditor()
{
    return new MonolizrAudioProcessorEditor (*this);
}

//==============================================================================
void MonolizrAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::ignoreUnused(destData);
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MonolizrAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    juce::ignoreUnused(data);
    juce::ignoreUnused(sizeInBytes);
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
    juce::ignoreUnused(midiMessages);
    jassert(buffer.getNumChannels() == 2);

    const float amount = mononess / 200.0f; // from 0.0 to 0.5
    const int numSamples = buffer.getNumSamples();
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    //--- mix channels according to 'amount' (0.0 .. 0.5)
    for (int i = 0; i < numSamples; ++i)
    {
        const float left = leftChannel[i];
        const float right = rightChannel[i];

        min = fmin(min, fmin(left, right));
        max = fmax(max, fmax(left, right));

        leftChannel[i] = left * (1 - amount) + right * amount;
        rightChannel[i] = right * (1 - amount) + left * amount;
    }

    //--- for full mono move signal to parameter 'position' (-100 (L) .. +100 (R))
    //--- else move to center gradually
    m = mononess / 100.0f; // from 0.0 to 1.0
    p = position / 100.0f; // from -1.0 to +1.0
    mp = m * p;
    mp2 = mp * 0.5f;

    //--- for full stereo or centered balance we're done
    if (mononess < 1 || fabs(position) < 1)
        return;

    if (p < 0) //--- to the left
    {
        for (int i = 0; i < numSamples; ++i)
        {
            //--- decrease right channel
            rightChannel[i] *= (1 + mp);

            //--- increase left channel
            leftChannel[i] *= (1 - mp2);
        }
    }
    else // to the right
    {
        for (int i = 0; i < numSamples; ++i)
        {
            //--- decrease left channel
            leftChannel[i] *= (1 - mp);

            //--- increase right channel
            rightChannel[i] *= (1 + mp2);
        }
    }
}
