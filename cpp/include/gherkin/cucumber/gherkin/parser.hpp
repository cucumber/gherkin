// This File is generated. Do not edit! Edit gherkin-cpp-Parser.razor instead.
// NOLINTBEGIN
#pragma once

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

namespace cucumber::gherkin
{

    template<typename Builder = AstBuilder, typename Scanner = TokenScanner, typename Matcher = TokenMatcher>
    class Parser : public ParserBase<Builder, Scanner, Matcher>
    {
    public:
        using parent = ParserBase<Builder, Scanner, Matcher>;
        using parent::parent;
        using parent::Parse;
        using context_type = typename parent::context_type;

    protected:
        void Parse(context_type& context) override
        {
            StartRule(context, RuleType::GHERKIN_DOCUMENT);

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

            EndRule(context, RuleType::GHERKIN_DOCUMENT);

            if (context.HasErrors())
            {
                throw CompositeParserError(context.errorPointers);
            }
        }

        void Build(context_type& context, Token& token)
        {
            context.builder.Build(token);
        }

        void StartRule(context_type& context, RuleType ruleType)
        {
            HandleAstError(context, ruleType,
                [&context](auto rtype)
                {
                    context.builder.StartRule(rtype);
                });
        }

        void EndRule(context_type& context, RuleType ruleType)
        {
            HandleAstError(context, ruleType,
                [&context](auto rtype)
                {
                    context.builder.EndRule(rtype);
                });
        }

        template<typename Argument, typename Action>
        bool HandleExternalError(context_type& context, bool defaultValue, Argument&& argument, Action&& action)
        {
            using ret_type = decltype(action(argument));

            try
            {
                if constexpr (std::is_same_v<ret_type, void>)
                {
                    action(argument);
                    return defaultValue;
                }
                else
                {
                    return action(argument);
                }
            }
            catch (const CompositeParserError& e)
            {
                for (const auto& errorPointer : e.Errors())
                {
                    context.AddError(errorPointer);
                }
            }
            catch (const ParserError& e)
            {
                auto errorPointer = NewParserError<ParserError>(e);
                context.AddError(errorPointer);
            }

            return defaultValue;
        }

        template<typename Argument, typename Action>
        void HandleAstError(context_type& context, Argument&& argument, Action&& action)
        {
            HandleExternalError(context, true, argument, action);
        }

        bool MatchEOF(context_type& context, Token& token)
        {
            return HandleExternalError(context, false, token,
                [&context](auto& tok)
                {
                    return context.matcher.MatchEOF(tok);
                });
        }

        bool MatchEmpty(context_type& context, Token& token)
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

        bool MatchComment(context_type& context, Token& token)
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

        bool MatchTagLine(context_type& context, Token& token)
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

        bool MatchFeatureLine(context_type& context, Token& token)
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

        bool MatchRuleLine(context_type& context, Token& token)
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

        bool MatchBackgroundLine(context_type& context, Token& token)
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

        bool MatchScenarioLine(context_type& context, Token& token)
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

        bool MatchExamplesLine(context_type& context, Token& token)
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

        bool MatchStepLine(context_type& context, Token& token)
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

        bool MatchDocStringSeparator(context_type& context, Token& token)
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

        bool MatchTableRow(context_type& context, Token& token)
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

        bool MatchLanguage(context_type& context, Token& token)
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

        bool MatchOther(context_type& context, Token& token)
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

