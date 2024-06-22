#pragma once
#include <exception>

namespace claw::util
{
    class IException : public std::exception
    {
    public:
        IException(const char* what) : std::exception(what)
        {
        }
    
        ~IException() override = default;
    };
}
