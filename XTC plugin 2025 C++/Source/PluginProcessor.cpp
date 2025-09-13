/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
XTCplugin2025CAudioProcessor::XTCplugin2025CAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    // La llamada expl�cita y correcta a la funci�n est�tica.
    parameters(*this, nullptr, "Parameters", XTCplugin2025CAudioProcessor::crearLayers())
#endif
{
    xtc_wrapper_initialize();
}

XTCplugin2025CAudioProcessor::~XTCplugin2025CAudioProcessor()
{
    xtc_wrapper_terminate();
}

// --- DEFINICI�N DE PAR�METROS ---
// La definici�n de la funci�n est�tica.
juce::AudioProcessorValueTreeState::ParameterLayout XTCplugin2025CAudioProcessor::crearLayers()
{
    // Usamos la sintaxis de lista de inicializaci�n para construir el layout directamente.
    return {
        std::make_unique<juce::AudioParameterFloat>("D",    "Dist. Altavoz-Oido", 0.5f, 2.0f, 1.0f),
        std::make_unique<juce::AudioParameterFloat>("DP",   "Dist. entre Altavoces", 0.1f, 1.0f, 0.2f),
        std::make_unique<juce::AudioParameterFloat>("DO",   "Dist. entre Oidos", 0.1f, 0.3f, 0.18f),
        std::make_unique<juce::AudioParameterFloat>("BETA", "Regularizacion", 0.0001f, 0.1f, 0.01f)
    };
}

//==============================================================================
const juce::String XTCplugin2025CAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool XTCplugin2025CAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool XTCplugin2025CAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool XTCplugin2025CAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double XTCplugin2025CAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int XTCplugin2025CAudioProcessor::getNumPrograms()
{
    return 1;
}

int XTCplugin2025CAudioProcessor::getCurrentProgram()
{
    return 0;
}

void XTCplugin2025CAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String XTCplugin2025CAudioProcessor::getProgramName(int index)
{
    return {};
}

void XTCplugin2025CAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void XTCplugin2025CAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    dspParameters.SampleRate = static_cast<double>(sampleRate);
}

void XTCplugin2025CAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool XTCplugin2025CAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    return true;
#endif
}
#endif

void XTCplugin2025CAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // --- ACTUALIZAR PAR�METROS DEL DSP ---
    dspParameters.D = *parameters.getRawParameterValue("D");
    dspParameters.dp = *parameters.getRawParameterValue("DP");
    dspParameters.b_do = *parameters.getRawParameterValue("DO");
    dspParameters.beta = *parameters.getRawParameterValue("BETA");

    // --- BUCLE DE PROCESAMIENTO ---
    const float* inputL = buffer.getReadPointer(0);
    const float* inputR = (totalNumInputChannels > 1) ? buffer.getReadPointer(1) : nullptr;
    float* outputL = buffer.getWritePointer(0);
    float* outputR = (totalNumOutputChannels > 1) ? buffer.getWritePointer(1) : nullptr;
    int numSamples = buffer.getNumSamples();

    // 1. Convertir entrada de JUCE a formato MATLAB
    std::vector<double> inputInterleaved(numSamples * 2);
    for (int i = 0; i < numSamples; ++i)
    {
        inputInterleaved[i * 2] = static_cast<double>(inputL[i]);
        if (inputR) inputInterleaved[i * 2 + 1] = static_cast<double>(inputR[i]);
        else        inputInterleaved[i * 2 + 1] = static_cast<double>(inputL[i]);
    }

    coder::array<double, 2U> matlabInput;
    matlabInput.set(inputInterleaved.data(), numSamples, 2);

    // 2. Llamar a la funci�n wrapper de MATLAB
    coder::array<double, 2U> matlabOutput;
    xtc_wrapper(matlabInput, &dspParameters, matlabOutput);

    // 3. Convertir salida de MATLAB de vuelta a formato JUCE
    for (int i = 0; i < numSamples; ++i)
    {
        outputL[i] = static_cast<float>(matlabOutput[i * 2]);
        if (outputR) outputR[i] = static_cast<float>(matlabOutput[i * 2 + 1]);
    }
}

//==============================================================================
bool XTCplugin2025CAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* XTCplugin2025CAudioProcessor::createEditor()
{
    return new XTCplugin2025CAudioProcessorEditor(*this);
}

//==============================================================================
void XTCplugin2025CAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // ...
}

void XTCplugin2025CAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // ...
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new XTCplugin2025CAudioProcessor();
}

