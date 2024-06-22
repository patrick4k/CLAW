#include "AnalogAudioDevice.h"

namespace claw::io
{
    void AudioProcessor::audioDeviceAboutToStart(juce::AudioIODevice* device)
    {
        m_device = device;
        m_sampleRate = device->getCurrentSampleRate();
        m_bufferSize = device->getCurrentBufferSizeSamples();
        util::console(*this, std::string{} + "Audio device started: Sample Rate = " + std::to_string(m_sampleRate) + ", Buffer Size = " + std::to_string(m_bufferSize));
    }

    void AudioProcessor::audioDeviceStopped()
    {
        util::console(*this, "Audio device stopped");
        m_device = nullptr;
    }

    void AudioProcessor::audioDeviceIOCallbackWithContext(const float* const* inputChannelData, int numInputChannels,
        float* const* outputChannelData, int numOutputChannels, int numSamples,
        const juce::AudioIODeviceCallbackContext&)
    {
        for (int channel = 0; channel < numOutputChannels; ++channel)
        {
            if (channel < numInputChannels && inputChannelData[channel] != nullptr)
            {
                // Hardcoded to [1] since bass comes in as mono in [1] and we want to fill both output channels with the same
                std::copy(inputChannelData[1], inputChannelData[1] + numSamples, outputChannelData[channel]);
            }
            else
            {
                std::fill(outputChannelData[channel], outputChannelData[channel] + numSamples, 0.0f);
            }
        }
    }

    void AnalogAudioDevice::start()
    {
        m_deviceManager.initialiseWithDefaultDevices(2, 2);
        m_deviceManager.addAudioCallback(&m_processor);
        if (!m_deviceManager.getCurrentAudioDevice())
        {
            throw util::RuntimeException(*this, "No default audio device found");
        }
        const auto& setup = m_deviceManager.getAudioDeviceSetup();
        util::console(*this, std::string{} + "Input Device: " + setup.inputDeviceName.toRawUTF8());
        util::console(*this, std::string{} + "Output Device: " + setup.outputDeviceName.toRawUTF8());
    }

    void AnalogAudioDevice::stop()
    {
        m_deviceManager.removeAudioCallback(&m_processor);
    }

    AnalogAudioDevice::~AnalogAudioDevice()
    {
        stop();
    }
}
