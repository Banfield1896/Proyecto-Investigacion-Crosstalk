/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class XTCplugin2025CAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    XTCplugin2025CAudioProcessorEditor (XTCplugin2025CAudioProcessor&);
    ~XTCplugin2025CAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    XTCplugin2025CAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XTCplugin2025CAudioProcessorEditor)
};
