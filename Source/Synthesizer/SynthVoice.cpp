/*
  ==============================================================================

    SynthVoice.cpp
    Created: 15 May 2020 2:46:06pm
    Author:  alexe

  ==============================================================================
*/

#include "SynthVoice.h"
#include "SynthSound.h"



RetroSynthVoice::RetroSynthVoice(Wavetable<float>* wavetable, double sampleRate): m_PhasorA(sampleRate), m_FilterA( new LowPass<float>(800, 0.2, 44100, 0.3)), m_FilterB( new LowPass<float>(800, 0.2, 44100, 0.3))
{
    m_WavetableA = wavetable;
    m_WavetableB = wavetable;
}

bool RetroSynthVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<RetroSynthSound*>(sound) != nullptr;
}

void RetroSynthVoice::startNote(int MidiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz(MidiNoteNumber);
    if (DetuneA > 0) {
        m_PhasorA.setFrequency(cyclesPerSecond + DetuneA);
    }
    m_PhasorA.setFrequency(cyclesPerSecond);
    DBG(m_PhasorA.getFreq());
    m_Envelope.noteOn();
}

void RetroSynthVoice::stopNote(float Veclocity, bool AllowTailOff)
{
    m_Envelope.noteOff();

}

void RetroSynthVoice::setCurrentPlaybackSampleRate(double samplerate)
{
    m_PhasorA.setSampleRate(samplerate);
    m_FilterA->resetsamplerate(samplerate);
    m_FilterB->resetsamplerate(samplerate);
}

void RetroSynthVoice::pitchWheelMoved(int newValue)
{
}

void RetroSynthVoice::controllerMoved(int controller, int newvalue)
{
}

void RetroSynthVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    
    float* left = outputBuffer.getWritePointer(0);
    float* right = outputBuffer.getWritePointer(1);
    for (int i = 0; i < numSamples; i++)
    {
        float sample = m_WavetableA->getSample(m_PhasorA.getPhase() * m_WavetableA->getSize())   ;
        sample = m_FilterA->process_samples(sample);
        sample = m_FilterB->process_samples(sample);
        m_PhasorA.tick();
        left[i] += sample;
        right[i] += sample;
    }
    m_Envelope.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
    if (!m_Envelope.isActive()) {
        clearCurrentNote();
    }

}
