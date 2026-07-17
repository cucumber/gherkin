#ifndef CUCUMBER_GHERKIN_PARSER_HPP
#define CUCUMBER_GHERKIN_PARSER_HPP

#include "cucumber/gherkin/exceptions.hpp"
#include "cucumber/gherkin/parser_base.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>

// This File is generated. Do not edit! Edit gherkin-cpp-Parser.razor instead.
// NOLINTBEGIN

namespace cucumber::gherkin
{
    template<typename BuilderType>
    class Parser : public ParserBase<BuilderType>
    {
    public:
        using Parent = ParserBase<BuilderType>;
        using Parent::Parent;
        using Parent::parse;
        using ContextType = typename Parent::ContextType;

    protected:
        void parse(ContextType& context) override
        {
            StartRule(context, RuleType::gherkinDocument);

            std::size_t state = 0;

            while (true)
            {
                auto token = context.ReadToken();
                state = MatchToken(state, token, context);

                if (token.IsEof())
                {
                    break;
                }
            }

            EndRule(context, RuleType::gherkinDocument);

            if (context.HasErrors())
            {
                throw CompositeParserError(context.errorPointers);
            }
        }

        void Build(ContextType& context, Token& token)
        {
            context.builder.Build(token);
        }

        void StartRule(ContextType& context, RuleType ruleType)
        {
            HandleAstError(context, ruleType,
                [&context](auto rtype)
                {
                    context.builder.StartRule(rtype);
                });
        }

        void EndRule(ContextType& context, RuleType ruleType)
        {
            HandleAstError(context, ruleType,
                [&context](auto rtype)
                {
                    context.builder.EndRule(rtype);
                });
        }

        template<typename Argument, typename Action>
        bool HandleExternalError(ContextType& context, bool default_value, Argument&& argument, Action&& action)
        {
            using RetType = decltype(action(argument));

            try
            {
                if constexpr (std::is_same_v<RetType, void>)
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
                for (const auto& error_pointer : e.Errors())
                {
                    context.AddError(error_pointer);
                }
            }
            catch (const ParserError& e)
            {
                auto error_pointer = NewParserError<ParserError>(e);
                context.AddError(error_pointer);
            }

            return default_value;
        }

        template<typename Argument, typename Action>
        void HandleAstError(ContextType& context, Argument&& argument, Action&& action)
        {
            HandleExternalError(context, true, argument, action);
        }

