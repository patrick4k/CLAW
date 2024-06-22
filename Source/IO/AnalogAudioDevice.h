#pragma once

#include "../Util/Util.h"
#include "IAudioDevice.h"
#include "../Util/RuntimeException.h"
#include <JuceHeader.h>

namespace claw::io
{
    class AudioProcessor : public juce::AudioIODeviceCallback
    {
    public:
        void audioDeviceAboutToStart(juce::AudioIODevice* device) override;

        void audioDeviceStopped() override;

        void audioDeviceIOCallbackWithContext(const float* const* inputChannelData,
                                              int numInputChannels,
                                              float* const* outputChannelData,
                                              int numOutputChannels,
                                              int numSamples,
                                              const juce::AudioIODeviceCallbackContext& context) override;

    private:
        juce::AudioIODevice* m_device{ nullptr };
        double m_sampleRate{ 0 };
        int m_bufferSize{ 0 };
    };

    class AnalogAudioDevice : public IAudioDevice
    {
    public:
        AnalogAudioDevice() = default;

        void start();
        void stop();

        ~AnalogAudioDevice() override;

    private:
        AudioProcessor m_processor{};
        juce::AudioDeviceManager m_deviceManager{};
    };
}
