/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.h"

//==============================================================================
class XTCplugin2025CAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    XTCplugin2025CAudioProcessorEditor(XTCplugin2025CAudioProcessor&);
    ~XTCplugin2025CAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // Esta referencia nos permite comunicarnos con el procesador de audio.
    XTCplugin2025CAudioProcessor& audioProcessor;

    // --- COMPONENTES DE LA GUI ---
    juce::Slider dSlider;
    juce::Slider dpSlider;
    juce::Slider doSlider;
    juce::Slider betaSlider;

    // --- ETIQUETAS PARA LOS SLIDERS ---
    juce::Label dLabel;
    juce::Label dpLabel;
    juce::Label doLabel;
    juce::Label betaLabel;

    // --- CONEXIONES AUTOMÁTICAS ---
    // Estos objetos "atan" un slider a un parámetro del APVTS. ¡Magia!
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> dAttachment;
    std::unique_ptr<SliderAttachment> dpAttachment;
    std::unique_ptr<SliderAttachment> doAttachment;
    std::unique_ptr<SliderAttachment> betaAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XTCplugin2025CAudioProcessorEditor)
};

