#pragma once
#include <iostream>
#include <type_traits>

// Use in global namespace, specialized nameof for custom sender identifiers in console
#define ClawMSpecializeNameof(type, name) namespace claw::util { template<> inline std::string nameof<type>() { return name; } }

namespace claw::util
{
    template<typename T>
    std::string nameof()
    {
        return typeid(T).name();
    }
    namespace _private
    {
        struct _msgtype_log {};
        struct _msg_type_error {};
    }
}

ClawMSpecializeNameof(claw::util::_private::_msgtype_log, "LOG")
ClawMSpecializeNameof(claw::util::_private::_msg_type_error, "ERROR")

namespace claw::util
{
    template<typename TSender, typename T>
    std::string msg(const T& arg)
    {
        return { "[" + nameof<TSender>() + "] " + arg };
    }
    
    template<typename TSender, typename T>
    std::string msg(const TSender&, const T& arg)
    {
        return msg<TSender>(arg);
    }

    template<typename T>
    void console(const T& arg)
    {
        std::cout << msg<_private::_msgtype_log>(arg) << std::endl;
    }
    
    template<typename TSender, typename T>
    void console(const TSender&, const T& arg)
    {
        console(msg<TSender>(arg));
    }

    template<typename T>
    void error(const T& arg)
    {
        std::cout << msg<_private::_msg_type_error>(arg) << std::endl;
    }

    template<typename TSender, typename T>
    void error(const TSender&, const T& arg)
    {
        error(msg<TSender>(arg));
    }

    template<typename... TArgs>
    void waitForEnter(const TArgs&... args)
    {
        console(args...);
        std::string _;
        std::getline(std::cin, _);
    }

    template<typename... TArgs>
    std::string input(const TArgs&... args)
    {
        console(args...);
        std::cout << "[INPUT] ";
        std::string in{};
        std::getline(std::cin, in);
        return in;
    }
    
    template<typename T, typename... Ts>
    struct is_in_pack : std::false_type {};

    template<typename T, typename U, typename... Ts>
    struct is_in_pack<T, U, Ts...> : std::conditional_t<std::is_same_v<T, U>, std::true_type, is_in_pack<T, Ts...>> {};
}
