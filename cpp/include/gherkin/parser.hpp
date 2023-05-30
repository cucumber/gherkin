// This file is generated. Do not edit! Edit gherkin-cpp-parser.razor instead.
#include <gherkin/parser_base.hpp>
#include <gherkin/rule_type.hpp>

namespace gherkin {

enum class error_type
{
    unexpected_eof,
    unexpected_token
};

template <
    typename Builder = ast_builder,
    typename Scanner = token_scanner,
    typename Matcher = token_matcher
>
class parser : public parser_base<Builder, Scanner, Matcher>
{
public:
    using parent = parser_base<Builder, Scanner, Matcher>;
    using parent::parent;
    using parent::parse;
    using context_type = typename parent::context_type;

protected:
    void parse(context_type& context) override
    {
        start_rule(context, rule_type::gherkin_document);

        std::size_t state = 0;

        while (true) {
            auto token = context.read_token();
            state = match_token(state, token, context);

            if (token.is_eof()) {
                break;
            }
        }

        end_rule(context, rule_type::gherkin_document);

        if (context.has_errors()) {
            context.report_errors();
        }
    }

    void build(context_type& context, token& token)
    { context.builder.build(token); }

    void start_rule(context_type& context, rule_type rule_type)
    {
        handle_ast_error(
            context,
            rule_type,
            [&context](auto rtype) {
                context.builder.start_rule(rtype);
            }
        );
    }

    void end_rule(context_type& context, rule_type rule_type)
    {
        handle_ast_error(
            context,
            rule_type,
            [&context](auto rtype) {
                context.builder.end_rule(rtype);
            }
        );
    }

    template <typename Argument, typename Action>
    bool handle_external_error(
        context_type& context,
        bool default_value,
        Argument&& argument,
        Action&& action
    )
    {
        using ret_type = decltype(action(argument));

        if (context.stop_at_first_error) {
            if constexpr (std::is_same_v<ret_type, void>) {
                action(argument);
                return default_value;
            } else {
                return action(argument);
            }
        }

        try {
            if constexpr (std::is_same_v<ret_type, void>) {
                action(argument);
                return default_value;
            } else {
                return action(argument);
            }
        } catch (const std::exception& e) {
            context.add_error(e);
        }

        return default_value;
    }

    template <typename Argument, typename Action>
    void handle_ast_error(
        context_type& context,
        Argument&& argument,
        Action&& action
    )
    { handle_external_error(context, true, argument, action); }


    bool match_e_o_f(context_type& context, token& token)
    {
        return
            handle_external_error(
                context,
                false,
                token,
                [&context](auto& t) {
                    return context.matcher.match_e_o_f(t);
                }
            );
    }

    bool match_empty(context_type& context, token& token)
    {
        if (token.is_eof()) {
            return false;
        }
        
        return
            handle_external_error(
                context,
                false,
                token,
                [&context](auto& t) {
                    return context.matcher.match_empty(t);
                }
            );
    }

    bool match_comment(context_type& context, token& token)
    {
        if (token.is_eof()) {
            return false;
        }
        
        return
            handle_external_error(
                context,
                false,
                token,
                [&context](auto& t) {
                    return context.matcher.match_comment(t);
                }
            );
    }

    bool match_tag_line(context_type& context, token& token)
    {
        if (token.is_eof()) {
            return false;
        }
        
        return
            handle_external_error(
                context,
                false,
                token,
                [&context](auto& t) {
                    return context.matcher.match_tag_line(t);
                }
            );
    }

    bool match_feature_line(context_type& context, token& token)
    {
        if (token.is_eof()) {
            return false;
        }
        
        return
            handle_external_error(
                context,
                false,
                token,
                [&context](auto& t) {
                    return context.matcher.match_feature_line(t);
                }
            );
    }

    bool match_rule_line(context_type& context, token& token)
    {
        if (token.is_eof()) {
            return false;
        }
        
        return
            handle_external_error(
                context,
                false,
                token,
                [&context](auto& t) {
                    return context.matcher.match_rule_line(t);
                }
            );
    }

