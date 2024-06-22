#pragma once
#include <string>

#include "IException.h"

namespace claw::util
{
    template<class TSender>
    class RuntimeException : public IException
    {
    public:
        RuntimeException() : IException("Unknown Exception")
        {
        }
    
        RuntimeException(const std::string& what) : IException(what.c_str())
        {
        }
    
        RuntimeException(const TSender&, const std::string& what) :
        IException(
            (std::string{} + "Runtime Exception from " + nameof<TSender>() + ": " + what).data()
            )
        {
        }

        ~RuntimeException() override = default;
    };    
}
