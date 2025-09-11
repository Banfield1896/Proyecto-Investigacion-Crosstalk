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
    // 1. Inicializar la estructura de parámetros con valores por defecto
    // al construir el plugin.
    dspParameters.D = 1.0;
    dspParameters.dp = 0.2;
    dspParameters.b_do = 0.18;
    dspParameters.beta = 0.01;
    // La frecuencia de muestreo se establecerá en prepareToPlay.
    dspParameters.SampleRate = 44100.0;

    // Llamar a la función de inicialización generada por Coder.
    // Esto prepara el estado persistente dentro del wrapper.
    xtc_wrapper_initialize();
}

XTCplugin2025CAudioProcessor::~XTCplugin2025CAudioProcessor()
{
    // Llamar a la función de terminación para liberar recursos.
    xtc_wrapper_terminate();
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
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int XTCplugin2025CAudioProcessor::getCurrentProgram()
{
    return 0;
}

void XTCplugin2025CAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String XTCplugin2025CAudioProcessor::getProgramName (int index)
{
    return {};
}

void XTCplugin2025CAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void XTCplugin2025CAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Cuando el DAW informa la frecuencia de muestreo y el tamaño del bloque,
    // simplemente actualizamos nuestra estructura de parámetros.
    // El motor DSP de MATLAB se configurará automáticamente en la primera
    // llamada a processBlock (step), usando este valor de SampleRate.
    dspParameters.SampleRate = static_cast<double>(sampleRate);
}

void XTCplugin2025CAudioProcessor::releaseResources()
{
    // El motor DSP de MATLAB se limpia automáticamente cuando el objeto
    // dspEngine es destruido (su destructor es llamado). No es necesario
    // llamar a una función de terminación explícita.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool XTCplugin2025CAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void XTCplugin2025CAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // --- BUCLE DE PROCESAMIENTO ---

    const float* inputL = buffer.getReadPointer(0);
    const float* inputR = (totalNumInputChannels > 1) ? buffer.getReadPointer(1) : nullptr;
    float* outputL = buffer.getWritePointer(0);
    float* outputR = (totalNumOutputChannels > 1) ? buffer.getWritePointer(1) : nullptr;
    int numSamples = buffer.getNumSamples();

    // 1. Convertir entrada de JUCE (float, separado) a MATLAB (double, intercalado)
    std::vector<double> inputInterleaved(numSamples * 2);
    for (int i = 0; i < numSamples; ++i)
    {
        inputInterleaved[i * 2] = static_cast<double>(inputL[i]);
        if (inputR) inputInterleaved[i * 2 + 1] = static_cast<double>(inputR[i]);
        else        inputInterleaved[i * 2 + 1] = static_cast<double>(inputL[i]);
    }

    coder::array<double, 2U> matlabInput;
    matlabInput.set(inputInterleaved.data(), numSamples, 2);

    // 2. Crear un array para la salida y LLAMAR A LA FUNCIÓN WRAPPER
    coder::array<double, 2U> matlabOutput;
    xtc_wrapper(matlabInput, &dspParameters, matlabOutput);

    // 3. Convertir salida de MATLAB (double, intercalado) de vuelta a JUCE (float, separado)
    for (int i = 0; i < numSamples; ++i)
    {
        outputL[i] = static_cast<float>(matlabOutput[i * 2]);
        if (outputR) outputR[i] = static_cast<float>(matlabOutput[i * 2 + 1]);
    }
}

//==============================================================================
bool XTCplugin2025CAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* XTCplugin2025CAudioProcessor::createEditor()
{
    return new XTCplugin2025CAudioProcessorEditor (*this);
}

//==============================================================================
void XTCplugin2025CAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void XTCplugin2025CAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new XTCplugin2025CAudioProcessor();
}
