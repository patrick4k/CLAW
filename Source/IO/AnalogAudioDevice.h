#pragma once

#include "IAudioDevice.h"
#include <JuceHeader.h>

#include "../AudioProcessor/NoOpAudioProcessor.h"
#include "../AudioProcessor/BitCrusher.h"

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
        audio_processor::BitCrusher m_processor{};
        juce::AudioDeviceManager m_deviceManager{};
    };
}

ClawMSpecializeNameof(claw::io::AnalogAudioDevice, "AnalogAudioDevice")
