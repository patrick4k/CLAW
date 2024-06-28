#include "BitCrusher.h"

namespace claw::audio_processor
{
    void BitCrusher::audioDeviceIOCallbackWithContext(const float* const* inputChannelData, int numInputChannels,
        float* const* outputChannelData, int numOutputChannels, int numSamples,
        const juce::AudioIODeviceCallbackContext& context)
    {
        for (int channel = 0; channel < numOutputChannels; ++channel)
        {
            for (uint32_t i = 0; i < numSamples; ++i)
            {
                const auto& sample = inputChannelData[1][i]; // Hardcoded to [1] since bass comes in as mono in [1] and we want to fill both output channels with the same
                float scaledSample = (sample + 1.0f) * 0.5f * m_maxLevels;

                // Round to the nearest integer to simulate quantization
                int quantizedSample = static_cast<int>(std::round(scaledSample));
                outputChannelData[channel][i] = quantizedSample / static_cast<float>(m_maxLevels) * 2.0f - 1.0f;
            }
        }
    }
}
