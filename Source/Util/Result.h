#pragma once

#include <string>
#include <optional>
#include "Util.h"

namespace claw::util
{
    template<typename TOk, typename TErr = std::string>
    class Result
    {
        using This = Result<TOk, TErr>;
    public:
        Result(TOk ok) : m_ok(ok) {}
        Result(TErr err) : m_err(err) {}
        
        template<class... TArgs>
        static This success(TArgs... args)
        {
            TOk ok{ args... };
            return Result{ std::move(ok) };
        }

        template<class... TArgs>
        static This error(TArgs... args)
        {
            TErr err{ args... };
            return Result{ std::move(err) };
        }

        [[nodiscard]]
        bool is_ok() const { return m_ok.has_value(); }

        [[nodiscard]]
        bool is_err() const { return m_err.has_value(); }

        explicit operator bool() const { return is_ok(); }

        [[nodiscard]] TOk unwrap() const
        {
            if (!m_ok)
            {
                if (m_err)
                    util::error(*this, m_err.value());
                else
                    util::error(*this, "Unknown error on Result::unwrap()");
            }
            return m_ok.value();
        }

        [[nodiscard]] TErr unwrap_err() const { return m_err.value(); }

        void ok(TOk ok)
        {
            m_err.reset();
            m_ok = ok;
        }
        void err(TErr err)
        {
            m_ok.reset();
            m_err = err;
        }

    private:
        std::optional<TOk> m_ok{};
        std::optional<TErr> m_err{};
    };
}
