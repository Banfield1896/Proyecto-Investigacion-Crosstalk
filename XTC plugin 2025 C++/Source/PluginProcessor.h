/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MATLAB/XTC_Processor.h"
#include "MATLAB/xtc_wrapper_types.h"
#include "MATLAB/xtc_wrapper.h"
#include "MATLAB/xtc_wrapper_initialize.h"
#include "MATLAB/xtc_wrapper_terminate.h"
#include "MATLAB/rtwtypes.h"

//==============================================================================
/**
*/
class XTCplugin2025CAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    XTCplugin2025CAudioProcessor();
    ~XTCplugin2025CAudioProcessor() override;

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

private:    
    struct0_T dspParameters;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XTCplugin2025CAudioProcessor)
};
