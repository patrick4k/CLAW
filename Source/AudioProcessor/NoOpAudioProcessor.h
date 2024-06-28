#pragma once

#include "IAudioProcessor.h"
#include "../Util/Util.h"

namespace claw::audio_processor
{
    class NoOpAudioProcessor : public IAudioProcessor
    {
    public:
        void audioDeviceIOCallbackWithContext(const float* const* inputChannelData,
                                              int numInputChannels,
                                              float* const* outputChannelData,
                                              int numOutputChannels,
                                              int numSamples,
                                              const juce::AudioIODeviceCallbackContext& context) override;
    };
}

ClawMSpecializeNameof(claw::audio_processor::NoOpAudioProcessor, "NoOpAudioProcessor")
