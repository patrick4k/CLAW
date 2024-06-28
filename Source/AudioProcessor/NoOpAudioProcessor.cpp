#include "NoOpAudioProcessor.h"
#include "../Util/Util.h"

namespace claw::audio_processor
{
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
