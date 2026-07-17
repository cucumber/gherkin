#ifndef CUCUMBER_GHERKIN_PARSER_HPP
#define CUCUMBER_GHERKIN_PARSER_HPP

#include "cucumber/gherkin/ast_builder.hpp"
#include "cucumber/gherkin/exceptions.hpp"
#include "cucumber/gherkin/parser_base.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/token_matcher.hpp"
#include "cucumber/gherkin/token_scanner.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>

// This File is generated. Do not edit! Edit gherkin-cpp-Parser.razor instead.
// NOLINTBEGIN

namespace cucumber::gherkin
{

    template<typename Builder = AstBuilder, typename Scanner = TokenScanner, typename Matcher = TokenMatcher>
    class Parser : public ParserBase<Builder, Scanner, Matcher>
    {
    public:
        using parent = ParserBase<Builder, Scanner, Matcher>;
        using parent::parent;
        using parent::parse;
        using context_type = typename parent::context_type;

    protected:
        void parse(context_type& context) override
        {
            start_rule(context, RuleType::gherkinDocument);

            std::size_t state = 0;

            while (true)
            {
                auto token = context.read_token();
                state = match_token(state, token, context);

                if (token.is_eof())
                {
                    break;
                }
            }

            end_rule(context, RuleType::gherkinDocument);

            if (context.has_errors())
            {
                throw CompositeParserError(context.error_pointers);
            }
        }

        void build(context_type& context, Token& token)
        {
            context.builder.build(token);
        }

        void start_rule(context_type& context, RuleType ruleType)
        {
            handle_ast_error(context, ruleType,
                [&context](auto rtype)
                {
                    context.builder.start_rule(rtype);
                });
        }

        void end_rule(context_type& context, RuleType ruleType)
        {
            handle_ast_error(context, ruleType,
                [&context](auto rtype)
                {
                    context.builder.end_rule(rtype);
                });
        }

        template<typename Argument, typename Action>
        bool handle_external_error(context_type& context, bool default_value, Argument&& argument, Action&& action)
        {
            using ret_type = decltype(action(argument));

            try
            {
                if constexpr (std::is_same_v<ret_type, void>)
                {
                    action(argument);
                    return default_value;
                }
                else
                {
                    return action(argument);
                }
            }
            catch (const CompositeParserError& e)
            {
                for (const auto& error_pointer : e.errors())
                {
                    context.add_error(error_pointer);
                }
            }
            catch (const ParserError& e)
            {
                auto error_pointer = new_parser_error<ParserError>(e);
                context.add_error(error_pointer);
            }

            return default_value;
        }

        template<typename Argument, typename Action>
        void handle_ast_error(context_type& context, Argument&& argument, Action&& action)
        {
            handle_external_error(context, true, argument, action);
        }

        bool match_e_o_f(context_type& context, Token& token)
        {
            return handle_external_error(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.match_e_o_f(tok);
                });
        }

