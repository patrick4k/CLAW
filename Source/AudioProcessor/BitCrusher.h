#pragma once
#include "IAudioProcessor.h"

namespace claw::audio_processor
{
    class BitCrusher : public IAudioProcessor
    {
    public:
        
        void audioDeviceIOCallbackWithContext(const float* const* inputChannelData,
                                              int numInputChannels,
                                              float* const* outputChannelData,
                                              int numOutputChannels,
                                              int numSamples,
                                              const juce::AudioIODeviceCallbackContext& context) override;

    private:
        uint32_t m_bitDepth{ 8 };
        int m_maxLevels{ (1 << m_bitDepth) - 1 };
    };
}
