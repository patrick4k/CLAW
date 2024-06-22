#pragma once
#include "../Component/IComponent.h"

namespace claw::io
{
    class IAudioDevice : public components::IComponent
    {
    public:
        virtual ~IAudioDevice() = default;
    };
}
