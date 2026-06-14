/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VolumeFaderAudioProcessorEditor::VolumeFaderAudioProcessorEditor(VolumeFaderAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 200);
    midiVolume.setSliderStyle(juce::Slider::LinearBarVertical);
    midiVolume.setRange(0.0, 127.0, 1.0);
    midiVolume.setValue(0.0);
    midiVolume.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    midiVolume.setPopupDisplayEnabled(true, false, this);
    midiVolume.setTextValueSuffix("Volume");
    midiVolume.addListener(this);
    
    Bypass.onClick = [this]
    {
        audioProcessor.Bypass = Bypass.getToggleState();
    };
    addAndMakeVisible(&midiVolume);
    addAndMakeVisible(&Bypass);
}

VolumeFaderAudioProcessorEditor::~VolumeFaderAudioProcessorEditor()
{
}

//==============================================================================
void VolumeFaderAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawFittedText("Midi Volume", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
    g.setFont(15.0f);

}

void VolumeFaderAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    midiVolume.setBounds(40, 30, 20, getHeight() - 60);
    Bypass.setBounds(100,juce::Justification::centred,80,40); 
}
void VolumeFaderAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    audioProcessor.NoteOnVelocity = midiVolume.getValue();
}