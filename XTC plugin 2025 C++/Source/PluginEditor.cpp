/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
XTCplugin2025CAudioProcessorEditor::XTCplugin2025CAudioProcessorEditor(XTCplugin2025CAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // --- CONFIGURAR SLIDERS ---
    for (auto* slider : { &dSlider, &dpSlider, &doSlider, &betaSlider })
    {
        slider->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        slider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
        addAndMakeVisible(slider);
    }

    // --- CONFIGURAR ETIQUETAS ---
    dLabel.setText("Dist. Altavoz-Oido", juce::dontSendNotification);
    dpLabel.setText("Dist. entre Altavoces", juce::dontSendNotification);
    doLabel.setText("Dist. entre Oidos", juce::dontSendNotification);
    betaLabel.setText("Regularizacion", juce::dontSendNotification);

    for (auto* label : { &dLabel, &dpLabel, &doLabel, &betaLabel })
    {
        label->setJustificationType(juce::Justification::centred);
        addAndMakeVisible(label);
    }

    // --- CONECTAR SLIDERS A PARÁMETROS (LA MAGIA) ---
    dAttachment = std::make_unique<SliderAttachment>(audioProcessor.APVTS, "D", dSlider);
    dpAttachment = std::make_unique<SliderAttachment>(audioProcessor.APVTS, "DP", dpSlider);
    doAttachment = std::make_unique<SliderAttachment>(audioProcessor.APVTS, "DO", doSlider);
    betaAttachment = std::make_unique<SliderAttachment>(audioProcessor.APVTS, "BETA", betaSlider);

    // Establecer el tamaño de la ventana del plugin
    setSize(500, 200);
}

XTCplugin2025CAudioProcessorEditor::~XTCplugin2025CAudioProcessorEditor()
{
}

//==============================================================================
void XTCplugin2025CAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Rellenar el fondo con un color oscuro
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void XTCplugin2025CAudioProcessorEditor::resized()
{
    // Organizar los componentes en una fila horizontal
    juce::FlexBox flexBox;
    flexBox.flexDirection = juce::FlexBox::Direction::row;
    flexBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    flexBox.alignItems = juce::FlexBox::AlignItems::center;

    // Crear un "box" para cada par de etiqueta y slider
    for (auto* slider : { &dSlider, &dpSlider, &doSlider, &betaSlider })
    {
        juce::FlexBox itemBox;
        itemBox.flexDirection = juce::FlexBox::Direction::column;
        itemBox.alignItems = juce::FlexBox::AlignItems::center;

        // Determinar qué etiqueta corresponde a cada slider
        juce::Label* correspondingLabel = nullptr;
        if (slider == &dSlider) correspondingLabel = &dLabel;
        if (slider == &dpSlider) correspondingLabel = &dpLabel;
        if (slider == &doSlider) correspondingLabel = &doLabel;
        if (slider == &betaSlider) correspondingLabel = &betaLabel;

        itemBox.items.add(juce::FlexItem(*correspondingLabel).withHeight(20.0f).withWidth(100.0f));
        itemBox.items.add(juce::FlexItem(*slider).withHeight(100.0f).withWidth(100.0f));

        flexBox.items.add(juce::FlexItem(itemBox).withFlex(1.0f));
    }

    flexBox.performLayout(getLocalBounds().toFloat());
}