        bool MatchEOF(ContextType& context, Token& token)
        {
            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchEOF(tok);
                });
        }

        bool MatchEmpty(ContextType& context, Token& token)
        {
            if (token.IsEof())
            {
                return false;
            }

            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchEmpty(tok);
                });
        }

        bool MatchComment(ContextType& context, Token& token)
        {
            if (token.IsEof())
            {
                return false;
            }

            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchComment(tok);
                });
        }

        bool MatchTagLine(ContextType& context, Token& token)
        {
            if (token.IsEof())
            {
                return false;
            }

            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchTagLine(tok);
                });
        }

        bool MatchFeatureLine(ContextType& context, Token& token)
        {
            if (token.IsEof())
            {
                return false;
            }

            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchFeatureLine(tok);
                });
        }

        bool MatchRuleLine(ContextType& context, Token& token)
        {
            if (token.IsEof())
            {
                return false;
            }

            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchRuleLine(tok);
                });
        }

        bool MatchBackgroundLine(ContextType& context, Token& token)
        {
            if (token.IsEof())
            {
                return false;
            }

            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchBackgroundLine(tok);
                });
        }

        bool MatchScenarioLine(ContextType& context, Token& token)
        {
            if (token.IsEof())
            {
                return false;
            }

            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchScenarioLine(tok);
                });
        }

        bool MatchExamplesLine(ContextType& context, Token& token)
        {
            if (token.IsEof())
            {
                return false;
            }

            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchExamplesLine(tok);
                });
        }

        bool MatchStepLine(ContextType& context, Token& token)
        {
            if (token.IsEof())
            {
                return false;
            }

            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchStepLine(tok);
                });
        }

        bool MatchDocStringSeparator(ContextType& context, Token& token)
        {
            if (token.IsEof())
            {
                return false;
            }

            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchDocStringSeparator(tok);
                });
        }

        bool MatchTableRow(ContextType& context, Token& token)
        {
            if (token.IsEof())
            {
                return false;
            }

            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchTableRow(tok);
                });
        }

        bool MatchLanguage(ContextType& context, Token& token)
        {
            if (token.IsEof())
            {
                return false;
            }

            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchLanguage(tok);
                });
        }

        bool MatchOther(ContextType& context, Token& token)
        {
            if (token.IsEof())
            {
                return false;
            }

            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchOther(tok);
                });
        }

        bool LookAhead0(ContextType& context, Token& current_token)
        {
            Token token;
            TokenQueue queue;
            bool match = false;

            while (true)
            {
                token = context.ReadToken();
                queue.push_back(token);

                if (MatchScenarioLine(context, token) || false)
                {
                    match = true;
                    break;
                }

                if (!(MatchEmpty(context, token) || MatchComment(context, token) || MatchTagLine(context, token) || false))
                {
                    break;
                }
            }

            context.PushTokens(queue);

            return match;
        }

        bool LookAhead1(ContextType& context, Token& current_token)
        {
            Token token;
            TokenQueue queue;
            bool match = false;

            while (true)
            {
                token = context.ReadToken();
                queue.push_back(token);

                if (MatchExamplesLine(context, token) || false)
                {
                    match = true;
                    break;
                }

                if (!(MatchEmpty(context, token) || MatchComment(context, token) || MatchTagLine(context, token) || false))
                {
                    break;
                }
            }

            context.PushTokens(queue);

            return match;
        }

        // Start
        std::size_t MatchTokenAt0(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                Build(context, token);
                return 42;
            }
            if (MatchLanguage(context, token))
            {
                StartRule(context, RuleType::feature);
                StartRule(context, RuleType::featureHeader);
                Build(context, token);
                return 1;
            }
            if (MatchTagLine(context, token))
            {
                StartRule(context, RuleType::feature);
                StartRule(context, RuleType::featureHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 2;
            }
            if (MatchFeatureLine(context, token))
            {
                StartRule(context, RuleType::feature);
                StartRule(context, RuleType::featureHeader);
                Build(context, token);
                return 3;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 0;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 0;
            }

            std::string state_comment = "State: 0 - Start";
            std::string expected_tokens = "#EOF, #Language, #TagLine, #FeatureLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 0;
        }

        // GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0
        std::size_t MatchTokenAt1(Token& token, ContextType& context)
        {
            if (MatchTagLine(context, token))
            {
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 2;
            }
            if (MatchFeatureLine(context, token))
            {
                Build(context, token);
                return 3;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 1;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 1;
            }

            std::string state_comment = "State: 1 - GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0";
            std::string expected_tokens = "#TagLine, #FeatureLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 1;
        }

        // GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0
        std::size_t MatchTokenAt2(Token& token, ContextType& context)
        {
            if (MatchTagLine(context, token))
            {
                Build(context, token);
                return 2;
            }
            if (MatchFeatureLine(context, token))
            {
                EndRule(context, RuleType::tags);
                Build(context, token);
                return 3;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 2;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 2;
            }

            std::string state_comment = "State: 2 - GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0";
            std::string expected_tokens = "#TagLine, #FeatureLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 2;
        }

        // GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0
        std::size_t MatchTokenAt3(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::featureHeader);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 3;
            }
            if (MatchComment(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 4;
            }
            if (MatchBackgroundLine(context, token))
            {
                EndRule(context, RuleType::featureHeader);
                StartRule(context, RuleType::background);
                Build(context, token);
                return 5;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::featureHeader);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::featureHeader);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::featureHeader);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::featureHeader);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 4;
            }

            std::string state_comment = "State: 3 - GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 3;
        }

        // GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt4(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::featureHeader);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 4;
            }
            if (MatchBackgroundLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::featureHeader);
                StartRule(context, RuleType::background);
                Build(context, token);
                return 5;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::description);
                    EndRule(context, RuleType::featureHeader);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::featureHeader);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::featureHeader);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::featureHeader);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 4;
            }

            std::string state_comment = "State: 4 - GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 4;
        }

        // GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0
        std::size_t MatchTokenAt5(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 5;
            }
            if (MatchComment(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 6;
            }
            if (MatchStepLine(context, token))
            {
                StartRule(context, RuleType::step);
                Build(context, token);
                return 7;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::background);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 6;
            }

            std::string state_comment = "State: 5 - GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 5;
        }

        // GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt6(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 6;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::description);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 7;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::description);
                    EndRule(context, RuleType::background);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 6;
            }

            std::string state_comment = "State: 6 - GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 6;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0
        std::size_t MatchTokenAt7(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                StartRule(context, RuleType::dataTable);
                Build(context, token);
                return 8;
            }
            if (MatchDocStringSeparator(context, token))
            {
                StartRule(context, RuleType::docString);
                Build(context, token);
                return 52;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 7;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::background);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 7;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 7;
            }

            std::string state_comment = "State: 7 - GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 7;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt8(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                Build(context, token);
                return 8;
            }
            if (MatchDocStringSeparator(context, token))
            {
                EndRule(context, RuleType::dataTable);
                StartRule(context, RuleType::docString);
                Build(context, token);
                return 9;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 7;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::dataTable);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::background);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 8;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 8;
            }

            std::string state_comment = "State: 8 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 8;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt9(Token& token, ContextType& context)
        {
            if (MatchDocStringSeparator(context, token))
            {
                Build(context, token);
                return 10;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 9;
            }

            std::string state_comment = "State: 9 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 9;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt10(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 7;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::docString);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::background);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 10;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 10;
            }

            std::string state_comment = "State: 10 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 10;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0
        std::size_t MatchTokenAt11(Token& token, ContextType& context)
        {
            if (MatchTagLine(context, token))
            {
                Build(context, token);
                return 11;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::tags);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 11;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 11;
            }

            std::string state_comment = "State: 11 - GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0";
            std::string expected_tokens = "#TagLine, #ScenarioLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 11;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
        std::size_t MatchTokenAt12(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 12;
            }
            if (MatchComment(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 13;
            }
            if (MatchStepLine(context, token))
            {
                StartRule(context, RuleType::step);
                Build(context, token);
                return 14;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 13;
            }

            std::string state_comment = "State: 12 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 12;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt13(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 13;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::description);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 14;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::description);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::description);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::description);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 13;
            }

            std::string state_comment = "State: 13 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 13;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
        std::size_t MatchTokenAt14(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                StartRule(context, RuleType::dataTable);
                Build(context, token);
                return 15;
            }
            if (MatchDocStringSeparator(context, token))
            {
                StartRule(context, RuleType::docString);
                Build(context, token);
                return 49;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 14;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::step);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 14;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 14;
            }

            std::string state_comment = "State: 14 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 14;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt15(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                Build(context, token);
                return 15;
            }
            if (MatchDocStringSeparator(context, token))
            {
                EndRule(context, RuleType::dataTable);
                StartRule(context, RuleType::docString);
                Build(context, token);
                return 16;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 14;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::dataTable);
                    EndRule(context, RuleType::step);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::dataTable);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 15;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 15;
            }

            std::string state_comment = "State: 15 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 15;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt16(Token& token, ContextType& context)
        {
            if (MatchDocStringSeparator(context, token))
            {
                Build(context, token);
                return 17;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 16;
            }

            std::string state_comment = "State: 16 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 16;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt17(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 14;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::docString);
                    EndRule(context, RuleType::step);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::docString);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 17;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 17;
            }

            std::string state_comment = "State: 17 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 17;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
        std::size_t MatchTokenAt18(Token& token, ContextType& context)
        {
            if (MatchTagLine(context, token))
            {
                Build(context, token);
                return 18;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::tags);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 19;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 18;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 18;
            }

            std::string state_comment = "State: 18 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0";
            std::string expected_tokens = "#TagLine, #ExamplesLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 18;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
        std::size_t MatchTokenAt19(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 19;
            }
            if (MatchComment(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 20;
            }
            if (MatchTableRow(context, token))
            {
                StartRule(context, RuleType::examplesTable);
                Build(context, token);
                return 21;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::examples);
                    EndRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::examples);
                    EndRule(context, RuleType::examplesDefinition);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 20;
            }

            std::string state_comment = "State: 19 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 19;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt20(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 20;
            }
            if (MatchTableRow(context, token))
            {
                EndRule(context, RuleType::description);
                StartRule(context, RuleType::examplesTable);
                Build(context, token);
                return 21;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::description);
                    EndRule(context, RuleType::examples);
                    EndRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::description);
                    EndRule(context, RuleType::examples);
                    EndRule(context, RuleType::examplesDefinition);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 20;
            }

            std::string state_comment = "State: 20 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 20;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
        std::size_t MatchTokenAt21(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::examplesTable);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                Build(context, token);
                return 21;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::examplesTable);
                    EndRule(context, RuleType::examples);
                    EndRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::examplesTable);
                    EndRule(context, RuleType::examples);
                    EndRule(context, RuleType::examplesDefinition);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::examplesTable);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::examplesTable);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::examplesTable);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::examplesTable);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 21;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 21;
            }

            std::string state_comment = "State: 21 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 21;
        }

        // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0
        std::size_t MatchTokenAt22(Token& token, ContextType& context)
        {
            if (MatchTagLine(context, token))
            {
                Build(context, token);
                return 22;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::tags);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 22;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 22;
            }

            std::string state_comment = "State: 22 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0";
            std::string expected_tokens = "#TagLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 22;
        }

        // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>#RuleLine:0
        std::size_t MatchTokenAt23(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::ruleHeader);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 24;
            }
            if (MatchBackgroundLine(context, token))
            {
                EndRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::background);
                Build(context, token);
                return 25;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::ruleHeader);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::ruleHeader);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::ruleHeader);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 24;
            }

            std::string state_comment = "State: 23 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>#RuleLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 23;
        }

        // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt24(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::ruleHeader);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 24;
            }
            if (MatchBackgroundLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::background);
                Build(context, token);
                return 25;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::description);
                    EndRule(context, RuleType::ruleHeader);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::ruleHeader);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::ruleHeader);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 24;
            }

            std::string state_comment = "State: 24 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 24;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0
        std::size_t MatchTokenAt25(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 25;
            }
            if (MatchComment(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 26;
            }
            if (MatchStepLine(context, token))
            {
                StartRule(context, RuleType::step);
                Build(context, token);
                return 27;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::background);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 26;
            }

            std::string state_comment = "State: 25 - GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 25;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt26(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 26;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::description);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 27;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::description);
                    EndRule(context, RuleType::background);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 26;
            }

            std::string state_comment = "State: 26 - GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 26;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0
        std::size_t MatchTokenAt27(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                StartRule(context, RuleType::dataTable);
                Build(context, token);
                return 28;
            }
            if (MatchDocStringSeparator(context, token))
            {
                StartRule(context, RuleType::docString);
                Build(context, token);
                return 46;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 27;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::background);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 27;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 27;
            }

            std::string state_comment = "State: 27 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 27;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt28(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                Build(context, token);
                return 28;
            }
            if (MatchDocStringSeparator(context, token))
            {
                EndRule(context, RuleType::dataTable);
                StartRule(context, RuleType::docString);
                Build(context, token);
                return 29;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 27;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::dataTable);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::background);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 28;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 28;
            }

            std::string state_comment = "State: 28 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 28;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt29(Token& token, ContextType& context)
        {
            if (MatchDocStringSeparator(context, token))
            {
                Build(context, token);
                return 30;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 29;
            }

            std::string state_comment = "State: 29 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 29;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt30(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 27;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::docString);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::background);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 30;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 30;
            }

            std::string state_comment = "State: 30 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 30;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0
        std::size_t MatchTokenAt31(Token& token, ContextType& context)
        {
            if (MatchTagLine(context, token))
            {
                Build(context, token);
                return 31;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::tags);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 31;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 31;
            }

            std::string state_comment = "State: 31 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0";
            std::string expected_tokens = "#TagLine, #ScenarioLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 31;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
        std::size_t MatchTokenAt32(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 32;
            }
            if (MatchComment(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 33;
            }
            if (MatchStepLine(context, token))
            {
                StartRule(context, RuleType::step);
                Build(context, token);
                return 34;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 33;
            }

            std::string state_comment = "State: 32 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 32;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt33(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 33;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::description);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 34;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::description);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::description);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::description);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 33;
            }

            std::string state_comment = "State: 33 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 33;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
        std::size_t MatchTokenAt34(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                StartRule(context, RuleType::dataTable);
                Build(context, token);
                return 35;
            }
            if (MatchDocStringSeparator(context, token))
            {
                StartRule(context, RuleType::docString);
                Build(context, token);
                return 43;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 34;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::step);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 34;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 34;
            }

            std::string state_comment = "State: 34 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 34;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt35(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                Build(context, token);
                return 35;
            }
            if (MatchDocStringSeparator(context, token))
            {
                EndRule(context, RuleType::dataTable);
                StartRule(context, RuleType::docString);
                Build(context, token);
                return 36;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 34;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::dataTable);
                    EndRule(context, RuleType::step);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::dataTable);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 35;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 35;
            }

            std::string state_comment = "State: 35 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 35;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt36(Token& token, ContextType& context)
        {
            if (MatchDocStringSeparator(context, token))
            {
                Build(context, token);
                return 37;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 36;
            }

            std::string state_comment = "State: 36 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 36;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt37(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 34;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::docString);
                    EndRule(context, RuleType::step);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::docString);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 37;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 37;
            }

            std::string state_comment = "State: 37 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 37;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
        std::size_t MatchTokenAt38(Token& token, ContextType& context)
        {
            if (MatchTagLine(context, token))
            {
                Build(context, token);
                return 38;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::tags);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 39;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 38;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 38;
            }

            std::string state_comment = "State: 38 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0";
            std::string expected_tokens = "#TagLine, #ExamplesLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 38;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
        std::size_t MatchTokenAt39(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 39;
            }
            if (MatchComment(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 40;
            }
            if (MatchTableRow(context, token))
            {
                StartRule(context, RuleType::examplesTable);
                Build(context, token);
                return 41;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::examples);
                    EndRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::examples);
                    EndRule(context, RuleType::examplesDefinition);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::description);
                Build(context, token);
                return 40;
            }

            std::string state_comment = "State: 39 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0";
            std::string expected_tokens = "#EOF, #Empty, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 39;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt40(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 40;
            }
            if (MatchTableRow(context, token))
            {
                EndRule(context, RuleType::description);
                StartRule(context, RuleType::examplesTable);
                Build(context, token);
                return 41;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::description);
                    EndRule(context, RuleType::examples);
                    EndRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::description);
                    EndRule(context, RuleType::examples);
                    EndRule(context, RuleType::examplesDefinition);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::description);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 40;
            }

            std::string state_comment = "State: 40 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expected_tokens = "#EOF, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 40;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
        std::size_t MatchTokenAt41(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::examplesTable);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                Build(context, token);
                return 41;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::examplesTable);
                    EndRule(context, RuleType::examples);
                    EndRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::examplesTable);
                    EndRule(context, RuleType::examples);
                    EndRule(context, RuleType::examplesDefinition);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::examplesTable);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::examplesTable);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::examplesTable);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::examplesTable);
                EndRule(context, RuleType::examples);
                EndRule(context, RuleType::examplesDefinition);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 41;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 41;
            }

            std::string state_comment = "State: 41 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 41;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt43(Token& token, ContextType& context)
        {
            if (MatchDocStringSeparator(context, token))
            {
                Build(context, token);
                return 44;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 43;
            }

            std::string state_comment = "State: 43 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 43;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt44(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                EndRule(context, RuleType::docString);
                StartRule(context, RuleType::dataTable);
                Build(context, token);
                return 45;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 34;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::docString);
                    EndRule(context, RuleType::step);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::docString);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 44;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 44;
            }

            std::string state_comment = "State: 44 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 44;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt45(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                Build(context, token);
                return 45;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 34;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::dataTable);
                    EndRule(context, RuleType::step);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::dataTable);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 45;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 45;
            }

            std::string state_comment = "State: 45 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 45;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt46(Token& token, ContextType& context)
        {
            if (MatchDocStringSeparator(context, token))
            {
                Build(context, token);
                return 47;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 46;
            }

            std::string state_comment = "State: 46 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 46;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt47(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                EndRule(context, RuleType::docString);
                StartRule(context, RuleType::dataTable);
                Build(context, token);
                return 48;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 27;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::docString);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::background);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 47;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 47;
            }

            std::string state_comment = "State: 47 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 47;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt48(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                Build(context, token);
                return 48;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 27;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::dataTable);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::background);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::rule);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 48;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 48;
            }

            std::string state_comment = "State: 48 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 48;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt49(Token& token, ContextType& context)
        {
            if (MatchDocStringSeparator(context, token))
            {
                Build(context, token);
                return 50;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 49;
            }

            std::string state_comment = "State: 49 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 49;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt50(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                EndRule(context, RuleType::docString);
                StartRule(context, RuleType::dataTable);
                Build(context, token);
                return 51;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 14;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::docString);
                    EndRule(context, RuleType::step);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::docString);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 50;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 50;
            }

            std::string state_comment = "State: 50 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 50;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt51(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                Build(context, token);
                return 51;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 14;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead1(context, token))
                {
                    EndRule(context, RuleType::dataTable);
                    EndRule(context, RuleType::step);
                    StartRule(context, RuleType::examplesDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::dataTable);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::scenario);
                    EndRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::examplesDefinition);
                StartRule(context, RuleType::examples);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::scenario);
                EndRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 51;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 51;
            }

            std::string state_comment = "State: 51 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 51;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt52(Token& token, ContextType& context)
        {
            if (MatchDocStringSeparator(context, token))
            {
                Build(context, token);
                return 53;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 52;
            }

            std::string state_comment = "State: 52 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0";
            std::string expected_tokens = "#DocStringSeparator, #Other";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 52;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt53(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                EndRule(context, RuleType::docString);
                StartRule(context, RuleType::dataTable);
                Build(context, token);
                return 54;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 7;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::docString);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::background);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::docString);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 53;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 53;
            }

            std::string state_comment = "State: 53 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 53;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt54(Token& token, ContextType& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                EndRule(context, RuleType::feature);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                Build(context, token);
                return 54;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                StartRule(context, RuleType::step);
                Build(context, token);
                return 7;
            }
            if (MatchTagLine(context, token))
            {
                if (LookAhead0(context, token))
                {
                    EndRule(context, RuleType::dataTable);
                    EndRule(context, RuleType::step);
                    EndRule(context, RuleType::background);
                    StartRule(context, RuleType::scenarioDefinition);
                    StartRule(context, RuleType::tags);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                StartRule(context, RuleType::tags);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::scenarioDefinition);
                StartRule(context, RuleType::scenario);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::dataTable);
                EndRule(context, RuleType::step);
                EndRule(context, RuleType::background);
                StartRule(context, RuleType::rule);
                StartRule(context, RuleType::ruleHeader);
                Build(context, token);
                return 23;
            }
            if (MatchComment(context, token))
            {
                Build(context, token);
                return 54;
            }
            if (MatchEmpty(context, token))
            {
                Build(context, token);
                return 54;
            }

            std::string state_comment = "State: 54 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0";
            std::string expected_tokens = "#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto error_pointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expected_tokens, state_comment) : NewParserError<UnexpectedToken>(token, expected_tokens, state_comment);

            if (context.stopAtFirstError)
            {
                throw *error_pointer;
            }

            context.AddError(std::move(error_pointer));

            return 54;
        }

        std::size_t MatchToken(std::size_t state, Token& token, ContextType& context)
        {
            switch (state)
            {
                case 0:
                    return MatchTokenAt0(token, context);
                case 1:
                    return MatchTokenAt1(token, context);
                case 2:
                    return MatchTokenAt2(token, context);
                case 3:
                    return MatchTokenAt3(token, context);
                case 4:
                    return MatchTokenAt4(token, context);
                case 5:
                    return MatchTokenAt5(token, context);
                case 6:
                    return MatchTokenAt6(token, context);
                case 7:
                    return MatchTokenAt7(token, context);
                case 8:
                    return MatchTokenAt8(token, context);
                case 9:
                    return MatchTokenAt9(token, context);
                case 10:
                    return MatchTokenAt10(token, context);
                case 11:
                    return MatchTokenAt11(token, context);
                case 12:
                    return MatchTokenAt12(token, context);
                case 13:
                    return MatchTokenAt13(token, context);
                case 14:
                    return MatchTokenAt14(token, context);
                case 15:
                    return MatchTokenAt15(token, context);
                case 16:
                    return MatchTokenAt16(token, context);
                case 17:
                    return MatchTokenAt17(token, context);
                case 18:
                    return MatchTokenAt18(token, context);
                case 19:
                    return MatchTokenAt19(token, context);
                case 20:
                    return MatchTokenAt20(token, context);
                case 21:
                    return MatchTokenAt21(token, context);
                case 22:
                    return MatchTokenAt22(token, context);
                case 23:
                    return MatchTokenAt23(token, context);
                case 24:
                    return MatchTokenAt24(token, context);
                case 25:
                    return MatchTokenAt25(token, context);
                case 26:
                    return MatchTokenAt26(token, context);
                case 27:
                    return MatchTokenAt27(token, context);
                case 28:
                    return MatchTokenAt28(token, context);
                case 29:
                    return MatchTokenAt29(token, context);
                case 30:
                    return MatchTokenAt30(token, context);
                case 31:
                    return MatchTokenAt31(token, context);
                case 32:
                    return MatchTokenAt32(token, context);
                case 33:
                    return MatchTokenAt33(token, context);
                case 34:
                    return MatchTokenAt34(token, context);
                case 35:
                    return MatchTokenAt35(token, context);
                case 36:
                    return MatchTokenAt36(token, context);
                case 37:
                    return MatchTokenAt37(token, context);
                case 38:
                    return MatchTokenAt38(token, context);
                case 39:
                    return MatchTokenAt39(token, context);
                case 40:
                    return MatchTokenAt40(token, context);
                case 41:
                    return MatchTokenAt41(token, context);
                case 43:
                    return MatchTokenAt43(token, context);
                case 44:
                    return MatchTokenAt44(token, context);
                case 45:
                    return MatchTokenAt45(token, context);
                case 46:
                    return MatchTokenAt46(token, context);
                case 47:
                    return MatchTokenAt47(token, context);
                case 48:
                    return MatchTokenAt48(token, context);
                case 49:
                    return MatchTokenAt49(token, context);
                case 50:
                    return MatchTokenAt50(token, context);
                case 51:
                    return MatchTokenAt51(token, context);
                case 52:
                    return MatchTokenAt52(token, context);
                case 53:
                    return MatchTokenAt53(token, context);
                case 54:
                    return MatchTokenAt54(token, context);
                default:
                    throw std::runtime_error("invalid operation: " + std::to_string(state));
            }
        }
    };

}

// NOLINTEND
#endif
