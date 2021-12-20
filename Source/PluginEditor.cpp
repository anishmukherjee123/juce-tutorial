/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstProjectAudioProcessorEditor::FirstProjectAudioProcessorEditor (FirstProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 200);
    
    // set attributes of the slider
    midiVolume.setSliderStyle (juce::Slider::LinearBarVertical); // style of slider (vertical)
    midiVolume.setRange (0.0, 127.0, 1.0); // value range
    midiVolume.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0); // no label
    midiVolume.setPopupDisplayEnabled (true, false, this); //
    midiVolume.setTextValueSuffix (" Volume");
    midiVolume.setValue(1.0);
    // make the slide visible
    addAndMakeVisible(&midiVolume);
}

FirstProjectAudioProcessorEditor::~FirstProjectAudioProcessorEditor()
{
}

//==============================================================================
void FirstProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::white);

    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("MIDI Volume", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void FirstProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    // position of slider
    midiVolume.setBounds(40, 30, 20, getHeight() - 60);
}
