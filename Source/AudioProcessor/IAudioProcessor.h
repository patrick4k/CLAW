#pragma once

#include <JuceHeader.h>

#include "../Util/Util.h"

namespace claw::audio_processor
{
    class IAudioProcessor : public juce::AudioIODeviceCallback
    {
    public:
        void audioDeviceAboutToStart(juce::AudioIODevice* device) override;

        void audioDeviceStopped() override;

    private:
        juce::AudioIODevice* m_device{ nullptr };
        double m_sampleRate{ 0 };
        int m_bufferSize{ 0 };
    };
}

ClawMSpecializeNameof(claw::audio_processor::IAudioProcessor, "AudioProcessor")