    bool match_background_line(context_type& context, token& token)
    {
        if (token.is_eof()) {
            return false;
        }
        
        return
            handle_external_error(
                context,
                false,
                token,
                [&context](auto& t) {
                    return context.matcher.match_background_line(t);
                }
            );
    }

    bool match_scenario_line(context_type& context, token& token)
    {
        if (token.is_eof()) {
            return false;
        }
        
        return
            handle_external_error(
                context,
                false,
                token,
                [&context](auto& t) {
                    return context.matcher.match_scenario_line(t);
                }
            );
    }

    bool match_examples_line(context_type& context, token& token)
    {
        if (token.is_eof()) {
            return false;
        }
        
        return
            handle_external_error(
                context,
                false,
                token,
                [&context](auto& t) {
                    return context.matcher.match_examples_line(t);
                }
            );
    }

    bool match_step_line(context_type& context, token& token)
    {
        if (token.is_eof()) {
            return false;
        }
        
        return
            handle_external_error(
                context,
                false,
                token,
                [&context](auto& t) {
                    return context.matcher.match_step_line(t);
                }
            );
    }

    bool match_doc_string_separator(context_type& context, token& token)
    {
        if (token.is_eof()) {
            return false;
        }
        
        return
            handle_external_error(
                context,
                false,
                token,
                [&context](auto& t) {
                    return context.matcher.match_doc_string_separator(t);
                }
            );
    }

    bool match_table_row(context_type& context, token& token)
    {
        if (token.is_eof()) {
            return false;
        }
        
        return
            handle_external_error(
                context,
                false,
                token,
                [&context](auto& t) {
                    return context.matcher.match_table_row(t);
                }
            );
    }

    bool match_language(context_type& context, token& token)
    {
        if (token.is_eof()) {
            return false;
        }
        
        return
            handle_external_error(
                context,
                false,
                token,
                [&context](auto& t) {
                    return context.matcher.match_language(t);
                }
            );
    }

    bool match_other(context_type& context, token& token)
    {
        if (token.is_eof()) {
            return false;
        }
        
        return
            handle_external_error(
                context,
                false,
                token,
                [&context](auto& t) {
                    return context.matcher.match_other(t);
                }
            );
    }


    bool lookahead_0(context_type& context, token& current_token)
    {
        current_token.detach();
        token token;
        token_queue queue;
        bool match = false;

        while (true) {
            token = context.read_token();
            token.detach();
            queue.push_back(token);

            if (match_scenario_line(context, token) || false) {
                match = true;
                break;
            }

            if (!(match_empty(context, token) || match_comment(context, token) || match_tag_line(context, token) || false)) {
                break;
            }
        }

        context.push_tokens(queue);

        return match;
    }

    bool lookahead_1(context_type& context, token& current_token)
    {
        current_token.detach();
        token token;
        token_queue queue;
        bool match = false;

        while (true) {
            token = context.read_token();
            token.detach();
            queue.push_back(token);

            if (match_examples_line(context, token) || false) {
                match = true;
                break;
            }

            if (!(match_empty(context, token) || match_comment(context, token) || match_tag_line(context, token) || false)) {
                break;
            }
        }

        context.push_tokens(queue);

        return match;
    }


    // Start
    std::size_t match_token_at_0(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            build(context, token);
            return 42;
        }
        if (match_language(context, token)) {
            start_rule(context, rule_type::feature);
            start_rule(context, rule_type::feature_header);
            build(context, token);
            return 1;
        }
        if (match_tag_line(context, token)) {
            start_rule(context, rule_type::feature);
            start_rule(context, rule_type::feature_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 2;
        }
        if (match_feature_line(context, token)) {
            start_rule(context, rule_type::feature);
            start_rule(context, rule_type::feature_header);
            build(context, token);
            return 3;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 0;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 0;
        }

        /* "State: 0 - Start" */
        std::string expected_tokens = "#EOF, #Language, #TagLine, #FeatureLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 0;
    }

    // GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0
    std::size_t match_token_at_1(token& token, context_type& context)
    {
        if (match_tag_line(context, token)) {
            start_rule(context, rule_type::tags);
            build(context, token);
            return 2;
        }
        if (match_feature_line(context, token)) {
            build(context, token);
            return 3;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 1;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 1;
        }

        /* "State: 1 - GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0" */
        std::string expected_tokens = "#TagLine, #FeatureLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 1;
    }

    // GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0
    std::size_t match_token_at_2(token& token, context_type& context)
    {
        if (match_tag_line(context, token)) {
            build(context, token);
            return 2;
        }
        if (match_feature_line(context, token)) {
            end_rule(context, rule_type::tags);
            build(context, token);
            return 3;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 2;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 2;
        }

        /* "State: 2 - GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0" */
        std::string expected_tokens = "#TagLine, #FeatureLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 2;
    }

    // GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0
    std::size_t match_token_at_3(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::feature_header);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 3;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 5;
        }
        if (match_background_line(context, token)) {
            end_rule(context, rule_type::feature_header);
            start_rule(context, rule_type::background);
            build(context, token);
            return 6;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::feature_header);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::feature_header);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::feature_header);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::feature_header);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            start_rule(context, rule_type::description);
            build(context, token);
            return 4;
        }

        /* "State: 3 - GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0" */
        std::string expected_tokens = "#EOF, #Empty, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 3;
    }

    // GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>#Other:0
    std::size_t match_token_at_4(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::feature_header);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            end_rule(context, rule_type::description);
            build(context, token);
            return 5;
        }
        if (match_background_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::feature_header);
            start_rule(context, rule_type::background);
            build(context, token);
            return 6;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::description);
                end_rule(context, rule_type::feature_header);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::feature_header);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::feature_header);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::feature_header);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            build(context, token);
            return 4;
        }

        /* "State: 4 - GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>#Other:0" */
        std::string expected_tokens = "#EOF, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 4;
    }

    // GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:2>#Comment:0
    std::size_t match_token_at_5(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::feature_header);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 5;
        }
        if (match_background_line(context, token)) {
            end_rule(context, rule_type::feature_header);
            start_rule(context, rule_type::background);
            build(context, token);
            return 6;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::feature_header);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::feature_header);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::feature_header);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::feature_header);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 5;
        }

        /* "State: 5 - GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:2>#Comment:0" */
        std::string expected_tokens = "#EOF, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 5;
    }

    // GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0
    std::size_t match_token_at_6(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 6;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 8;
        }
        if (match_step_line(context, token)) {
            start_rule(context, rule_type::step);
            build(context, token);
            return 9;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::background);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            start_rule(context, rule_type::description);
            build(context, token);
            return 7;
        }

        /* "State: 6 - GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0" */
        std::string expected_tokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 6;
    }

    // GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>#Other:0
    std::size_t match_token_at_7(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            end_rule(context, rule_type::description);
            build(context, token);
            return 8;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::description);
            start_rule(context, rule_type::step);
            build(context, token);
            return 9;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::description);
                end_rule(context, rule_type::background);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            build(context, token);
            return 7;
        }

        /* "State: 7 - GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>#Other:0" */
        std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 7;
    }

    // GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:2>#Comment:0
    std::size_t match_token_at_8(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 8;
        }
        if (match_step_line(context, token)) {
            start_rule(context, rule_type::step);
            build(context, token);
            return 9;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::background);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 8;
        }

        /* "State: 8 - GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:2>#Comment:0" */
        std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 8;
    }

    // GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0
    std::size_t match_token_at_9(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_table_row(context, token)) {
            start_rule(context, rule_type::data_table);
            build(context, token);
            return 10;
        }
        if (match_doc_string_separator(context, token)) {
            start_rule(context, rule_type::doc_string);
            build(context, token);
            return 49;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::step);
            build(context, token);
            return 9;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::step);
                end_rule(context, rule_type::background);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 9;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 9;
        }

        /* "State: 9 - GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0" */
        std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 9;
    }

    // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
    std::size_t match_token_at_10(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_table_row(context, token)) {
            build(context, token);
            return 10;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::step);
            build(context, token);
            return 9;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::data_table);
                end_rule(context, rule_type::step);
                end_rule(context, rule_type::background);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 10;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 10;
        }

        /* "State: 10 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0" */
        std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 10;
    }

    // GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0
    std::size_t match_token_at_11(token& token, context_type& context)
    {
        if (match_tag_line(context, token)) {
            build(context, token);
            return 11;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::tags);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 11;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 11;
        }

        /* "State: 11 - GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0" */
        std::string expected_tokens = "#TagLine, #ScenarioLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 11;
    }

    // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
    std::size_t match_token_at_12(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 12;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 14;
        }
        if (match_step_line(context, token)) {
            start_rule(context, rule_type::step);
            build(context, token);
            return 15;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 17;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 18;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            start_rule(context, rule_type::description);
            build(context, token);
            return 13;
        }

        /* "State: 12 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0" */
        std::string expected_tokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 12;
    }

    // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0
    std::size_t match_token_at_13(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            end_rule(context, rule_type::description);
            build(context, token);
            return 14;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::description);
            start_rule(context, rule_type::step);
            build(context, token);
            return 15;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::description);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 17;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::description);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::description);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 18;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            build(context, token);
            return 13;
        }

        /* "State: 13 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0" */
        std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 13;
    }

    // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0
    std::size_t match_token_at_14(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 14;
        }
        if (match_step_line(context, token)) {
            start_rule(context, rule_type::step);
            build(context, token);
            return 15;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 17;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 18;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 14;
        }

        /* "State: 14 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0" */
        std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 14;
    }

    // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
    std::size_t match_token_at_15(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_table_row(context, token)) {
            start_rule(context, rule_type::data_table);
            build(context, token);
            return 16;
        }
        if (match_doc_string_separator(context, token)) {
            start_rule(context, rule_type::doc_string);
            build(context, token);
            return 47;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::step);
            build(context, token);
            return 15;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::step);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 17;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::step);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 18;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 15;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 15;
        }

        /* "State: 15 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0" */
        std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 15;
    }

    // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
    std::size_t match_token_at_16(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_table_row(context, token)) {
            build(context, token);
            return 16;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::step);
            build(context, token);
            return 15;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::data_table);
                end_rule(context, rule_type::step);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 17;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::data_table);
                end_rule(context, rule_type::step);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 18;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 16;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 16;
        }

        /* "State: 16 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0" */
        std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 16;
    }

    // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
    std::size_t match_token_at_17(token& token, context_type& context)
    {
        if (match_tag_line(context, token)) {
            build(context, token);
            return 17;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::tags);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 18;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 17;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 17;
        }

        /* "State: 17 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0" */
        std::string expected_tokens = "#TagLine, #ExamplesLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 17;
    }

    // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
    std::size_t match_token_at_18(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 18;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 20;
        }
        if (match_table_row(context, token)) {
            start_rule(context, rule_type::examples_table);
            build(context, token);
            return 21;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 17;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 18;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            start_rule(context, rule_type::description);
            build(context, token);
            return 19;
        }

        /* "State: 18 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0" */
        std::string expected_tokens = "#EOF, #Empty, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 18;
    }

    // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0
    std::size_t match_token_at_19(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            end_rule(context, rule_type::description);
            build(context, token);
            return 20;
        }
        if (match_table_row(context, token)) {
            end_rule(context, rule_type::description);
            start_rule(context, rule_type::examples_table);
            build(context, token);
            return 21;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::description);
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 17;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::description);
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 18;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            build(context, token);
            return 19;
        }

        /* "State: 19 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0" */
        std::string expected_tokens = "#EOF, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 19;
    }

    // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0
    std::size_t match_token_at_20(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 20;
        }
        if (match_table_row(context, token)) {
            start_rule(context, rule_type::examples_table);
            build(context, token);
            return 21;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 17;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 18;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 20;
        }

        /* "State: 20 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0" */
        std::string expected_tokens = "#EOF, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 20;
    }

    // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
    std::size_t match_token_at_21(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::examples_table);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_table_row(context, token)) {
            build(context, token);
            return 21;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::examples_table);
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 17;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::examples_table);
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::examples_table);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::examples_table);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 18;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::examples_table);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::examples_table);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 21;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 21;
        }

        /* "State: 21 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0" */
        std::string expected_tokens = "#EOF, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 21;
    }

    // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0
    std::size_t match_token_at_22(token& token, context_type& context)
    {
        if (match_tag_line(context, token)) {
            build(context, token);
            return 22;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::tags);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 22;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 22;
        }

        /* "State: 22 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0" */
        std::string expected_tokens = "#TagLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 22;
    }

    // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>#RuleLine:0
    std::size_t match_token_at_23(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::rule_header);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 25;
        }
        if (match_background_line(context, token)) {
            end_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::background);
            build(context, token);
            return 26;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::rule_header);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::rule_header);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::rule_header);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            start_rule(context, rule_type::description);
            build(context, token);
            return 24;
        }

        /* "State: 23 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>#RuleLine:0" */
        std::string expected_tokens = "#EOF, #Empty, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 23;
    }

    // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:1>Description:0>#Other:0
    std::size_t match_token_at_24(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::rule_header);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            end_rule(context, rule_type::description);
            build(context, token);
            return 25;
        }
        if (match_background_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::background);
            build(context, token);
            return 26;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::description);
                end_rule(context, rule_type::rule_header);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::rule_header);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::rule_header);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            build(context, token);
            return 24;
        }

        /* "State: 24 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:1>Description:0>#Other:0" */
        std::string expected_tokens = "#EOF, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 24;
    }

    // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:2>#Comment:0
    std::size_t match_token_at_25(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::rule_header);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 25;
        }
        if (match_background_line(context, token)) {
            end_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::background);
            build(context, token);
            return 26;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::rule_header);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::rule_header);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::rule_header);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 25;
        }

        /* "State: 25 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:2>#Comment:0" */
        std::string expected_tokens = "#EOF, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 25;
    }

    // GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0
    std::size_t match_token_at_26(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 26;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 28;
        }
        if (match_step_line(context, token)) {
            start_rule(context, rule_type::step);
            build(context, token);
            return 29;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::background);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            start_rule(context, rule_type::description);
            build(context, token);
            return 27;
        }

        /* "State: 26 - GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0" */
        std::string expected_tokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 26;
    }

    // GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>#Other:0
    std::size_t match_token_at_27(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            end_rule(context, rule_type::description);
            build(context, token);
            return 28;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::description);
            start_rule(context, rule_type::step);
            build(context, token);
            return 29;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::description);
                end_rule(context, rule_type::background);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            build(context, token);
            return 27;
        }

        /* "State: 27 - GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>#Other:0" */
        std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 27;
    }

    // GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:2>#Comment:0
    std::size_t match_token_at_28(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 28;
        }
        if (match_step_line(context, token)) {
            start_rule(context, rule_type::step);
            build(context, token);
            return 29;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::background);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 28;
        }

        /* "State: 28 - GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:2>#Comment:0" */
        std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 28;
    }

    // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0
    std::size_t match_token_at_29(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_table_row(context, token)) {
            start_rule(context, rule_type::data_table);
            build(context, token);
            return 30;
        }
        if (match_doc_string_separator(context, token)) {
            start_rule(context, rule_type::doc_string);
            build(context, token);
            return 45;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::step);
            build(context, token);
            return 29;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::step);
                end_rule(context, rule_type::background);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 29;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 29;
        }

        /* "State: 29 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0" */
        std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 29;
    }

    // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
    std::size_t match_token_at_30(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_table_row(context, token)) {
            build(context, token);
            return 30;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::step);
            build(context, token);
            return 29;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::data_table);
                end_rule(context, rule_type::step);
                end_rule(context, rule_type::background);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 30;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 30;
        }

        /* "State: 30 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0" */
        std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 30;
    }

    // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0
    std::size_t match_token_at_31(token& token, context_type& context)
    {
        if (match_tag_line(context, token)) {
            build(context, token);
            return 31;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::tags);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 31;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 31;
        }

        /* "State: 31 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0" */
        std::string expected_tokens = "#TagLine, #ScenarioLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 31;
    }

    // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
    std::size_t match_token_at_32(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 32;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 34;
        }
        if (match_step_line(context, token)) {
            start_rule(context, rule_type::step);
            build(context, token);
            return 35;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 37;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 38;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            start_rule(context, rule_type::description);
            build(context, token);
            return 33;
        }

        /* "State: 32 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0" */
        std::string expected_tokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 32;
    }

    // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0
    std::size_t match_token_at_33(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            end_rule(context, rule_type::description);
            build(context, token);
            return 34;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::description);
            start_rule(context, rule_type::step);
            build(context, token);
            return 35;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::description);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 37;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::description);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::description);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 38;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            build(context, token);
            return 33;
        }

        /* "State: 33 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0" */
        std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 33;
    }

    // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0
    std::size_t match_token_at_34(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 34;
        }
        if (match_step_line(context, token)) {
            start_rule(context, rule_type::step);
            build(context, token);
            return 35;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 37;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 38;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 34;
        }

        /* "State: 34 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0" */
        std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 34;
    }

    // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
    std::size_t match_token_at_35(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_table_row(context, token)) {
            start_rule(context, rule_type::data_table);
            build(context, token);
            return 36;
        }
        if (match_doc_string_separator(context, token)) {
            start_rule(context, rule_type::doc_string);
            build(context, token);
            return 43;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::step);
            build(context, token);
            return 35;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::step);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 37;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::step);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 38;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 35;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 35;
        }

        /* "State: 35 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0" */
        std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 35;
    }

    // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
    std::size_t match_token_at_36(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_table_row(context, token)) {
            build(context, token);
            return 36;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::step);
            build(context, token);
            return 35;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::data_table);
                end_rule(context, rule_type::step);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 37;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::data_table);
                end_rule(context, rule_type::step);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 38;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::data_table);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 36;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 36;
        }

        /* "State: 36 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0" */
        std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 36;
    }

    // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
    std::size_t match_token_at_37(token& token, context_type& context)
    {
        if (match_tag_line(context, token)) {
            build(context, token);
            return 37;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::tags);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 38;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 37;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 37;
        }

        /* "State: 37 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0" */
        std::string expected_tokens = "#TagLine, #ExamplesLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 37;
    }

    // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
    std::size_t match_token_at_38(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 38;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 40;
        }
        if (match_table_row(context, token)) {
            start_rule(context, rule_type::examples_table);
            build(context, token);
            return 41;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 37;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 38;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            start_rule(context, rule_type::description);
            build(context, token);
            return 39;
        }

        /* "State: 38 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0" */
        std::string expected_tokens = "#EOF, #Empty, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 38;
    }

    // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0
    std::size_t match_token_at_39(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            end_rule(context, rule_type::description);
            build(context, token);
            return 40;
        }
        if (match_table_row(context, token)) {
            end_rule(context, rule_type::description);
            start_rule(context, rule_type::examples_table);
            build(context, token);
            return 41;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::description);
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 37;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::description);
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 38;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::description);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_other(context, token)) {
            build(context, token);
            return 39;
        }

        /* "State: 39 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0" */
        std::string expected_tokens = "#EOF, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 39;
    }

    // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0
    std::size_t match_token_at_40(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 40;
        }
        if (match_table_row(context, token)) {
            start_rule(context, rule_type::examples_table);
            build(context, token);
            return 41;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 37;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 38;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 40;
        }

        /* "State: 40 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0" */
        std::string expected_tokens = "#EOF, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 40;
    }

    // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
    std::size_t match_token_at_41(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::examples_table);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_table_row(context, token)) {
            build(context, token);
            return 41;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::examples_table);
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 37;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::examples_table);
                end_rule(context, rule_type::examples);
                end_rule(context, rule_type::examples_definition);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::examples_table);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::examples_table);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 38;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::examples_table);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::examples_table);
            end_rule(context, rule_type::examples);
            end_rule(context, rule_type::examples_definition);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 41;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 41;
        }

        /* "State: 41 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0" */
        std::string expected_tokens = "#EOF, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 41;
    }

    // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
    std::size_t match_token_at_43(token& token, context_type& context)
    {
        if (match_doc_string_separator(context, token)) {
            build(context, token);
            return 44;
        }
        if (match_other(context, token)) {
            build(context, token);
            return 43;
        }

        /* "State: 43 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0" */
        std::string expected_tokens = "#DocStringSeparator, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 43;
    }

    // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
    std::size_t match_token_at_44(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::step);
            build(context, token);
            return 35;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::doc_string);
                end_rule(context, rule_type::step);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 37;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::doc_string);
                end_rule(context, rule_type::step);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 38;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 44;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 44;
        }

        /* "State: 44 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0" */
        std::string expected_tokens = "#EOF, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 44;
    }

    // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
    std::size_t match_token_at_45(token& token, context_type& context)
    {
        if (match_doc_string_separator(context, token)) {
            build(context, token);
            return 46;
        }
        if (match_other(context, token)) {
            build(context, token);
            return 45;
        }

        /* "State: 45 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0" */
        std::string expected_tokens = "#DocStringSeparator, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 45;
    }

    // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
    std::size_t match_token_at_46(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::step);
            build(context, token);
            return 29;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::doc_string);
                end_rule(context, rule_type::step);
                end_rule(context, rule_type::background);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 31;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 32;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 46;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 46;
        }

        /* "State: 46 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0" */
        std::string expected_tokens = "#EOF, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 46;
    }

    // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
    std::size_t match_token_at_47(token& token, context_type& context)
    {
        if (match_doc_string_separator(context, token)) {
            build(context, token);
            return 48;
        }
        if (match_other(context, token)) {
            build(context, token);
            return 47;
        }

        /* "State: 47 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0" */
        std::string expected_tokens = "#DocStringSeparator, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 47;
    }

    // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
    std::size_t match_token_at_48(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::step);
            build(context, token);
            return 15;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_1(context, token)) {
                end_rule(context, rule_type::doc_string);
                end_rule(context, rule_type::step);
                start_rule(context, rule_type::examples_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 17;
            }
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::doc_string);
                end_rule(context, rule_type::step);
                end_rule(context, rule_type::scenario);
                end_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_examples_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::examples_definition);
            start_rule(context, rule_type::examples);
            build(context, token);
            return 18;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::scenario);
            end_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 48;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 48;
        }

        /* "State: 48 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0" */
        std::string expected_tokens = "#EOF, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 48;
    }

    // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
    std::size_t match_token_at_49(token& token, context_type& context)
    {
        if (match_doc_string_separator(context, token)) {
            build(context, token);
            return 50;
        }
        if (match_other(context, token)) {
            build(context, token);
            return 49;
        }

        /* "State: 49 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0" */
        std::string expected_tokens = "#DocStringSeparator, #Other";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 49;
    }

    // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
    std::size_t match_token_at_50(token& token, context_type& context)
    {
        if (match_e_o_f(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            end_rule(context, rule_type::feature);
            build(context, token);
            return 42;
        }
        if (match_step_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            start_rule(context, rule_type::step);
            build(context, token);
            return 9;
        }
        if (match_tag_line(context, token)) {
            if (lookahead_0(context, token)) {
                end_rule(context, rule_type::doc_string);
                end_rule(context, rule_type::step);
                end_rule(context, rule_type::background);
                start_rule(context, rule_type::scenario_definition);
                start_rule(context, rule_type::tags);
                build(context, token);
                return 11;
            }
        }
        if (match_tag_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            start_rule(context, rule_type::tags);
            build(context, token);
            return 22;
        }
        if (match_scenario_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::scenario_definition);
            start_rule(context, rule_type::scenario);
            build(context, token);
            return 12;
        }
        if (match_rule_line(context, token)) {
            end_rule(context, rule_type::doc_string);
            end_rule(context, rule_type::step);
            end_rule(context, rule_type::background);
            start_rule(context, rule_type::rule);
            start_rule(context, rule_type::rule_header);
            build(context, token);
            return 23;
        }
        if (match_comment(context, token)) {
            build(context, token);
            return 50;
        }
        if (match_empty(context, token)) {
            build(context, token);
            return 50;
        }

        /* "State: 50 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0" */
        std::string expected_tokens = "#EOF, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

        auto error =
            (
                token.is_eof()
                ? "unexpected eof: "
                : "unexpected token: "
            )
            + expected_tokens
            ;

        if (context.stop_at_first_error) {
            //throw parser_error(error + );
        }

        context.add_error(expected_tokens);

        return 50;
    }

    std::size_t match_token(std::size_t state, token& token, context_type& context)
    {
        switch (state) {
        case 0:
            return match_token_at_0(token, context);
        case 1:
            return match_token_at_1(token, context);
        case 2:
            return match_token_at_2(token, context);
        case 3:
            return match_token_at_3(token, context);
        case 4:
            return match_token_at_4(token, context);
        case 5:
            return match_token_at_5(token, context);
        case 6:
            return match_token_at_6(token, context);
        case 7:
            return match_token_at_7(token, context);
        case 8:
            return match_token_at_8(token, context);
        case 9:
            return match_token_at_9(token, context);
        case 10:
            return match_token_at_10(token, context);
        case 11:
            return match_token_at_11(token, context);
        case 12:
            return match_token_at_12(token, context);
        case 13:
            return match_token_at_13(token, context);
        case 14:
            return match_token_at_14(token, context);
        case 15:
            return match_token_at_15(token, context);
        case 16:
            return match_token_at_16(token, context);
        case 17:
            return match_token_at_17(token, context);
        case 18:
            return match_token_at_18(token, context);
        case 19:
            return match_token_at_19(token, context);
        case 20:
            return match_token_at_20(token, context);
        case 21:
            return match_token_at_21(token, context);
        case 22:
            return match_token_at_22(token, context);
        case 23:
            return match_token_at_23(token, context);
        case 24:
            return match_token_at_24(token, context);
        case 25:
            return match_token_at_25(token, context);
        case 26:
            return match_token_at_26(token, context);
        case 27:
            return match_token_at_27(token, context);
        case 28:
            return match_token_at_28(token, context);
        case 29:
            return match_token_at_29(token, context);
        case 30:
            return match_token_at_30(token, context);
        case 31:
            return match_token_at_31(token, context);
        case 32:
            return match_token_at_32(token, context);
        case 33:
            return match_token_at_33(token, context);
        case 34:
            return match_token_at_34(token, context);
        case 35:
            return match_token_at_35(token, context);
        case 36:
            return match_token_at_36(token, context);
        case 37:
            return match_token_at_37(token, context);
        case 38:
            return match_token_at_38(token, context);
        case 39:
            return match_token_at_39(token, context);
        case 40:
            return match_token_at_40(token, context);
        case 41:
            return match_token_at_41(token, context);
        case 43:
            return match_token_at_43(token, context);
        case 44:
            return match_token_at_44(token, context);
        case 45:
            return match_token_at_45(token, context);
        case 46:
            return match_token_at_46(token, context);
        case 47:
            return match_token_at_47(token, context);
        case 48:
            return match_token_at_48(token, context);
        case 49:
            return match_token_at_49(token, context);
        case 50:
            return match_token_at_50(token, context);
        default:
            context.add_error("invalid operation: " + std::to_string(state));
            return -1;
        }
    }
};

}
