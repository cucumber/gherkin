#ifndef CUCUMBER_GHERKIN_CB_TYPES_HPP
#define CUCUMBER_GHERKIN_CB_TYPES_HPP

#include "cucumber/gherkin/parse_error.hpp"
#include "cucumber/messages/Pickle.hpp"
#include "cucumber/messages/Source.hpp"
#include <functional>
#include <nlohmann/json.hpp>

namespace cucumber::gherkin
{

    namespace cms = cucumber::messages;

    using source_cb = std::function<void(const cms::Source&)>;
    using pickle_cb = std::function<void(const cms::Pickle&)>;
    using error_cb = std::function<void(const ParseError&)>;

    template<typename Ast>
    struct Callbacks
    {
        using ast_cb = std::function<void(const Ast&)>;

        source_cb source;
        ast_cb ast;
        pickle_cb pickle;
        error_cb error;
    };

    template<typename Callback, typename Msg>
    void CallCb(Callback& callback, const Msg& message)
    {
        if (callback)
        {
            callback(message);
        }
    }

}

#endif
