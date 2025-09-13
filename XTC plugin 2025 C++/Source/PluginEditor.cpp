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
    // Usamos el APVTS del procesador para crear las conexiones.
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
    // Esta función define la posición y el tamaño de tus componentes.
    // Usamos un FlexBox para organizarlos automáticamente en una fila.

    juce::FlexBox flexBox;
    flexBox.flexDirection = juce::FlexBox::Direction::row;
    flexBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    flexBox.alignItems = juce::FlexBox::AlignItems::center;

    // Un "box" para cada par de etiqueta y slider
    juce::FlexBox dBox, dpBox, doBox, betaBox;
    for (auto* box : { &dBox, &dpBox, &doBox, &betaBox })
    {
        box->flexDirection = juce::FlexBox::Direction::column;
        box->alignItems = juce::FlexBox::AlignItems::center;
    }

    dBox.items.add(juce::FlexItem(dLabel).withHeight(20.0f).withWidth(120.0f));
    dBox.items.add(juce::FlexItem(dSlider).withHeight(100.0f).withWidth(100.0f));

    dpBox.items.add(juce::FlexItem(dpLabel).withHeight(20.0f).withWidth(120.0f));
    dpBox.items.add(juce::FlexItem(dpSlider).withHeight(100.0f).withWidth(100.0f));

    doBox.items.add(juce::FlexItem(doLabel).withHeight(20.0f).withWidth(120.0f));
    doBox.items.add(juce::FlexItem(doSlider).withHeight(100.0f).withWidth(100.0f));

    betaBox.items.add(juce::FlexItem(betaLabel).withHeight(20.0f).withWidth(120.0f));
    betaBox.items.add(juce::FlexItem(betaSlider).withHeight(100.0f).withWidth(100.0f));

    flexBox.items.add(juce::FlexItem(dBox).withFlex(1.0f));
    flexBox.items.add(juce::FlexItem(dpBox).withFlex(1.0f));
    flexBox.items.add(juce::FlexItem(doBox).withFlex(1.0f));
    flexBox.items.add(juce::FlexItem(betaBox).withFlex(1.0f));

    flexBox.performLayout(getLocalBounds().reduced(10).toFloat());
}