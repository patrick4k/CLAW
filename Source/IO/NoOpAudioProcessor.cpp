#include "NoOpAudioProcessor.h"
#include "../Util/Util.h"

namespace claw::io
{
    void NoOpAudioProcessor::audioDeviceAboutToStart(juce::AudioIODevice* device)
    {
        m_device = device;
        m_sampleRate = device->getCurrentSampleRate();
        m_bufferSize = device->getCurrentBufferSizeSamples();
        util::console(*this, std::string{} + "Audio device started: Sample Rate = " + std::to_string(m_sampleRate) + ", Buffer Size = " + std::to_string(m_bufferSize));
    }

    void NoOpAudioProcessor::audioDeviceStopped()
    {
        util::console(*this, "Audio device stopped");
        m_device = nullptr;
    }

    void NoOpAudioProcessor::audioDeviceIOCallbackWithContext(const float* const* inputChannelData, int numInputChannels,
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
}
