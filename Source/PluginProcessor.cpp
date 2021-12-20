/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstProjectAudioProcessor::FirstProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

FirstProjectAudioProcessor::~FirstProjectAudioProcessor()
{
}

//==============================================================================
const juce::String FirstProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FirstProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FirstProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FirstProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FirstProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FirstProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FirstProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FirstProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FirstProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void FirstProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FirstProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void FirstProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FirstProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FirstProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear(); // clear whatever is in the current audio buffer
 
    juce::MidiBuffer processedMidi; // new midi buffer to hold new information
 
    for (const auto metadata : midiMessages) // iterate through midi buffer
    {
        // get the message and time from the buffer
        auto message = metadata.getMessage();
        const auto time = metadata.samplePosition;
        // if the note is currently being played, get information about it
        if (message.isNoteOn())
        {
            message = juce::MidiMessage::noteOn (message.getChannel(),
                                                 message.getNoteNumber(),
                                                 (juce::uint8) noteOnVel);
        }
        // pass the event to the new midi buffer
        processedMidi.addEvent (message, time);
    }
    // swap the current buffer with the modified one
    midiMessages.swapWith (processedMidi);
}

//==============================================================================
bool FirstProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FirstProjectAudioProcessor::createEditor()
{
    return new FirstProjectAudioProcessorEditor (*this);
}

//==============================================================================
void FirstProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FirstProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FirstProjectAudioProcessor();
}
