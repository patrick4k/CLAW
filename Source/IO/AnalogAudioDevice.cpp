#include "AnalogAudioDevice.h"
#include "../Util/RuntimeException.h"

namespace claw::io
{
    void AnalogAudioDevice::start()
    {
        m_deviceManager.initialiseWithDefaultDevices(2, 2);
        m_deviceManager.addAudioCallback(&m_processor);
        if (!m_deviceManager.getCurrentAudioDevice())
        {
            throw util::RuntimeException(*this, "No default audio device found");
        }
        const auto& setup = m_deviceManager.getAudioDeviceSetup();
        util::console(*this, std::string{} + "Input Device: " + setup.inputDeviceName.toRawUTF8());
        util::console(*this, std::string{} + "Output Device: " + setup.outputDeviceName.toRawUTF8());
    }

    void AnalogAudioDevice::stop()
    {
        m_deviceManager.removeAudioCallback(&m_processor);
    }

    AnalogAudioDevice::~AnalogAudioDevice()
    {
        stop();
    }
}
