#include "IAudioProcessor.h"
#include "../Util/Util.h"

namespace claw::audio_processor
{
    void IAudioProcessor::audioDeviceAboutToStart(juce::AudioIODevice* device)
    {
        m_device = device;
        m_sampleRate = device->getCurrentSampleRate();
        m_bufferSize = device->getCurrentBufferSizeSamples();
        util::console(*this, std::string{} + "Audio device started: Sample Rate = " + std::to_string(m_sampleRate) + ", Buffer Size = " + std::to_string(m_bufferSize));
    }

    void IAudioProcessor::audioDeviceStopped()
    {
        util::console(*this, "Audio device stopped");
        m_device = nullptr;
    }
}
