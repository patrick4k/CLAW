#pragma once

#include <future>

#include "../Util/Result.h"

namespace claw::components
{
    class IComponent
    {
    public:
        using RunResult = util::Result<int>;
        virtual ~IComponent() = default;
    };
}
