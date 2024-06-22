#pragma once
#include "../Util/Result.h"

namespace claw::apps
{
    class IApplication
    {
    public:
        virtual ~IApplication() = default;
        using ApplicationRunResult = util::Result<int>;
        
        virtual ApplicationRunResult run() = 0;
    };
}
