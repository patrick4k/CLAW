#include "CommandLineParser.h"

#include <map>
#include <regex>

namespace claw::util::parser
{
    IParser::ParseResult CommandLineParser::parse(const std::string& stream) const
    {
        auto mut_stream = stream;
        
        const std::vector ignore{
            std::regex{ "^(\\s).*$" },
            std::regex{ "^(\\t).*$" },
            std::regex{ "^(\\n).*$" },
            std::regex{ "^(\\r).*$" }
        };

        const std::vector<std::pair<CommandLineToken::Type, std::regex>> token_regex{
            { CommandLineToken::Type::eDouble,      std::regex{R"(^(\d+\.\d+).*$)" } },
            { CommandLineToken::Type::eInt,         std::regex{ R"(^(\d+).*$)" } },
            { CommandLineToken::Type::eIdentifier,  std::regex{R"(^(\w[\w\dA-Za-z]*).*$)" } },
            { CommandLineToken::Type::eString,      std::regex{R"(^("[^"]*").*$)" } },
        };

        std::vector<TokenPtr> tokens{};
        while (!mut_stream.empty())
        {
            bool found_match{ false };
            
            // Match ignore patterns
            bool more_ignore{ true };
            while (more_ignore)
            {
                more_ignore = false;
                for (const auto& ignore_pattern : ignore)
                {
                    std::smatch match{};
                    if (std::regex_match(mut_stream, match, ignore_pattern))
                    {
                        found_match = true;
                        more_ignore = true;
                        const auto& submatch = match[1];
                        const auto& len = submatch.length();
                        mut_stream = mut_stream.substr(len);
                    }
                }
            }

            // Match tokens
            bool more_tokens{ true };
            while (more_tokens)
            {
                more_tokens = false;
                for (const auto& [type, pattern] : token_regex)
                {
                    std::smatch match{};
                    if (std::regex_match(mut_stream, match, pattern))
                    {
                        found_match = true;
                        more_tokens = true;
                        const auto& submatch = match[1]; 
                        const auto& len = submatch.length();
                        tokens.emplace_back(std::make_shared<CommandLineToken>(type,  submatch.str()));
                        mut_stream = mut_stream.substr(len);
                    }
                }
            }

            if (!found_match && !mut_stream.empty())
            {
                return ParseResult::error("Cannot find match, invalid string");
            }
        }

        return tokens;
    }
}
