// This file is generated. Do not edit! Edit gherkin-cpp-parser.razor instead.
#include <gherkin/parser.hpp>
#include <gherkin/parser_context.hpp>
#include <gherkin/token_scanner.hpp>
#include <gherkin/rule_type.hpp>

namespace gherkin {

parser::parser(const parser_info& pi)
: pi_{pi}
{}

std::size_t
parser::parse(const file& file)
{
    ast_builder_.reset();
    token_scanner_.reset();
    token_matcher_.reset();

    parser_context context{
        .token_scanner = token_scanner_,
        .token_matcher = token_matcher_
    };

    start_rule(context, rule_type::gherkin_document);

    std::size_t state = 0;

    while (true) {
        auto token = read_token(context);
        state = match_token(state, token, context);

        if (token.is_eof()) {
            break;
        }
    }

    end_rule(context, rule_type::gherkin_document);

    if (context.has_errors()) {
        // TODO: thow coumpound error
    }

    return get_result();
}

std::size_t
parser::match_token(std::size_t state, token& token, parser_context& context)
{
    return state;
}

token
parser::read_token(parser_context& context)
{
    token t;

    if (context.has_token()) {
        t = context.pop_token();
    } else {
        t = context.token_scanner.read();
    }

    return t;
}

std::size_t
parser::get_result() const
{ return 0; }

namespace detail {

void
handle_ast_error(parser_context& context)
{}


bool
match_e_o_f(parser_context& context, token& token)
{
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_e_o_f
        );
}

bool
match_empty(parser_context& context, token& token)
{
    if (token.eof()) {
        return false;
    }
    
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_empty
        );
}

bool
match_comment(parser_context& context, token& token)
{
    if (token.eof()) {
        return false;
    }
    
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_comment
        );
}

bool
match_tag_line(parser_context& context, token& token)
{
    if (token.eof()) {
        return false;
    }
    
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_tag_line
        );
}

bool
match_feature_line(parser_context& context, token& token)
{
    if (token.eof()) {
        return false;
    }
    
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_feature_line
        );
}

bool
match_rule_line(parser_context& context, token& token)
{
    if (token.eof()) {
        return false;
    }
    
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_rule_line
        );
}

bool
match_background_line(parser_context& context, token& token)
{
    if (token.eof()) {
        return false;
    }
    
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_background_line
        );
}

bool
match_scenario_line(parser_context& context, token& token)
{
    if (token.eof()) {
        return false;
    }
    
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_scenario_line
        );
}

bool
match_examples_line(parser_context& context, token& token)
{
    if (token.eof()) {
        return false;
    }
    
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_examples_line
        );
}

bool
match_step_line(parser_context& context, token& token)
{
    if (token.eof()) {
        return false;
    }
    
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_step_line
        );
}

bool
match_doc_string_separator(parser_context& context, token& token)
{
    if (token.eof()) {
        return false;
    }
    
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_doc_string_separator
        );
}

bool
match_table_row(parser_context& context, token& token)
{
    if (token.eof()) {
        return false;
    }
    
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_table_row
        );
}

bool
match_language(parser_context& context, token& token)
{
    if (token.eof()) {
        return false;
    }
    
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_language
        );
}

bool
match_other(parser_context& context, token& token)
{
    if (token.eof()) {
        return false;
    }
    
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_other
        );
}

