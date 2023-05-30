#pragma once

#include <functional>

#include <nlohmann/json.hpp>

#include <cucumber/messages/pickle.hpp>
#include <cucumber/messages/source.hpp>

#include <gherkin/parse_error.hpp>

namespace gherkin {

namespace cms = cucumber::messages;

using source_cb = std::function<void (const cms::source&)>;
using pickle_cb = std::function<void (const cms::pickle&)>;
using error_cb = std::function<void (const parse_error&)>;

template <typename Ast>
struct callbacks
{
    using ast_cb = std::function<void (const Ast&)>;

    gherkin::source_cb source;
    ast_cb ast;
    gherkin::pickle_cb pickle;
    error_cb error;
};

template <typename Callback, typename Msg>
void
call_cb(Callback& cb, const Msg& m)
{
    if (cb) {
        cb(m);
    }
}

}
