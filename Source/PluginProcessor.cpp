/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MIDISynthAudioProcessor::MIDISynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ), apvts(*this, nullptr, "Parameters", createParams())
#endif
{

    synth.addSound(new SynthSound());
    
    for (int i = 0; i < 4; i++) {
        synth.addVoice(new SynthVoice());
    }
    
}

MIDISynthAudioProcessor::~MIDISynthAudioProcessor()
{
}

//==============================================================================
const juce::String MIDISynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MIDISynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MIDISynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MIDISynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MIDISynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MIDISynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MIDISynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MIDISynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MIDISynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void MIDISynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MIDISynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<SynthVoice*> (synth.getVoice(i))) {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void MIDISynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MIDISynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MIDISynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    buffer.clear();

    for (int i = 0; i < synth.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<SynthVoice*> (synth.getVoice(i))) {

            //osc controls
            //adsr

            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");


            auto& wave = *apvts.getRawParameterValue("OSC");
            auto& wave2 = *apvts.getRawParameterValue("OSC2");
            
            auto& detune = *apvts.getRawParameterValue("OSCDET");
            auto& detune2 = *apvts.getRawParameterValue("OSCDET2");

            auto& transpose = *apvts.getRawParameterValue("OSCTRANS");
            auto& transpose2 = *apvts.getRawParameterValue("OSCTRANS2");

            auto& phase = *apvts.getRawParameterValue("OSCPHASE");
            auto& phase2 = *apvts.getRawParameterValue("OSCPHASE2");

            auto& gain = *apvts.getRawParameterValue("OSCGAIN");
            auto& gain2 = *apvts.getRawParameterValue("OSCGAIN2");

            auto& freq = *apvts.getRawParameterValue("FILTERFREQ");
            auto& res = *apvts.getRawParameterValue("FILTERRES");
            auto& type = *apvts.getRawParameterValue("FILTERTYPE");
            auto& filterOn = *apvts.getRawParameterValue("FILTERON");

            voice->getAmp().setADSR(attack, decay, sustain, release);

            voice->getOsc().setWave(wave);
            voice->getOsc2().setWave(wave2);

            voice->getOsc().setDetuneValue(detune);
            voice->getOsc2().setDetuneValue(detune2);

            voice->getOsc().setTransposeValue(transpose);
            voice->getOsc2().setTransposeValue(transpose2);

            voice->getOsc().setPhase(phase * (2 * juce::MathConstants<float>::pi / 360));
            voice->getOsc2().setPhase(phase2 * (2 * juce::MathConstants<float>::pi / 360));

            voice->getOsc().setGain(gain);
            voice->getOsc2().setGain(gain2);

            
            voice->getFilterL().setFilter(freq, res, type);
            voice->getFilterL().isOn = filterOn;
            voice->getFilterR().setFilter(freq, res, type);
            voice->getFilterR().isOn = filterOn;

            //LFO

        }
    }

    

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    scopeDataCollector.process(buffer.getReadPointer(0), buffer.getNumSamples());


}

//==============================================================================
bool MIDISynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MIDISynthAudioProcessor::createEditor()
{
    return new MIDISynthAudioProcessorEditor (*this);
}

//==============================================================================
void MIDISynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MIDISynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MIDISynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout MIDISynthAudioProcessor::createParams() {

    

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;


    //osc
    params.push_back(std::make_unique<juce::AudioParameterChoice> ("OSC", "Oscillator", juce::StringArray {"Sine", "Saw", "Square", "Triangle"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSCTRANS", "Transpose", -12, 12, 0, juce::AudioParameterIntAttributes{}));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSCDET", "Detune", -100, 100, 0, juce::AudioParameterIntAttributes{}));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSCPHASE", "Phase", 0, 360, 0, juce::AudioParameterIntAttributes{}));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSCGAIN", "Gain", juce::NormalisableRange<float> {-60.0, -6.0}, -18.0));


    //osc 2
    params.push_back(std::make_unique<juce::AudioParameterChoice> ("OSC2", "Oscillator", juce::StringArray{ "Sine", "Saw", "Square", "Triangle"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSCTRANS2", "Transpose", -12, 12, 0, juce::AudioParameterIntAttributes{}));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSCDET2", "Detune", -100, 100, 0, juce::AudioParameterIntAttributes{}));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSCPHASE2", "Phase", 0, 360, 0, juce::AudioParameterIntAttributes{}));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSCGAIN2", "Gain", juce::NormalisableRange<float> {-60.0, -6.0}, -18.0));

    //amp

    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> {0.0f, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> {0.0f, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> {0.0f, 1.0f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> {0.0f, 3.0f}, 0.1f));


    //filter
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERFREQ", "Frequency", juce::NormalisableRange<float> {20.0f, 20000.0f, 0.1f, 0.6}, 20000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES", "Resonance", juce::NormalisableRange<float> {0.1f, 5.0f, 0.01f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Type", juce::StringArray{ "Lowpass", "Highpass", "Bandpass" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterBool>("FILTERON", "Filter Power", false));


    return { params.begin(), params.end() };    

}
