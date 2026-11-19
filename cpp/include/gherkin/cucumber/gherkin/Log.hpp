#ifndef CUCUMBER_GHERKIN_LOG_HPP
#define CUCUMBER_GHERKIN_LOG_HPP

#include <cerrno>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <system_error>

namespace cucumber::gherkin
{

    template<typename... Args>
    std::string LogString(Args&&... args)
    {
        std::ostringstream oss;

        (oss << ... << std::forward<Args>(args)); // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

        return oss.str();
    }

    template<typename... Args>
    void Log(Args&&... args)
    {
        std::cout << LogString(std::forward<Args>(args)...) << std::endl;
    }

    template<typename... Args>
    void Warn(Args&&... args)
    {
        Log("W: ", std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Error(Args&&... args)
    {
        Log("E: ", std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Die(Args&&... args)
    {
        throw std::runtime_error(LogString(std::forward<Args>(args)...));
    }

    template<typename... Args>
    void DieIf(bool cond, Args&&... args)
    {
        if (!cond)
        {
            return;
        }

        Die(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void DieUnless(bool cond, Args&&... args)
    {
        DieIf(!cond, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Sysdie(Args&&... args)
    {
        auto err = errno;
        auto econd = std::system_category().default_error_condition(err);

        Die(std::forward<Args>(args)..., ": ", econd.message());
    }

    template<typename... Args>
    void SysdieIf(bool cond, Args&&... args)
    {
        if (!cond)
        {
            return;
        }

        Sysdie(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void SysdieUnless(bool cond, Args&&... args)
    {
        SysdieIf(!cond, std::forward<Args>(args)...);
    }

}

#endif
