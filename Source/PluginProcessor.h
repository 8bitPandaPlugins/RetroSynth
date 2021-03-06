/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Synthesizer/SynthSource.h"
//==============================================================================
/**
*/
class RetroSynthAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    RetroSynthAudioProcessor();
    ~RetroSynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    MidiKeyboardState m_keystate;

    ADSR::Parameters* m_FilterPerameters = nullptr;
    ADSR::Parameters* m_AmpPerameters = nullptr;
    int* m_FilterMode = nullptr;


    float* m_VCF1_Cutoff = nullptr;
    float* m_VCF1_Res = nullptr;
    int* m_Filter1Type = nullptr;
    float* m_VCF2_Cutoff = nullptr;
    float* m_VCF2_Res = nullptr;
    int* m_Filter2Type = nullptr;
    double* m_FilterEnvelope = nullptr;

    float* m_OSC1_FrequencyMod = nullptr;
    float* m_OSC1_Detune = nullptr;
    int* m_Waveform1Index = nullptr;
    float* m_OSC2_FrequencyMod = nullptr;
    float* m_OSC2_Detune = nullptr;;
    int* m_Waveform2Index = nullptr;

    float* m_OSC2_Vol = nullptr;



private:
    //==============================================================================
   RetroSynthAudioSource m_synth;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RetroSynthAudioProcessor)
};
