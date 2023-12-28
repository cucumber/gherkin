#pragma once

#include <string>
#include <sstream>
#include <iostream>

namespace cucumber::gherkin {

template <typename... Args>
std::string
log_string(Args&&... args)
{
    std::ostringstream oss;

    (oss << ... << args);

    return oss.str();
}

template <typename... Args>
void
log(Args&&... args)
{ std::cout << log_string(std::forward<Args>(args)...) << std::endl; }

template <typename... Args>
void
warn(Args&&... args)
{ log("W: ", std::forward<Args>(args)...); }

template <typename... Args>
void
error(Args&&... args)
{ log("E: ", std::forward<Args>(args)...); }

template <typename... Args>
void
die(Args&&... args)
{ throw std::runtime_error(log_string(std::forward<Args>(args)...)); }

template <typename... Args>
void
die_if(bool cond, Args&&... args)
{
    if (!cond) {
        return;
    }

    die(std::forward<Args>(args)...);
}

template <typename... Args>
void
die_unless(bool cond, Args&&... args)
{ die_if(!cond, std::forward<Args>(args)...); }

template <typename... Args>
void
sysdie(Args&&... args)
{
    auto err = errno;
    auto econd = std::system_category().default_error_condition(err);

    die(std::forward<Args>(args)..., ": ", econd.message());
}

template <typename... Args>
void
sysdie_if(bool cond, Args&&... args)
{
    if (!cond) {
        return;
    }

    sysdie(std::forward<Args>(args)...);
}

template <typename... Args>
void
sysdie_unless(bool cond, Args&&... args)
{ sysdie_if(!cond, std::forward<Args>(args)...); }

}