parser::match_token(parser_context& context, token& token)
{
    state_map = {
        0: self.match_token_at_0,
        1: self.match_token_at_1,
        2: self.match_token_at_2,
        3: self.match_token_at_3,
        4: self.match_token_at_4,
        5: self.match_token_at_5,
        6: self.match_token_at_6,
        7: self.match_token_at_7,
        8: self.match_token_at_8,
        9: self.match_token_at_9,
        10: self.match_token_at_10,
        11: self.match_token_at_11,
        12: self.match_token_at_12,
        13: self.match_token_at_13,
        14: self.match_token_at_14,
        15: self.match_token_at_15,
        16: self.match_token_at_16,
        17: self.match_token_at_17,
        18: self.match_token_at_18,
        19: self.match_token_at_19,
        20: self.match_token_at_20,
        21: self.match_token_at_21,
        22: self.match_token_at_22,
        23: self.match_token_at_23,
        24: self.match_token_at_24,
        25: self.match_token_at_25,
        26: self.match_token_at_26,
        27: self.match_token_at_27,
        28: self.match_token_at_28,
        29: self.match_token_at_29,
        30: self.match_token_at_30,
        31: self.match_token_at_31,
        32: self.match_token_at_32,
        33: self.match_token_at_33,
        34: self.match_token_at_34,
        35: self.match_token_at_35,
        36: self.match_token_at_36,
        37: self.match_token_at_37,
        38: self.match_token_at_38,
        39: self.match_token_at_39,
        40: self.match_token_at_40,
        41: self.match_token_at_41,
        43: self.match_token_at_43,
        44: self.match_token_at_44,
        45: self.match_token_at_45,
        46: self.match_token_at_46,
        47: self.match_token_at_47,
        48: self.match_token_at_48,
        49: self.match_token_at_49,
        50: self.match_token_at_50,
    }
    if state in state_map:
        return state_map[state](token, context)
    else:
        raise RuntimeError("Unknown state: " + str(state))
}


// Start
std::size_t
match_token_at_0(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Language(context, token)) {
        start_rule(context, Rule_Feature);
        start_rule(context, Rule_FeatureHeader);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        start_rule(context, Rule_Feature);
        start_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
        return transition.TargetState;
    }
    if (match_FeatureLine(context, token)) {
        start_rule(context, Rule_Feature);
        start_rule(context, Rule_FeatureHeader);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }


    /* "State: 0 - Start" */
    std::string expected_tokens = L"#EOF, #Language, #TagLine, #FeatureLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 0;}

// GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0
std::size_t
match_token_at_1(parser& parser, token& token, parser_context& context)
{
    if (match_TagLine(context, token)) {
        start_rule(context, Rule_Tags);
        build(context, token);
        return transition.TargetState;
    }
    if (match_FeatureLine(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }


    /* "State: 1 - GherkinDocument:0>Feature:0>FeatureHeader:0>#Language:0" */
    std::string expected_tokens = L"#TagLine, #FeatureLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 1;}

// GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0
std::size_t
match_token_at_2(parser& parser, token& token, parser_context& context)
{
    if (match_TagLine(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_FeatureLine(context, token)) {
        end_rule(context, Rule_Tags);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }


    /* "State: 2 - GherkinDocument:0>Feature:0>FeatureHeader:1>Tags:0>#TagLine:0" */
    std::string expected_tokens = L"#TagLine, #FeatureLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 2;}

// GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0
std::size_t
match_token_at_3(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_FeatureHeader);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_BackgroundLine(context, token)) {
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_Background);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_FeatureHeader);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_FeatureHeader);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_FeatureHeader);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_FeatureHeader);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            start_rule(context, Rule_Description);
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 3 - GherkinDocument:0>Feature:0>FeatureHeader:2>#FeatureLine:0" */
    std::string expected_tokens = L"#EOF, #Empty, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 3;}

// GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>#Other:0
std::size_t
match_token_at_4(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Description);
        end_rule(context, Rule_FeatureHeader);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        end_rule(context, Rule_Description);
        build(context, token);
        return transition.TargetState;
    }
    if (match_BackgroundLine(context, token)) {
        end_rule(context, Rule_Description);
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_Background);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_FeatureHeader);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_FeatureHeader);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_FeatureHeader);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_FeatureHeader);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 4 - GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:1>Description:0>#Other:0" */
    std::string expected_tokens = L"#EOF, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 4;}

// GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:2>#Comment:0
std::size_t
match_token_at_5(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_FeatureHeader);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_BackgroundLine(context, token)) {
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_Background);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_FeatureHeader);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_FeatureHeader);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_FeatureHeader);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_FeatureHeader);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 5 - GherkinDocument:0>Feature:0>FeatureHeader:3>DescriptionHelper:2>#Comment:0" */
    std::string expected_tokens = L"#EOF, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 5;}

// GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0
std::size_t
match_token_at_6(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Background);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Background);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            start_rule(context, Rule_Description);
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 6 - GherkinDocument:0>Feature:1>Background:0>#BackgroundLine:0" */
    std::string expected_tokens = L"#EOF, #Empty, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 6;}

// GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>#Other:0
std::size_t
match_token_at_7(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        end_rule(context, Rule_Description);
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_Description);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 7 - GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:1>Description:0>#Other:0" */
    std::string expected_tokens = L"#EOF, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 7;}

// GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:2>#Comment:0
std::size_t
match_token_at_8(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Background);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Background);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 8 - GherkinDocument:0>Feature:1>Background:1>DescriptionHelper:2>#Comment:0" */
    std::string expected_tokens = L"#EOF, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 8;}

// GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0
std::size_t
match_token_at_9(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        start_rule(context, Rule_DataTable);
        build(context, token);
        return transition.TargetState;
    }
    if (match_DocStringSeparator(context, token)) {
        start_rule(context, Rule_DocString);
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Comment(context, token)) {
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 9 - GherkinDocument:0>Feature:1>Background:2>Step:0>#StepLine:0" */
    std::string expected_tokens = L"#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 9;}

// GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
std::size_t
match_token_at_10(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Comment(context, token)) {
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 10 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0" */
    std::string expected_tokens = L"#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 10;}

// GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0
std::size_t
match_token_at_11(parser& parser, token& token, parser_context& context)
{
    if (match_TagLine(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
        end_rule(context, Rule_Tags);
        start_rule(context, Rule_Scenario);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }


    /* "State: 11 - GherkinDocument:0>Feature:2>ScenarioDefinition:0>Tags:0>#TagLine:0" */
    std::string expected_tokens = L"#TagLine, #ScenarioLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 11;}

// GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
std::size_t
match_token_at_12(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            start_rule(context, Rule_Description);
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 12 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0" */
    std::string expected_tokens = L"#EOF, #Empty, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 12;}

// GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0
std::size_t
match_token_at_13(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        end_rule(context, Rule_Description);
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_Description);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_Description);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_Description);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 13 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0" */
    std::string expected_tokens = L"#EOF, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 13;}

// GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0
std::size_t
match_token_at_14(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 14 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0" */
    std::string expected_tokens = L"#EOF, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 14;}

// GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
std::size_t
match_token_at_15(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        start_rule(context, Rule_DataTable);
        build(context, token);
        return transition.TargetState;
    }
    if (match_DocStringSeparator(context, token)) {
        start_rule(context, Rule_DocString);
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_Step);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_Step);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Comment(context, token)) {
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 15 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0" */
    std::string expected_tokens = L"#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 15;}

// GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
std::size_t
match_token_at_16(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Comment(context, token)) {
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 16 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0" */
    std::string expected_tokens = L"#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 16;}

// GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
std::size_t
match_token_at_17(parser& parser, token& token, parser_context& context)
{
    if (match_TagLine(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
        end_rule(context, Rule_Tags);
        start_rule(context, Rule_Examples);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }


    /* "State: 17 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0" */
    std::string expected_tokens = L"#TagLine, #ExamplesLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 17;}

// GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
std::size_t
match_token_at_18(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        start_rule(context, Rule_ExamplesTable);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            start_rule(context, Rule_Description);
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 18 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0" */
    std::string expected_tokens = L"#EOF, #Empty, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 18;}

// GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0
std::size_t
match_token_at_19(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        end_rule(context, Rule_Description);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        end_rule(context, Rule_Description);
        start_rule(context, Rule_ExamplesTable);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 19 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0" */
    std::string expected_tokens = L"#EOF, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 19;}

// GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0
std::size_t
match_token_at_20(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        start_rule(context, Rule_ExamplesTable);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 20 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0" */
    std::string expected_tokens = L"#EOF, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 20;}

// GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
std::size_t
match_token_at_21(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_ExamplesTable);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_ExamplesTable);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_ExamplesTable);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_ExamplesTable);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_ExamplesTable);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_ExamplesTable);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Comment(context, token)) {
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 21 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0" */
    std::string expected_tokens = L"#EOF, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 21;}

// GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0
std::size_t
match_token_at_22(parser& parser, token& token, parser_context& context)
{
    if (match_TagLine(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
        end_rule(context, Rule_Tags);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }


    /* "State: 22 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:0>Tags:0>#TagLine:0" */
    std::string expected_tokens = L"#TagLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 22;}

// GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>#RuleLine:0
std::size_t
match_token_at_23(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_RuleHeader);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_BackgroundLine(context, token)) {
        end_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Background);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_RuleHeader);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_RuleHeader);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            start_rule(context, Rule_Description);
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 23 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:1>#RuleLine:0" */
    std::string expected_tokens = L"#EOF, #Empty, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 23;}

// GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:1>Description:0>#Other:0
std::size_t
match_token_at_24(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Description);
        end_rule(context, Rule_RuleHeader);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        end_rule(context, Rule_Description);
        build(context, token);
        return transition.TargetState;
    }
    if (match_BackgroundLine(context, token)) {
        end_rule(context, Rule_Description);
        end_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Background);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_RuleHeader);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_RuleHeader);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 24 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:1>Description:0>#Other:0" */
    std::string expected_tokens = L"#EOF, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 24;}

// GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:2>#Comment:0
std::size_t
match_token_at_25(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_RuleHeader);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_BackgroundLine(context, token)) {
        end_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Background);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_RuleHeader);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_RuleHeader);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 25 - GherkinDocument:0>Feature:3>Rule:0>RuleHeader:2>DescriptionHelper:2>#Comment:0" */
    std::string expected_tokens = L"#EOF, #Comment, #BackgroundLine, #TagLine, #ScenarioLine, #RuleLine, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 25;}

// GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0
std::size_t
match_token_at_26(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Background);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Background);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            start_rule(context, Rule_Description);
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 26 - GherkinDocument:0>Feature:3>Rule:1>Background:0>#BackgroundLine:0" */
    std::string expected_tokens = L"#EOF, #Empty, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 26;}

// GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>#Other:0
std::size_t
match_token_at_27(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        end_rule(context, Rule_Description);
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_Description);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Background);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Background);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 27 - GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:1>Description:0>#Other:0" */
    std::string expected_tokens = L"#EOF, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 27;}

// GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:2>#Comment:0
std::size_t
match_token_at_28(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Background);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Background);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 28 - GherkinDocument:0>Feature:3>Rule:1>Background:1>DescriptionHelper:2>#Comment:0" */
    std::string expected_tokens = L"#EOF, #Comment, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 28;}

// GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0
std::size_t
match_token_at_29(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        start_rule(context, Rule_DataTable);
        build(context, token);
        return transition.TargetState;
    }
    if (match_DocStringSeparator(context, token)) {
        start_rule(context, Rule_DocString);
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Comment(context, token)) {
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 29 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:0>#StepLine:0" */
    std::string expected_tokens = L"#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 29;}

// GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
std::size_t
match_token_at_30(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Comment(context, token)) {
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 30 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0" */
    std::string expected_tokens = L"#EOF, #TableRow, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 30;}

// GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0
std::size_t
match_token_at_31(parser& parser, token& token, parser_context& context)
{
    if (match_TagLine(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
        end_rule(context, Rule_Tags);
        start_rule(context, Rule_Scenario);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }


    /* "State: 31 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:0>Tags:0>#TagLine:0" */
    std::string expected_tokens = L"#TagLine, #ScenarioLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 31;}

// GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0
std::size_t
match_token_at_32(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            start_rule(context, Rule_Description);
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 32 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:0>#ScenarioLine:0" */
    std::string expected_tokens = L"#EOF, #Empty, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 32;}

// GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0
std::size_t
match_token_at_33(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        end_rule(context, Rule_Description);
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_Description);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_Description);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_Description);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 33 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:1>Description:0>#Other:0" */
    std::string expected_tokens = L"#EOF, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 33;}

// GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0
std::size_t
match_token_at_34(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 34 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:1>DescriptionHelper:2>#Comment:0" */
    std::string expected_tokens = L"#EOF, #Comment, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 34;}

// GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0
std::size_t
match_token_at_35(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        start_rule(context, Rule_DataTable);
        build(context, token);
        return transition.TargetState;
    }
    if (match_DocStringSeparator(context, token)) {
        start_rule(context, Rule_DocString);
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_Step);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_Step);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Comment(context, token)) {
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 35 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:0>#StepLine:0" */
    std::string expected_tokens = L"#EOF, #TableRow, #DocStringSeparator, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 35;}

// GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0
std::size_t
match_token_at_36(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_DataTable);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Comment(context, token)) {
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 36 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:0>DataTable:0>#TableRow:0" */
    std::string expected_tokens = L"#EOF, #TableRow, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 36;}

// GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0
std::size_t
match_token_at_37(parser& parser, token& token, parser_context& context)
{
    if (match_TagLine(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
        end_rule(context, Rule_Tags);
        start_rule(context, Rule_Examples);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }


    /* "State: 37 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:0>Tags:0>#TagLine:0" */
    std::string expected_tokens = L"#TagLine, #ExamplesLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 37;}

// GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0
std::size_t
match_token_at_38(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Empty(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        start_rule(context, Rule_ExamplesTable);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            start_rule(context, Rule_Description);
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 38 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:0>#ExamplesLine:0" */
    std::string expected_tokens = L"#EOF, #Empty, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 38;}

// GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0
std::size_t
match_token_at_39(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        end_rule(context, Rule_Description);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        end_rule(context, Rule_Description);
        start_rule(context, Rule_ExamplesTable);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Description);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Other(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 39 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:1>Description:0>#Other:0" */
    std::string expected_tokens = L"#EOF, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 39;}

// GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0
std::size_t
match_token_at_40(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_Comment(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        start_rule(context, Rule_ExamplesTable);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 40 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:1>DescriptionHelper:2>#Comment:0" */
    std::string expected_tokens = L"#EOF, #Comment, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 40;}

// GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0
std::size_t
match_token_at_41(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TableRow(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_ExamplesTable);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_ExamplesTable);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_ExamplesTable);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_ExamplesTable);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_ExamplesTable);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_ExamplesTable);
            end_rule(context, Rule_Examples);
            end_rule(context, Rule_ExamplesDefinition);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Comment(context, token)) {
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 41 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:3>ExamplesDefinition:1>Examples:2>ExamplesTable:0>#TableRow:0" */
    std::string expected_tokens = L"#EOF, #TableRow, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 41;}

// GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
std::size_t
match_token_at_43(parser& parser, token& token, parser_context& context)
{
    if (match_DocStringSeparator(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Other(context, token)) {
        build(context, token);
        return transition.TargetState;
    }


    /* "State: 43 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0" */
    std::string expected_tokens = L"#DocStringSeparator, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 43;}

// GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
std::size_t
match_token_at_44(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Comment(context, token)) {
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 44 - GherkinDocument:0>Feature:3>Rule:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0" */
    std::string expected_tokens = L"#EOF, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 44;}

// GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
std::size_t
match_token_at_45(parser& parser, token& token, parser_context& context)
{
    if (match_DocStringSeparator(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Other(context, token)) {
        build(context, token);
        return transition.TargetState;
    }


    /* "State: 45 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0" */
    std::string expected_tokens = L"#DocStringSeparator, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 45;}

// GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
std::size_t
match_token_at_46(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            end_rule(context, Rule_Rule);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Comment(context, token)) {
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 46 - GherkinDocument:0>Feature:3>Rule:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0" */
    std::string expected_tokens = L"#EOF, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 46;}

// GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
std::size_t
match_token_at_47(parser& parser, token& token, parser_context& context)
{
    if (match_DocStringSeparator(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Other(context, token)) {
        build(context, token);
        return transition.TargetState;
    }


    /* "State: 47 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0" */
    std::string expected_tokens = L"#DocStringSeparator, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 47;}

// GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
std::size_t
match_token_at_48(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_1(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ExamplesLine(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            start_rule(context, Rule_ExamplesDefinition);
            start_rule(context, Rule_Examples);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Scenario);
            end_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Comment(context, token)) {
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 48 - GherkinDocument:0>Feature:2>ScenarioDefinition:1>Scenario:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0" */
    std::string expected_tokens = L"#EOF, #StepLine, #TagLine, #ExamplesLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 48;}

// GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0
std::size_t
match_token_at_49(parser& parser, token& token, parser_context& context)
{
    if (match_DocStringSeparator(context, token)) {
        build(context, token);
        return transition.TargetState;
    }
    if (match_Other(context, token)) {
        build(context, token);
        return transition.TargetState;
    }


    /* "State: 49 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:0>#DocStringSeparator:0" */
    std::string expected_tokens = L"#DocStringSeparator, #Other";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 49;}

// GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0
std::size_t
match_token_at_50(parser& parser, token& token, parser_context& context)
{
    if (match_EOF(context, token)) {
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Feature);
        build(context, token);
        return transition.TargetState;
    }
    if (match_StepLine(context, token)) {
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
        return transition.TargetState;
    }
    if (match_TagLine(context, token)) {
        if (lookahead_0(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
        }
    }
    if (match_TagLine(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            start_rule(context, Rule_Tags);
            build(context, token);
            return transition.TargetState;
    }
    if (match_ScenarioLine(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_ScenarioDefinition);
            start_rule(context, Rule_Scenario);
            build(context, token);
            return transition.TargetState;
    }
    if (match_RuleLine(context, token)) {
            end_rule(context, Rule_DocString);
            end_rule(context, Rule_Step);
            end_rule(context, Rule_Background);
            start_rule(context, Rule_Rule);
            start_rule(context, Rule_RuleHeader);
            build(context, token);
            return transition.TargetState;
    }
    if (match_Comment(context, token)) {
            build(context, token);
            return transition.TargetState;
    }
    if (match_Empty(context, token)) {
            build(context, token);
            return transition.TargetState;
    }


    /* "State: 50 - GherkinDocument:0>Feature:1>Background:2>Step:1>StepArg:0>__alt0:1>DocString:2>#DocStringSeparator:0" */
    std::string expected_tokens = L"#EOF, #StepLine, #TagLine, #ScenarioLine, #RuleLine, #Comment, #Empty";

    auto error =
        token.is_eof()
        ? error_type::unexpected_eof
        : error_type::unexpected_token
        ;

    if (stop_at_first_error()) {
        throw_error(error, token, expected_tokens);
    }

    add_error(error, token, expected_tokens);

    return 50;}


bool
lookahead_0(parser_context& context, token& current_token)
{
    current_token.detach();
    token token;
    token_queue queue;
    bool match = false;

    while (true) {
        token = context.read_token();
        token.detach()
        queue.push_back(token);

        if (smatch_ScenarioLine(context, token) || false) {
            match = true;
            break;
        }

        if not (match_Empty(context, token) || match_Comment(context, token) || match_TagLine(context, token) || false) {
            break;
        }

        context.push_tokens(queue);

        return match;
}
bool
lookahead_1(parser_context& context, token& current_token)
{
    current_token.detach();
    token token;
    token_queue queue;
    bool match = false;

    while (true) {
        token = context.read_token();
        token.detach()
        queue.push_back(token);

        if (smatch_ExamplesLine(context, token) || false) {
            match = true;
            break;
        }

        if not (match_Empty(context, token) || match_Comment(context, token) || match_TagLine(context, token) || false) {
            break;
        }

        context.push_tokens(queue);

        return match;
}
void
handle_ast_error(parser_context& context, token& token, match_function action)
{ handle_external_error(context, true, token, action); }

bool
handle_external_error(
    parser_context& context,
    bool default_value,
    token& token,
    match_function action
)
{
    if (context.stop_at_first_error) {
        return action(token);
    }

    try {
        return action(token);
    } catch (const std::exception& e) {
        add_error(context, e);
    }

    return default_value;
}

} // namespace detail
