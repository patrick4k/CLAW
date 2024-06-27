#pragma once

#include "IAudioDevice.h"
#include <JuceHeader.h>

#include "NoOpAudioProcessor.h"

namespace claw::io
{
    class AnalogAudioDevice : public IAudioDevice
    {
    public:
        AnalogAudioDevice() = default;

        void start();
        void stop();

        ~AnalogAudioDevice() override;

    private:
        NoOpAudioProcessor m_processor{};
        juce::AudioDeviceManager m_deviceManager{};
    };
}

ClawMSpecializeNameof(claw::io::AnalogAudioDevice, "AnalogAudioDevice")
