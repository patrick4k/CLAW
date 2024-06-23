#pragma once
#include <iostream>
#include <type_traits>

namespace claw::util
{
    template<typename T>
    std::string nameof()
    {
        return typeid(T).name();
    }

    struct _msgtype_log {};
    template<> inline std::string nameof<_msgtype_log>() { return "LOG"; }

    struct _msg_type_error {};
    template<> inline std::string nameof<_msg_type_error>() { return "ERROR"; }

    template<typename TSender, typename T>
    std::string msg(T arg)
    {
        return { "[" + nameof<TSender>() + "] " + arg };
    }
    
    template<typename TSender, typename T>
    std::string msg(const TSender&, T arg)
    {
        return msg<TSender>(arg);
    }

    template<typename T>
    void console(const T& arg)
    {
        std::cout << msg<_msgtype_log>(arg) << std::endl;
    }
    
    template<typename TSender, typename T>
    void console(const TSender&, const T& arg)
    {
        console(msg<TSender>(arg));
    }

    template<typename T>
    void error(const T& arg)
    {
        std::cout << msg<_msg_type_error>(arg) << std::endl;
    }

    template<typename TSender, typename T>
    void error(const TSender&, T arg)
    {
        error(msg<TSender>(arg));
    }

    template<typename... TArgs>
    void waitForEnter(const TArgs&... args)
    {
        console(args...);
        std::cin.get();
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
