#include <combaseapi.h>
#include <JuceHeader.h>

#include "Application/CommandLineApp.h"
#include "IO/AnalogAudioDevice.h"
#include "Util/Util.h"

using namespace claw;

int main ()
{
    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
        util::error("Failed to initialize COM library");
        return 1;
    }
    juce::MessageManager::getInstance();
    juce::ConsoleApplication app;

    try
    {
        apps::CommandLineApp claw{};
        if (const auto& result = claw.run())
        {
            util::console("Exiting application...");
            CoUninitialize();
            util::console("Exiting Program...");
            return result.unwrap();
        }
        else
        {
            util::error(result.unwrap_err());
        }
    }
    catch (const std::exception& e)
    {
        util::error(e.what());
    }
    catch (...)
    {
        util::error("Caught Unknown Exception.");
    }
    
    CoUninitialize();
    util::console("Exiting Program...");
    return 0;
}
