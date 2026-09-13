#ifndef CUCUMBER_GHERKIN_CB_TYPES_HPP
#define CUCUMBER_GHERKIN_CB_TYPES_HPP

#include "cucumber/gherkin/ParseError.hpp"
#include "cucumber/messages/Pickle.hpp"
#include "cucumber/messages/Source.hpp"
#include <functional>
#include <nlohmann/json.hpp>

namespace cucumber::gherkin
{
    using SourceCb = std::function<void(const messages::Source&)>;
    using PickleCb = std::function<void(const messages::Pickle&)>;
    using ErrorCb = std::function<void(const ParseError&)>;

    template<typename Ast>
    struct Callbacks
    {
        using AstCb = std::function<void(const Ast&)>;

        SourceCb source;
        AstCb ast;
        PickleCb pickle;
        ErrorCb error;
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