        bool Lookahead0(context_type& context, Token& currentToken)
        {
            Token token;
            token_queue queue;
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

        bool Lookahead1(context_type& context, Token& currentToken)
        {
            Token token;
            token_queue queue;
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
        std::size_t MatchTokenAt0(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                Build(context, token);
                return 42;
            }
            if (MatchLanguage(context, token))
            {
                StartRule(context, RuleType::FEATURE);
                StartRule(context, RuleType::FEATURE_HEADER);
                Build(context, token);
                return 1;
            }
            if (MatchTagLine(context, token))
            {
                StartRule(context, RuleType::FEATURE);
                StartRule(context, RuleType::FEATURE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 2;
            }
            if (MatchFeatureLine(context, token))
            {
                StartRule(context, RuleType::FEATURE);
                StartRule(context, RuleType::FEATURE_HEADER);
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

            std::string stateComment = "State: 0 - Start";
            std::string expectedTokens = "#EOF, #Language, #TagLine, #FeatureLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 0;
        }

        // GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0
        std::size_t MatchTokenAt1(Token& token, context_type& context)
        {
            if (MatchTagLine(context, token))
            {
                StartRule(context, RuleType::TAGS);
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

            std::string stateComment = "State: 1 - GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0";
            std::string expectedTokens = "#TagLine, #FeatureLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 1;
        }

        // GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0
        std::size_t MatchTokenAt2(Token& token, context_type& context)
        {
            if (MatchTagLine(context, token))
            {
                Build(context, token);
                return 2;
            }
            if (MatchFeatureLine(context, token))
            {
                EndRule(context, RuleType::TAGS);
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

            std::string stateComment = "State: 2 - GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0";
            std::string expectedTokens = "#TagLine, #FeatureLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 2;
        }

        // GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0
        std::size_t MatchTokenAt3(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::FEATURE_HEADER);
                EndRule(context, RuleType::FEATURE);
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
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 4;
            }
            if (MatchBackgroundLine(context, token))
            {
                EndRule(context, RuleType::FEATURE_HEADER);
                StartRule(context, RuleType::BACKGROUND);
                Build(context, token);
                return 5;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::FEATURE_HEADER);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::FEATURE_HEADER);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::FEATURE_HEADER);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::FEATURE_HEADER);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 4;
            }

            std::string stateComment = "State: 3 - GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0";
            std::string expectedTokens = "#EOF, #Empty, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 3;
        }

        // GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt4(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::FEATURE_HEADER);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::FEATURE_HEADER);
                StartRule(context, RuleType::BACKGROUND);
                Build(context, token);
                return 5;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DESCRIPTION);
                    EndRule(context, RuleType::FEATURE_HEADER);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::FEATURE_HEADER);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::FEATURE_HEADER);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::FEATURE_HEADER);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 4;
            }

            std::string stateComment = "State: 4 - GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expectedTokens = "#EOF, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 4;
        }

        // GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0
        std::size_t MatchTokenAt5(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::FEATURE);
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
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 6;
            }
            if (MatchStepLine(context, token))
            {
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 7;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::BACKGROUND);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 6;
            }

            std::string stateComment = "State: 5 - GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0";
            std::string expectedTokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 5;
        }

        // GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt6(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DESCRIPTION);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 7;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DESCRIPTION);
                    EndRule(context, RuleType::BACKGROUND);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 6;
            }

            std::string stateComment = "State: 6 - GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expectedTokens = "#EOF, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 6;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0
        std::size_t MatchTokenAt7(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::FEATURE);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                StartRule(context, RuleType::DATA_TABLE);
                Build(context, token);
                return 8;
            }
            if (MatchDocStringSeparator(context, token))
            {
                StartRule(context, RuleType::DOC_STRING);
                Build(context, token);
                return 52;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 7;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::BACKGROUND);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 7 - GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0";
            std::string expectedTokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 7;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt8(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DATA_TABLE);
                StartRule(context, RuleType::DOC_STRING);
                Build(context, token);
                return 9;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 7;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DATA_TABLE);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::BACKGROUND);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 8 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0";
            std::string expectedTokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 8;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt9(Token& token, context_type& context)
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

            std::string stateComment = "State: 9 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0";
            std::string expectedTokens = "#DocStringSeparator, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 9;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt10(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::FEATURE);
                Build(context, token);
                return 42;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 7;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DOC_STRING);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::BACKGROUND);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 10 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0";
            std::string expectedTokens = "#EOF, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 10;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0
        std::size_t MatchTokenAt11(Token& token, context_type& context)
        {
            if (MatchTagLine(context, token))
            {
                Build(context, token);
                return 11;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::TAGS);
                StartRule(context, RuleType::SCENARIO);
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

            std::string stateComment = "State: 11 - GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0";
            std::string expectedTokens = "#TagLine, #ScenarioLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 11;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
        std::size_t MatchTokenAt12(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::FEATURE);
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
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 13;
            }
            if (MatchStepLine(context, token))
            {
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 14;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 13;
            }

            std::string stateComment = "State: 12 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0";
            std::string expectedTokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 12;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt13(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DESCRIPTION);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 14;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::DESCRIPTION);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DESCRIPTION);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 13;
            }

            std::string stateComment = "State: 13 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expectedTokens = "#EOF, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 13;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
        std::size_t MatchTokenAt14(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::FEATURE);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                StartRule(context, RuleType::DATA_TABLE);
                Build(context, token);
                return 15;
            }
            if (MatchDocStringSeparator(context, token))
            {
                StartRule(context, RuleType::DOC_STRING);
                Build(context, token);
                return 49;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 14;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::STEP);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 14 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0";
            std::string expectedTokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 14;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt15(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DATA_TABLE);
                StartRule(context, RuleType::DOC_STRING);
                Build(context, token);
                return 16;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 14;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::DATA_TABLE);
                    EndRule(context, RuleType::STEP);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DATA_TABLE);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 15 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0";
            std::string expectedTokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 15;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt16(Token& token, context_type& context)
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

            std::string stateComment =
                "State: 16 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0";
            std::string expectedTokens = "#DocStringSeparator, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 16;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt17(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::FEATURE);
                Build(context, token);
                return 42;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 14;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::DOC_STRING);
                    EndRule(context, RuleType::STEP);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DOC_STRING);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment =
                "State: 17 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0";
            std::string expectedTokens = "#EOF, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 17;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
        std::size_t MatchTokenAt18(Token& token, context_type& context)
        {
            if (MatchTagLine(context, token))
            {
                Build(context, token);
                return 18;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::TAGS);
                StartRule(context, RuleType::EXAMPLES);
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

            std::string stateComment = "State: 18 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0";
            std::string expectedTokens = "#TagLine, #ExamplesLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 18;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
        std::size_t MatchTokenAt19(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::FEATURE);
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
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 20;
            }
            if (MatchTableRow(context, token))
            {
                StartRule(context, RuleType::EXAMPLES_TABLE);
                Build(context, token);
                return 21;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::EXAMPLES);
                    EndRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::EXAMPLES);
                    EndRule(context, RuleType::EXAMPLES_DEFINITION);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 20;
            }

            std::string stateComment = "State: 19 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0";
            std::string expectedTokens = "#EOF, #Empty, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 19;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt20(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DESCRIPTION);
                StartRule(context, RuleType::EXAMPLES_TABLE);
                Build(context, token);
                return 21;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::DESCRIPTION);
                    EndRule(context, RuleType::EXAMPLES);
                    EndRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DESCRIPTION);
                    EndRule(context, RuleType::EXAMPLES);
                    EndRule(context, RuleType::EXAMPLES_DEFINITION);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 20;
            }

            std::string stateComment = "State: 20 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expectedTokens = "#EOF, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 20;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
        std::size_t MatchTokenAt21(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::EXAMPLES_TABLE);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::FEATURE);
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
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::EXAMPLES_TABLE);
                    EndRule(context, RuleType::EXAMPLES);
                    EndRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::EXAMPLES_TABLE);
                    EndRule(context, RuleType::EXAMPLES);
                    EndRule(context, RuleType::EXAMPLES_DEFINITION);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES_TABLE);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES_TABLE);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES_TABLE);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES_TABLE);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 21 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0";
            std::string expectedTokens = "#EOF, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 21;
        }

        // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0
        std::size_t MatchTokenAt22(Token& token, context_type& context)
        {
            if (MatchTagLine(context, token))
            {
                Build(context, token);
                return 22;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::TAGS);
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

            std::string stateComment = "State: 22 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0";
            std::string expectedTokens = "#TagLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 22;
        }

        // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>#RuleLine:0
        std::size_t MatchTokenAt23(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::RULE_HEADER);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
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
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 24;
            }
            if (MatchBackgroundLine(context, token))
            {
                EndRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::BACKGROUND);
                Build(context, token);
                return 25;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::RULE_HEADER);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::RULE_HEADER);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::RULE_HEADER);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 24;
            }

            std::string stateComment = "State: 23 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>#RuleLine:0";
            std::string expectedTokens = "#EOF, #Empty, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 23;
        }

        // GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt24(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::RULE_HEADER);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::BACKGROUND);
                Build(context, token);
                return 25;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DESCRIPTION);
                    EndRule(context, RuleType::RULE_HEADER);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::RULE_HEADER);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::RULE_HEADER);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 24;
            }

            std::string stateComment = "State: 24 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expectedTokens = "#EOF, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 24;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0
        std::size_t MatchTokenAt25(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
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
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 26;
            }
            if (MatchStepLine(context, token))
            {
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 27;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::BACKGROUND);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 26;
            }

            std::string stateComment = "State: 25 - GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0";
            std::string expectedTokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 25;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt26(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DESCRIPTION);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 27;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DESCRIPTION);
                    EndRule(context, RuleType::BACKGROUND);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 26;
            }

            std::string stateComment = "State: 26 - GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expectedTokens = "#EOF, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 26;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0
        std::size_t MatchTokenAt27(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                StartRule(context, RuleType::DATA_TABLE);
                Build(context, token);
                return 28;
            }
            if (MatchDocStringSeparator(context, token))
            {
                StartRule(context, RuleType::DOC_STRING);
                Build(context, token);
                return 46;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 27;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::BACKGROUND);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 27 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0";
            std::string expectedTokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 27;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt28(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DATA_TABLE);
                StartRule(context, RuleType::DOC_STRING);
                Build(context, token);
                return 29;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 27;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DATA_TABLE);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::BACKGROUND);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 28 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0";
            std::string expectedTokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 28;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt29(Token& token, context_type& context)
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

            std::string stateComment = "State: 29 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0";
            std::string expectedTokens = "#DocStringSeparator, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 29;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt30(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
                Build(context, token);
                return 42;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 27;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DOC_STRING);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::BACKGROUND);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 30 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0";
            std::string expectedTokens = "#EOF, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 30;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0
        std::size_t MatchTokenAt31(Token& token, context_type& context)
        {
            if (MatchTagLine(context, token))
            {
                Build(context, token);
                return 31;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::TAGS);
                StartRule(context, RuleType::SCENARIO);
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

            std::string stateComment = "State: 31 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0";
            std::string expectedTokens = "#TagLine, #ScenarioLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 31;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
        std::size_t MatchTokenAt32(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
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
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 33;
            }
            if (MatchStepLine(context, token))
            {
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 34;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 33;
            }

            std::string stateComment = "State: 32 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0";
            std::string expectedTokens = "#EOF, #Empty, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 32;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt33(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DESCRIPTION);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 34;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::DESCRIPTION);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DESCRIPTION);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 33;
            }

            std::string stateComment = "State: 33 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expectedTokens = "#EOF, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 33;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
        std::size_t MatchTokenAt34(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                StartRule(context, RuleType::DATA_TABLE);
                Build(context, token);
                return 35;
            }
            if (MatchDocStringSeparator(context, token))
            {
                StartRule(context, RuleType::DOC_STRING);
                Build(context, token);
                return 43;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 34;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::STEP);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 34 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0";
            std::string expectedTokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 34;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt35(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DATA_TABLE);
                StartRule(context, RuleType::DOC_STRING);
                Build(context, token);
                return 36;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 34;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::DATA_TABLE);
                    EndRule(context, RuleType::STEP);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DATA_TABLE);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 35 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:0>DataTable:0>#TableRow:0";
            std::string expectedTokens = "#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 35;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt36(Token& token, context_type& context)
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

            std::string stateComment =
                "State: 36 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:0>#DocStringSeparator:0";
            std::string expectedTokens = "#DocStringSeparator, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 36;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt37(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
                Build(context, token);
                return 42;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 34;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::DOC_STRING);
                    EndRule(context, RuleType::STEP);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DOC_STRING);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment =
                "State: 37 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTableAndMaybeDocString:1>DocString:2>#DocStringSeparator:0";
            std::string expectedTokens = "#EOF, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 37;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
        std::size_t MatchTokenAt38(Token& token, context_type& context)
        {
            if (MatchTagLine(context, token))
            {
                Build(context, token);
                return 38;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::TAGS);
                StartRule(context, RuleType::EXAMPLES);
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

            std::string stateComment = "State: 38 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0";
            std::string expectedTokens = "#TagLine, #ExamplesLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 38;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
        std::size_t MatchTokenAt39(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
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
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 40;
            }
            if (MatchTableRow(context, token))
            {
                StartRule(context, RuleType::EXAMPLES_TABLE);
                Build(context, token);
                return 41;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::EXAMPLES);
                    EndRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::EXAMPLES);
                    EndRule(context, RuleType::EXAMPLES_DEFINITION);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                StartRule(context, RuleType::DESCRIPTION);
                Build(context, token);
                return 40;
            }

            std::string stateComment = "State: 39 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0";
            std::string expectedTokens = "#EOF, #Empty, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 39;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0
        std::size_t MatchTokenAt40(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DESCRIPTION);
                StartRule(context, RuleType::EXAMPLES_TABLE);
                Build(context, token);
                return 41;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::DESCRIPTION);
                    EndRule(context, RuleType::EXAMPLES);
                    EndRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DESCRIPTION);
                    EndRule(context, RuleType::EXAMPLES);
                    EndRule(context, RuleType::EXAMPLES_DEFINITION);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DESCRIPTION);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                Build(context, token);
                return 23;
            }
            if (MatchOther(context, token))
            {
                Build(context, token);
                return 40;
            }

            std::string stateComment =
                "State: 40 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>__alt1:0>#Other:0";
            std::string expectedTokens = "#EOF, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 40;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
        std::size_t MatchTokenAt41(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::EXAMPLES_TABLE);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
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
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::EXAMPLES_TABLE);
                    EndRule(context, RuleType::EXAMPLES);
                    EndRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::EXAMPLES_TABLE);
                    EndRule(context, RuleType::EXAMPLES);
                    EndRule(context, RuleType::EXAMPLES_DEFINITION);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES_TABLE);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES_TABLE);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES_TABLE);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::EXAMPLES_TABLE);
                EndRule(context, RuleType::EXAMPLES);
                EndRule(context, RuleType::EXAMPLES_DEFINITION);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 41 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0";
            std::string expectedTokens = "#EOF, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 41;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt43(Token& token, context_type& context)
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

            std::string stateComment =
                "State: 43 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0";
            std::string expectedTokens = "#DocStringSeparator, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 43;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt44(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                StartRule(context, RuleType::DATA_TABLE);
                Build(context, token);
                return 45;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 34;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::DOC_STRING);
                    EndRule(context, RuleType::STEP);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DOC_STRING);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment =
                "State: 44 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0";
            std::string expectedTokens = "#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 44;
        }

        // GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt45(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 34;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::DATA_TABLE);
                    EndRule(context, RuleType::STEP);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 38;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DATA_TABLE);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 39;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 45 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0";
            std::string expectedTokens = "#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 45;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt46(Token& token, context_type& context)
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

            std::string stateComment = "State: 46 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0";
            std::string expectedTokens = "#DocStringSeparator, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 46;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt47(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                StartRule(context, RuleType::DATA_TABLE);
                Build(context, token);
                return 48;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 27;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DOC_STRING);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::BACKGROUND);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 47 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0";
            std::string expectedTokens = "#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 47;
        }

        // GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt48(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 27;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DATA_TABLE);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::BACKGROUND);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 31;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 32;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 48 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0";
            std::string expectedTokens = "#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 48;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt49(Token& token, context_type& context)
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

            std::string stateComment =
                "State: 49 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0";
            std::string expectedTokens = "#DocStringSeparator, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 49;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt50(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::FEATURE);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                StartRule(context, RuleType::DATA_TABLE);
                Build(context, token);
                return 51;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 14;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::DOC_STRING);
                    EndRule(context, RuleType::STEP);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DOC_STRING);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment =
                "State: 50 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0";
            std::string expectedTokens = "#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 50;
        }

        // GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt51(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 14;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead1(context, token))
                {
                    EndRule(context, RuleType::DATA_TABLE);
                    EndRule(context, RuleType::STEP);
                    StartRule(context, RuleType::EXAMPLES_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 18;
                }
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DATA_TABLE);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::SCENARIO);
                    EndRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchExamplesLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::EXAMPLES_DEFINITION);
                StartRule(context, RuleType::EXAMPLES);
                Build(context, token);
                return 19;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::SCENARIO);
                EndRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 51 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0";
            std::string expectedTokens = "#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 51;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0
        std::size_t MatchTokenAt52(Token& token, context_type& context)
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

            std::string stateComment = "State: 52 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:0>#DocStringSeparator:0";
            std::string expectedTokens = "#DocStringSeparator, #Other";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 52;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0
        std::size_t MatchTokenAt53(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::FEATURE);
                Build(context, token);
                return 42;
            }
            if (MatchTableRow(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                StartRule(context, RuleType::DATA_TABLE);
                Build(context, token);
                return 54;
            }
            if (MatchStepLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 7;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DOC_STRING);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::BACKGROUND);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DOC_STRING);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 53 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:0>DocString:2>#DocStringSeparator:0";
            std::string expectedTokens = "#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 53;
        }

        // GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0
        std::size_t MatchTokenAt54(Token& token, context_type& context)
        {
            if (MatchEOF(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                EndRule(context, RuleType::FEATURE);
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
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                StartRule(context, RuleType::STEP);
                Build(context, token);
                return 7;
            }
            if (MatchTagLine(context, token))
            {
                if (Lookahead0(context, token))
                {
                    EndRule(context, RuleType::DATA_TABLE);
                    EndRule(context, RuleType::STEP);
                    EndRule(context, RuleType::BACKGROUND);
                    StartRule(context, RuleType::SCENARIO_DEFINITION);
                    StartRule(context, RuleType::TAGS);
                    Build(context, token);
                    return 11;
                }
            }
            if (MatchTagLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
                StartRule(context, RuleType::TAGS);
                Build(context, token);
                return 22;
            }
            if (MatchScenarioLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::SCENARIO_DEFINITION);
                StartRule(context, RuleType::SCENARIO);
                Build(context, token);
                return 12;
            }
            if (MatchRuleLine(context, token))
            {
                EndRule(context, RuleType::DATA_TABLE);
                EndRule(context, RuleType::STEP);
                EndRule(context, RuleType::BACKGROUND);
                StartRule(context, RuleType::RULE);
                StartRule(context, RuleType::RULE_HEADER);
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

            std::string stateComment = "State: 54 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocStringAndMaybeDataTable:1>DataTable:0>#TableRow:0";
            std::string expectedTokens = "#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

            auto errorPointer = token.IsEof() ? NewParserError<UnexpectedEof>(token, expectedTokens, stateComment) : NewParserError<UnexpectedToken>(token, expectedTokens, stateComment);

            if (context.stopAtFirstError)
            {
                throw *errorPointer;
            }

            context.AddError(std::move(errorPointer));

            return 54;
        }

        std::size_t MatchToken(std::size_t state, Token& token, context_type& context)
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
