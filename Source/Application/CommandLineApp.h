#pragma once

#include "IApplication.h"
#include "../Component/ComponentContainer.h"
#include "../IO/AnalogAudioDevice.h"

namespace claw::apps
{
    class CommandLineApp : public IApplication
    {
        using CLComponentContainer = components::ComponentContainer<io::AnalogAudioDevice>;
    public:
        CommandLineApp() = default;

        ApplicationRunResult run() override;
    
    private:
        CLComponentContainer m_components{};
        bool m_shouldEnd{ false };

        std::map<std::string, std::function<void(CommandLineApp& app)>> m_fnMap {
            {
                "start",
                [](CommandLineApp& app)
                {
                    app.m_components.GetComponent<io::AnalogAudioDevice>().start();
                }
            },
            {
                "stop",
                [](CommandLineApp& app)
                {
                    app.m_components.GetComponent<io::AnalogAudioDevice>().stop();
                }
            },
            {
                "exit",
                [](CommandLineApp& app)
                {
                    app.m_shouldEnd = true;
                }
            },
            {
                "debug",
                [](CommandLineApp& app)
                {
                    util::console(app, "TODO: Debug");
                }
            }
        };
    };
}
