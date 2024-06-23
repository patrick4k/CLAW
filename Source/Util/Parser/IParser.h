#pragma once
#include <functional>
#include <optional>
#include <string>

#include "../Result.h"


namespace claw::util::parser
{

    class IToken
    {
    public:
        virtual ~IToken() = default;

        virtual const std::string& string() const = 0;
    };
    
    class IParser
    {
    public:
        using TokenPtr = std::shared_ptr<IToken>;
        using ParseResult = Result<std::vector<TokenPtr>>;
        
        virtual ~IParser() = default;

        [[nodiscard]] virtual ParseResult parse(const std::string& stream) const = 0;
        
    };
}
