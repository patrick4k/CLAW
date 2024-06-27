#pragma once
#include "IParser.h"

namespace claw::util::parser
{
    class CommandLineToken : public IToken
    {
    public:
        enum Type
        {
            eIdentifier,
            eString,
            eDouble,
            eInt
        };

        CommandLineToken(Type type, std::string str) : m_type(type), m_str(std::move(str))
        {
        }

        const Type& type() const { return m_type; }
        const std::string& string() const override { return m_str; }
        
    private:
        Type m_type;
        std::string m_str;
    };
    
    class CommandLineParser : public IParser
    {
    public:
        CommandLineParser() = default;
        
        [[nodiscard]] ParseResult parse(const std::string& stream) const override;
    };
}