        bool match_empty(context_type& context, Token& token)
        {
            if (token.is_eof())
            {
                return false;
            }

            return handle_external_error(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.match_empty(tok);
                });
        }

        bool match_comment(context_type& context, Token& token)
        {
            if (token.is_eof())
            {
                return false;
            }

            return handle_external_error(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.match_comment(tok);
                });
        }

        bool match_tag_line(context_type& context, Token& token)
        {
            if (token.is_eof())
            {
                return false;
            }

            return handle_external_error(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.match_tag_line(tok);
                });
        }

        bool match_feature_line(context_type& context, Token& token)
        {
            if (token.is_eof())
            {
                return false;
            }

            return handle_external_error(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.match_feature_line(tok);
                });
        }

        bool match_rule_line(context_type& context, Token& token)
        {
            if (token.is_eof())
            {
                return false;
            }

            return handle_external_error(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.match_rule_line(tok);
                });
        }

        bool match_background_line(context_type& context, Token& token)
        {
            if (token.is_eof())
            {
                return false;
            }

            return handle_external_error(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.match_background_line(tok);
                });
        }

        bool match_scenario_line(context_type& context, Token& token)
        {
            if (token.is_eof())
            {
                return false;
            }

            return handle_external_error(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.match_scenario_line(tok);
                });
        }

        bool match_examples_line(context_type& context, Token& token)
        {
            if (token.is_eof())
            {
                return false;
            }

            return handle_external_error(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.match_examples_line(tok);
                });
        }

        bool match_step_line(context_type& context, Token& token)
        {
            if (token.is_eof())
            {
                return false;
            }

            return handle_external_error(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.match_step_line(tok);
                });
        }

        bool match_doc_string_separator(context_type& context, Token& token)
        {
            if (token.is_eof())
            {
                return false;
            }

            return handle_external_error(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.match_doc_string_separator(tok);
                });
        }

        bool match_table_row(context_type& context, Token& token)
        {
            if (token.is_eof())
            {
                return false;
            }

            return handle_external_error(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.match_table_row(tok);
                });
        }

        bool match_language(context_type& context, Token& token)
        {
            if (token.is_eof())
            {
                return false;
            }

            return handle_external_error(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.match_language(tok);
                });
        }

        bool match_other(context_type& context, Token& token)
        {
            if (token.is_eof())
            {
                return false;
            }

            return handle_external_error(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.match_other(tok);
                });
        }

        bool lookahead_0(context_type& context, Token& current_token)
        {
            Token token;
            token_queue queue;
            bool match = false;

            while (true)
            {
                token = context.read_token();
                queue.push_back(token);

                if (match_scenario_line(context, token) || false)
                {
                    match = true;
                    break;
                }

                if (!(match_empty(context, token) || match_comment(context, token) || match_tag_line(context, token) || false))
                {
                    break;
                }
            }

            context.push_tokens(queue);

            return match;
        }

        bool lookahead_1(context_type& context, Token& current_token)
        {
            Token token;
            token_queue queue;
            bool match = false;

            while (true)
            {
                token = context.read_token();
                queue.push_back(token);

                if (match_examples_line(context, token) || false)
                {
                    match = true;
                    break;
                }

                if (!(match_empty(context, token) || match_comment(context, token) || match_tag_line(context, token) || false))
                {
                    break;
                }
            }

            context.push_tokens(queue);

            return match;
        }

        // Start
        std::size_t match_token_at_0(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                build(context, token);
                return 42;
            }
            if (match_language(context, token))
            {
                start_rule(context, RuleType::feature);
                start_rule(context, RuleType::featureHeader);
                build(context, token);
                return 1;
            }
            if (match_tag_line(context, token))
            {
                start_rule(context, RuleType::feature);
                start_rule(context, RuleType::featureHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 2;
            }
            if (match_feature_line(context, token))
            {
                start_rule(context, RuleType::feature);
                start_rule(context, RuleType::featureHeader);
                build(context, token);
                return 3;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 0;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 0;
            }

            std::string state_comment = "State: 0 - Start";
            std::string expected_tokens = "#EOF, #Language, #TagLine, #FeatureLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 0;
        }

        // GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0
        std::size_t match_token_at_1(Token& token, context_type& context)
        {
            if (match_tag_line(context, token))
            {
                start_rule(context, RuleType::tags);
                build(context, token);
                return 2;
            }
            if (match_feature_line(context, token))
            {
                build(context, token);
                return 3;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 1;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 1;
            }

            std::string state_comment = "State: 1 - GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0";
            std::string expected_tokens = "#TagLine, #FeatureLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 1;
        }

        // GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0
        std::size_t match_token_at_2(Token& token, context_type& context)
        {
            if (match_tag_line(context, token))
            {
                build(context, token);
                return 2;
            }
            if (match_feature_line(context, token))
            {
                end_rule(context, RuleType::tags);
                build(context, token);
                return 3;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 2;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 2;
            }

            std::string state_comment = "State: 2 - GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0";
            std::string expected_tokens = "#TagLine, #FeatureLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 2;
        }

        // GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0
        std::size_t match_token_at_3(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::featureHeader);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 3;
            }
            if (match_comment(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 4;
            }
            if (match_background_line(context, token))
            {
                end_rule(context, RuleType::featureHeader);
                start_rule(context, RuleType::background);
                build(context, token);
                return 5;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::featureHeader);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::featureHeader);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::featureHeader);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::featureHeader);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 4;
            }

            std::string state_comment = "State: 3 - GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 3;
        }

        // GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t match_token_at_4(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::featureHeader);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 4;
            }
            if (match_background_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::featureHeader);
                start_rule(context, RuleType::background);
                build(context, token);
                return 5;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::description);
                    end_rule(context, RuleType::featureHeader);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::featureHeader);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::featureHeader);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::featureHeader);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 4;
            }

            std::string state_comment = "State: 4 - GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 4;
        }

        // GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0
        std::size_t match_token_at_5(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 5;
            }
            if (match_comment(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 6;
            }
            if (match_step_line(context, token))
            {
                start_rule(context, RuleType::step);
                build(context, token);
                return 7;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::background);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 6;
            }

            std::string state_comment = "State: 5 - GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 5;
        }

        // GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t match_token_at_6(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 6;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::description);
                start_rule(context, RuleType::step);
                build(context, token);
                return 7;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::description);
                    end_rule(context, RuleType::background);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 6;
            }

            std::string state_comment = "State: 6 - GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 6;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0
        std::size_t match_token_at_7(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                start_rule(context, RuleType::dataTable);
                build(context, token);
                return 8;
            }
            if (match_doc_string_separator(context, token))
            {
                start_rule(context, RuleType::docString);
                build(context, token);
                return 52;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 7;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::background);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 7;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 7;
            }

            std::string state_comment = "State: 7 - GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 7;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
        std::size_t match_token_at_8(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                build(context, token);
                return 8;
            }
            if (match_doc_string_separator(context, token))
            {
                end_rule(context, RuleType::dataTable);
                start_rule(context, RuleType::docString);
                build(context, token);
                return 9;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 7;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::dataTable);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::background);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 8;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 8;
            }

            std::string state_comment = "State: 8 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 8;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
        std::size_t match_token_at_9(Token& token, context_type& context)
        {
            if (match_doc_string_separator(context, token))
            {
                build(context, token);
                return 10;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 9;
            }

            std::string state_comment = "State: 9 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 9;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
        std::size_t match_token_at_10(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 7;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::docString);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::background);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 10;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 10;
            }

            std::string state_comment = "State: 10 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 10;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0
        std::size_t match_token_at_11(Token& token, context_type& context)
        {
            if (match_tag_line(context, token))
            {
                build(context, token);
                return 11;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::tags);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 11;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 11;
            }

            std::string state_comment = "State: 11 - GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0";
            std::string expected_tokens = "#TagLine, #ScenarioLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 11;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
        std::size_t match_token_at_12(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 12;
            }
            if (match_comment(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 13;
            }
            if (match_step_line(context, token))
            {
                start_rule(context, RuleType::step);
                build(context, token);
                return 14;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 18;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 19;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 13;
            }

            std::string state_comment = "State: 12 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 12;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t match_token_at_13(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 13;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::description);
                start_rule(context, RuleType::step);
                build(context, token);
                return 14;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::description);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 18;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::description);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::description);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 19;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 13;
            }

            std::string state_comment = "State: 13 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 13;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
        std::size_t match_token_at_14(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                start_rule(context, RuleType::dataTable);
                build(context, token);
                return 15;
            }
            if (match_doc_string_separator(context, token))
            {
                start_rule(context, RuleType::docString);
                build(context, token);
                return 49;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 14;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::step);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 18;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 19;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 14;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 14;
            }

            std::string state_comment = "State: 14 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 14;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
        std::size_t match_token_at_15(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                build(context, token);
                return 15;
            }
            if (match_doc_string_separator(context, token))
            {
                end_rule(context, RuleType::dataTable);
                start_rule(context, RuleType::docString);
                build(context, token);
                return 16;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 14;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::dataTable);
                    end_rule(context, RuleType::step);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 18;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::dataTable);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 19;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 15;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 15;
            }

            std::string state_comment = "State: 15 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 15;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
        std::size_t match_token_at_16(Token& token, context_type& context)
        {
            if (match_doc_string_separator(context, token))
            {
                build(context, token);
                return 17;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 16;
            }

            std::string state_comment = "State: 16 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 16;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
        std::size_t match_token_at_17(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 14;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::docString);
                    end_rule(context, RuleType::step);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 18;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::docString);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 19;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 17;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 17;
            }

            std::string state_comment = "State: 17 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 17;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
        std::size_t match_token_at_18(Token& token, context_type& context)
        {
            if (match_tag_line(context, token))
            {
                build(context, token);
                return 18;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::tags);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 19;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 18;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 18;
            }

            std::string state_comment = "State: 18 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0";
            std::string expected_tokens = "#TagLine, #ExamplesLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 18;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
        std::size_t match_token_at_19(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 19;
            }
            if (match_comment(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 20;
            }
            if (match_table_row(context, token))
            {
                start_rule(context, RuleType::examplesTable);
                build(context, token);
                return 21;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::examples);
                    end_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 18;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::examples);
                    end_rule(context, RuleType::examplesDefinition);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 19;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 20;
            }

            std::string state_comment = "State: 19 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 19;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t match_token_at_20(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 20;
            }
            if (match_table_row(context, token))
            {
                end_rule(context, RuleType::description);
                start_rule(context, RuleType::examplesTable);
                build(context, token);
                return 21;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::description);
                    end_rule(context, RuleType::examples);
                    end_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 18;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::description);
                    end_rule(context, RuleType::examples);
                    end_rule(context, RuleType::examplesDefinition);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 19;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 20;
            }

            std::string state_comment = "State: 20 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 20;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
        std::size_t match_token_at_21(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::examplesTable);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                build(context, token);
                return 21;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::examplesTable);
                    end_rule(context, RuleType::examples);
                    end_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 18;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::examplesTable);
                    end_rule(context, RuleType::examples);
                    end_rule(context, RuleType::examplesDefinition);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::examplesTable);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::examplesTable);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 19;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::examplesTable);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::examplesTable);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 21;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 21;
            }

            std::string state_comment = "State: 21 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 21;
        }

        // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0
        std::size_t match_token_at_22(Token& token, context_type& context)
        {
            if (match_tag_line(context, token))
            {
                build(context, token);
                return 22;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::tags);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 22;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 22;
            }

            std::string state_comment = "State: 22 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0";
            std::string expected_tokens = "#TagLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 22;
        }

        // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>#RuleLine:0
        std::size_t match_token_at_23(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::ruleHeader);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 24;
            }
            if (match_background_line(context, token))
            {
                end_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::background);
                build(context, token);
                return 25;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::ruleHeader);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::ruleHeader);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::ruleHeader);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 24;
            }

            std::string state_comment = "State: 23 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>#RuleLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 23;
        }

        // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t match_token_at_24(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::ruleHeader);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 24;
            }
            if (match_background_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::background);
                build(context, token);
                return 25;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::description);
                    end_rule(context, RuleType::ruleHeader);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::ruleHeader);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::ruleHeader);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 24;
            }

            std::string state_comment = "State: 24 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 24;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0
        std::size_t match_token_at_25(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 25;
            }
            if (match_comment(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 26;
            }
            if (match_step_line(context, token))
            {
                start_rule(context, RuleType::step);
                build(context, token);
                return 27;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::background);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 26;
            }

            std::string state_comment = "State: 25 - GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 25;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t match_token_at_26(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 26;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::description);
                start_rule(context, RuleType::step);
                build(context, token);
                return 27;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::description);
                    end_rule(context, RuleType::background);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 26;
            }

            std::string state_comment = "State: 26 - GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 26;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0
        std::size_t match_token_at_27(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                start_rule(context, RuleType::dataTable);
                build(context, token);
                return 28;
            }
            if (match_doc_string_separator(context, token))
            {
                start_rule(context, RuleType::docString);
                build(context, token);
                return 46;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 27;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::background);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 27;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 27;
            }

            std::string state_comment = "State: 27 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 27;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
        std::size_t match_token_at_28(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                build(context, token);
                return 28;
            }
            if (match_doc_string_separator(context, token))
            {
                end_rule(context, RuleType::dataTable);
                start_rule(context, RuleType::docString);
                build(context, token);
                return 29;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 27;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::dataTable);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::background);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 28;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 28;
            }

            std::string state_comment = "State: 28 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 28;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
        std::size_t match_token_at_29(Token& token, context_type& context)
        {
            if (match_doc_string_separator(context, token))
            {
                build(context, token);
                return 30;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 29;
            }

            std::string state_comment = "State: 29 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 29;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
        std::size_t match_token_at_30(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 27;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::docString);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::background);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 30;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 30;
            }

            std::string state_comment = "State: 30 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 30;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0
        std::size_t match_token_at_31(Token& token, context_type& context)
        {
            if (match_tag_line(context, token))
            {
                build(context, token);
                return 31;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::tags);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 31;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 31;
            }

            std::string state_comment = "State: 31 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0";
            std::string expected_tokens = "#TagLine, #ScenarioLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 31;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
        std::size_t match_token_at_32(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 32;
            }
            if (match_comment(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 33;
            }
            if (match_step_line(context, token))
            {
                start_rule(context, RuleType::step);
                build(context, token);
                return 34;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 38;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 39;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 33;
            }

            std::string state_comment = "State: 32 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 32;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t match_token_at_33(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 33;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::description);
                start_rule(context, RuleType::step);
                build(context, token);
                return 34;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::description);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 38;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::description);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::description);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 39;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 33;
            }

            std::string state_comment = "State: 33 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 33;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
        std::size_t match_token_at_34(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                start_rule(context, RuleType::dataTable);
                build(context, token);
                return 35;
            }
            if (match_doc_string_separator(context, token))
            {
                start_rule(context, RuleType::docString);
                build(context, token);
                return 43;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 34;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::step);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 38;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 39;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 34;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 34;
            }

            std::string state_comment = "State: 34 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 34;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
        std::size_t match_token_at_35(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                build(context, token);
                return 35;
            }
            if (match_doc_string_separator(context, token))
            {
                end_rule(context, RuleType::dataTable);
                start_rule(context, RuleType::docString);
                build(context, token);
                return 36;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 34;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::dataTable);
                    end_rule(context, RuleType::step);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 38;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::dataTable);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 39;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 35;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 35;
            }

            std::string state_comment = "State: 35 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 35;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
        std::size_t match_token_at_36(Token& token, context_type& context)
        {
            if (match_doc_string_separator(context, token))
            {
                build(context, token);
                return 37;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 36;
            }

            std::string state_comment = "State: 36 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 36;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
        std::size_t match_token_at_37(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 34;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::docString);
                    end_rule(context, RuleType::step);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 38;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::docString);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 39;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 37;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 37;
            }

            std::string state_comment = "State: 37 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 37;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
        std::size_t match_token_at_38(Token& token, context_type& context)
        {
            if (match_tag_line(context, token))
            {
                build(context, token);
                return 38;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::tags);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 39;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 38;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 38;
            }

            std::string state_comment = "State: 38 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0";
            std::string expected_tokens = "#TagLine, #ExamplesLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 38;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
        std::size_t match_token_at_39(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 39;
            }
            if (match_comment(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 40;
            }
            if (match_table_row(context, token))
            {
                start_rule(context, RuleType::examplesTable);
                build(context, token);
                return 41;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::examples);
                    end_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 38;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::examples);
                    end_rule(context, RuleType::examplesDefinition);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 39;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                start_rule(context, RuleType::description);
                build(context, token);
                return 40;
            }

            std::string state_comment = "State: 39 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 39;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t match_token_at_40(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 40;
            }
            if (match_table_row(context, token))
            {
                end_rule(context, RuleType::description);
                start_rule(context, RuleType::examplesTable);
                build(context, token);
                return 41;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::description);
                    end_rule(context, RuleType::examples);
                    end_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 38;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::description);
                    end_rule(context, RuleType::examples);
                    end_rule(context, RuleType::examplesDefinition);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 39;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::description);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 40;
            }

            std::string state_comment = "State: 40 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 40;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
        std::size_t match_token_at_41(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::examplesTable);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                build(context, token);
                return 41;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::examplesTable);
                    end_rule(context, RuleType::examples);
                    end_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 38;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::examplesTable);
                    end_rule(context, RuleType::examples);
                    end_rule(context, RuleType::examplesDefinition);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::examplesTable);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::examplesTable);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 39;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::examplesTable);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::examplesTable);
                end_rule(context, RuleType::examples);
                end_rule(context, RuleType::examplesDefinition);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 41;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 41;
            }

            std::string state_comment = "State: 41 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 41;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
        std::size_t match_token_at_43(Token& token, context_type& context)
        {
            if (match_doc_string_separator(context, token))
            {
                build(context, token);
                return 44;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 43;
            }

            std::string state_comment = "State: 43 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 43;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
        std::size_t match_token_at_44(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                end_rule(context, RuleType::docString);
                start_rule(context, RuleType::dataTable);
                build(context, token);
                return 45;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 34;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::docString);
                    end_rule(context, RuleType::step);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 38;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::docString);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 39;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 44;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 44;
            }

            std::string state_comment = "State: 44 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 44;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
        std::size_t match_token_at_45(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                build(context, token);
                return 45;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 34;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::dataTable);
                    end_rule(context, RuleType::step);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 38;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::dataTable);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 39;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 45;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 45;
            }

            std::string state_comment = "State: 45 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 45;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
        std::size_t match_token_at_46(Token& token, context_type& context)
        {
            if (match_doc_string_separator(context, token))
            {
                build(context, token);
                return 47;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 46;
            }

            std::string state_comment = "State: 46 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 46;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
        std::size_t match_token_at_47(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                end_rule(context, RuleType::docString);
                start_rule(context, RuleType::dataTable);
                build(context, token);
                return 48;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 27;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::docString);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::background);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 47;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 47;
            }

            std::string state_comment = "State: 47 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 47;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
        std::size_t match_token_at_48(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                build(context, token);
                return 48;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 27;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::dataTable);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::background);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 31;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 32;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::rule);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 48;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 48;
            }

            std::string state_comment = "State: 48 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 48;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
        std::size_t match_token_at_49(Token& token, context_type& context)
        {
            if (match_doc_string_separator(context, token))
            {
                build(context, token);
                return 50;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 49;
            }

            std::string state_comment = "State: 49 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 49;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
        std::size_t match_token_at_50(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                end_rule(context, RuleType::docString);
                start_rule(context, RuleType::dataTable);
                build(context, token);
                return 51;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 14;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::docString);
                    end_rule(context, RuleType::step);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 18;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::docString);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 19;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 50;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 50;
            }

            std::string state_comment = "State: 50 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 50;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
        std::size_t match_token_at_51(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                build(context, token);
                return 51;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 14;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_1(context, token))
                {
                    end_rule(context, RuleType::dataTable);
                    end_rule(context, RuleType::step);
                    start_rule(context, RuleType::examplesDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 18;
                }
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::dataTable);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::scenario);
                    end_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_examples_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::examplesDefinition);
                start_rule(context, RuleType::examples);
                build(context, token);
                return 19;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::scenario);
                end_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 51;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 51;
            }

            std::string state_comment = "State: 51 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 51;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
        std::size_t match_token_at_52(Token& token, context_type& context)
        {
            if (match_doc_string_separator(context, token))
            {
                build(context, token);
                return 53;
            }
            if (match_other(context, token))
            {
                build(context, token);
                return 52;
            }

            std::string state_comment = "State: 52 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 52;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
        std::size_t match_token_at_53(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                end_rule(context, RuleType::docString);
                start_rule(context, RuleType::dataTable);
                build(context, token);
                return 54;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 7;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::docString);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::background);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::docString);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 53;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 53;
            }

            std::string state_comment = "State: 53 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 53;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
        std::size_t match_token_at_54(Token& token, context_type& context)
        {
            if (match_e_o_f(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                end_rule(context, RuleType::feature);
                build(context, token);
                return 42;
            }
            if (match_table_row(context, token))
            {
                build(context, token);
                return 54;
            }
            if (match_step_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                start_rule(context, RuleType::step);
                build(context, token);
                return 7;
            }
            if (match_tag_line(context, token))
            {
                if (lookahead_0(context, token))
                {
                    end_rule(context, RuleType::dataTable);
                    end_rule(context, RuleType::step);
                    end_rule(context, RuleType::background);
                    start_rule(context, RuleType::scenarioDefinition);
                    start_rule(context, RuleType::tags);
                    build(context, token);
                    return 11;
                }
            }
            if (match_tag_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                start_rule(context, RuleType::tags);
                build(context, token);
                return 22;
            }
            if (match_scenario_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::scenarioDefinition);
                start_rule(context, RuleType::scenario);
                build(context, token);
                return 12;
            }
            if (match_rule_line(context, token))
            {
                end_rule(context, RuleType::dataTable);
                end_rule(context, RuleType::step);
                end_rule(context, RuleType::background);
                start_rule(context, RuleType::rule);
                start_rule(context, RuleType::ruleHeader);
                build(context, token);
                return 23;
            }
            if (match_comment(context, token))
            {
                build(context, token);
                return 54;
            }
            if (match_empty(context, token))
            {
                build(context, token);
                return 54;
            }

            std::string state_comment = "State: 54 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.is_eof() ? new_parser_error<UnexpectedEof>(token, expected_tokens, state_comment) : new_parser_error<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stop_at_first_error)
            {
                throw *error_pointer;
            }

            context.add_error(std::move(error_pointer));

            return 54;
        }

        std::size_t match_token(std::size_t state, Token& token, context_type& context)
        {
            switch (state)
            {
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
                case 51:
                    return match_token_at_51(token, context);
                case 52:
                    return match_token_at_52(token, context);
                case 53:
                    return match_token_at_53(token, context);
                case 54:
                    return match_token_at_54(token, context);
                default:
                    throw std::runtime_error("invalid operation: " + std::to_string(state));
            }
        }
    };

}

// NOLINTEND
#endif
