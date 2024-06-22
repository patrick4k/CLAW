#include "CommandLineApp.h"

namespace claw::apps
{
    IApplication::ApplicationRunResult CommandLineApp::run()
    {
        while (!m_shouldEnd)
        {
            auto cmd = util::input(*this, "Enter command: ");
            if (auto fn = m_fnMap[cmd])
            {
                fn(*this);
            }
            else
            {
                util::error(*this, "Invalid command");
            }
        }

        return 0;
    }
}
