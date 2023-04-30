// This file is generated. Do not edit! Edit gherkin-cpp-parser.razor instead.
#include <gherkin/parser.hpp>
#include <gherkin/parser_context.hpp>
#include <gherkin/token_scanner.hpp>
#include <gherkin/rule_type.hpp>

namespace gherkin {

parser::parser(const parser_info& pi)
: pi_{pi}
{}

int
parser::parse(const file& file)
{
    ast_builder_.reset();
    token_scanner_.reset();
    token_matcher_.reset();

    parser_context context{
        .token_scanner = token_scanner_,
        .token_matcher = token_matcher_
    };

    start_rule(context, rule_type::GherkinDocument);

    std::size_t state = 0;

    while (true) {
        auto token = read_token(context);
        state = match_token(state, token, context);

        if (token.is_eof()) {
            break;
        }
    }

    end_rule(context, rule_type::GherkinDocument);

    if (context.has_errors()) {
        // TODO: thow coumpound error
    }

    return get_result();
}

void
parser::match_token(parser_context& context, token& token)
{

}

token
parser::read_token(parser_context& context)
{
    token t;

    if (context.has_token()) {
        t = context.pop_token());
    } else {
        t = context.token_scanner.read();
    }

    return t;
}

void
parser::handle_ast_error(parser_context& context)
{}


parser::match_EOF(parser_context& context, token& token)
{
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_EOF
        );
}

parser::match_Empty(parser_context& context, token& token)
{
    if token.eof():
        return False
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_Empty
        );
}

parser::match_Comment(parser_context& context, token& token)
{
    if token.eof():
        return False
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_Comment
        );
}

parser::match_TagLine(parser_context& context, token& token)
{
    if token.eof():
        return False
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_TagLine
        );
}

parser::match_FeatureLine(parser_context& context, token& token)
{
    if token.eof():
        return False
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_FeatureLine
        );
}

parser::match_RuleLine(parser_context& context, token& token)
{
    if token.eof():
        return False
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_RuleLine
        );
}

parser::match_BackgroundLine(parser_context& context, token& token)
{
    if token.eof():
        return False
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_BackgroundLine
        );
}

parser::match_ScenarioLine(parser_context& context, token& token)
{
    if token.eof():
        return False
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_ScenarioLine
        );
}

parser::match_ExamplesLine(parser_context& context, token& token)
{
    if token.eof():
        return False
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_ExamplesLine
        );
}

parser::match_StepLine(parser_context& context, token& token)
{
    if token.eof():
        return False
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_StepLine
        );
}

parser::match_DocStringSeparator(parser_context& context, token& token)
{
    if token.eof():
        return False
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_DocStringSeparator
        );
}

parser::match_TableRow(parser_context& context, token& token)
{
    if token.eof():
        return False
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_TableRow
        );
}

parser::match_Language(parser_context& context, token& token)
{
    if token.eof():
        return False
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_Language
        );
}

parser::match_Other(parser_context& context, token& token)
{
    if token.eof():
        return False
    return
        handle_external_error(
            context,
            false,
            token,
            context.token_matcher.match_Other
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
parser::match_token_at_0(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        build(context, token);
            return 42
    if self.match_Language(context, token):
        start_rule(context, Rule_Feature);
        start_rule(context, Rule_FeatureHeader);
        build(context, token);
            return 1
    if self.match_TagLine(context, token):
        start_rule(context, Rule_Feature);
        start_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 2
    if self.match_FeatureLine(context, token):
        start_rule(context, Rule_Feature);
        start_rule(context, Rule_FeatureHeader);
        build(context, token);
            return 3
    if self.match_Comment(context, token):
        build(context, token);
            return 0
    if self.match_Empty(context, token):
        build(context, token);
            return 0


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
parser::match_token_at_1(token& token, parser_context& context)
{
    if self.match_TagLine(context, token):
        start_rule(context, Rule_Tags);
        build(context, token);
            return 2
    if self.match_FeatureLine(context, token):
        build(context, token);
            return 3
    if self.match_Comment(context, token):
        build(context, token);
            return 1
    if self.match_Empty(context, token):
        build(context, token);
            return 1


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
parser::match_token_at_2(token& token, parser_context& context)
{
    if self.match_TagLine(context, token):
        build(context, token);
            return 2
    if self.match_FeatureLine(context, token):
        end_rule(context, Rule_Tags);
        build(context, token);
            return 3
    if self.match_Comment(context, token):
        build(context, token);
            return 2
    if self.match_Empty(context, token):
        build(context, token);
            return 2


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
parser::match_token_at_3(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_FeatureHeader);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Empty(context, token):
        build(context, token);
            return 3
    if self.match_Comment(context, token):
        build(context, token);
            return 5
    if self.match_BackgroundLine(context, token):
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_Background);
        build(context, token);
            return 6
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        start_rule(context, Rule_Description);
        build(context, token);
            return 4


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
parser::match_token_at_4(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_FeatureHeader);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        end_rule(context, Rule_Description);
        build(context, token);
            return 5
    if self.match_BackgroundLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_Background);
        build(context, token);
            return 6
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        build(context, token);
            return 4


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
parser::match_token_at_5(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_FeatureHeader);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        build(context, token);
            return 5
    if self.match_BackgroundLine(context, token):
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_Background);
        build(context, token);
            return 6
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_FeatureHeader);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Empty(context, token):
        build(context, token);
            return 5


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
parser::match_token_at_6(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Empty(context, token):
        build(context, token);
            return 6
    if self.match_Comment(context, token):
        build(context, token);
            return 8
    if self.match_StepLine(context, token):
        start_rule(context, Rule_Step);
        build(context, token);
            return 9
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Background);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Background);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        start_rule(context, Rule_Description);
        build(context, token);
            return 7


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
parser::match_token_at_7(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        end_rule(context, Rule_Description);
        build(context, token);
            return 8
    if self.match_StepLine(context, token):
        end_rule(context, Rule_Description);
        start_rule(context, Rule_Step);
        build(context, token);
            return 9
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        build(context, token);
            return 7


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
parser::match_token_at_8(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        build(context, token);
            return 8
    if self.match_StepLine(context, token):
        start_rule(context, Rule_Step);
        build(context, token);
            return 9
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Background);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Background);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Empty(context, token):
        build(context, token);
            return 8


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
parser::match_token_at_9(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_TableRow(context, token):
        start_rule(context, Rule_DataTable);
        build(context, token);
            return 10
    if self.match_DocStringSeparator(context, token):
        start_rule(context, Rule_DocString);
        build(context, token);
            return 49
    if self.match_StepLine(context, token):
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
            return 9
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 9
    if self.match_Empty(context, token):
        build(context, token);
            return 9


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
parser::match_token_at_10(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_TableRow(context, token):
        build(context, token);
            return 10
    if self.match_StepLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
            return 9
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 10
    if self.match_Empty(context, token):
        build(context, token);
            return 10


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
parser::match_token_at_11(token& token, parser_context& context)
{
    if self.match_TagLine(context, token):
        build(context, token);
            return 11
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Tags);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_Comment(context, token):
        build(context, token);
            return 11
    if self.match_Empty(context, token):
        build(context, token);
            return 11


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
parser::match_token_at_12(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Empty(context, token):
        build(context, token);
            return 12
    if self.match_Comment(context, token):
        build(context, token);
            return 14
    if self.match_StepLine(context, token):
        start_rule(context, Rule_Step);
        build(context, token);
            return 15
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 17
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 18
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        start_rule(context, Rule_Description);
        build(context, token);
            return 13


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
parser::match_token_at_13(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        end_rule(context, Rule_Description);
        build(context, token);
            return 14
    if self.match_StepLine(context, token):
        end_rule(context, Rule_Description);
        start_rule(context, Rule_Step);
        build(context, token);
            return 15
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_Description);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 17
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_Description);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 18
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        build(context, token);
            return 13


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
parser::match_token_at_14(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        build(context, token);
            return 14
    if self.match_StepLine(context, token):
        start_rule(context, Rule_Step);
        build(context, token);
            return 15
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 17
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 18
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Empty(context, token):
        build(context, token);
            return 14


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
parser::match_token_at_15(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_TableRow(context, token):
        start_rule(context, Rule_DataTable);
        build(context, token);
            return 16
    if self.match_DocStringSeparator(context, token):
        start_rule(context, Rule_DocString);
        build(context, token);
            return 47
    if self.match_StepLine(context, token):
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
            return 15
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_Step);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 17
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_Step);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 18
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 15
    if self.match_Empty(context, token):
        build(context, token);
            return 15


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
parser::match_token_at_16(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_TableRow(context, token):
        build(context, token);
            return 16
    if self.match_StepLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
            return 15
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 17
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 18
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 16
    if self.match_Empty(context, token):
        build(context, token);
            return 16


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
parser::match_token_at_17(token& token, parser_context& context)
{
    if self.match_TagLine(context, token):
        build(context, token);
            return 17
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_Tags);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 18
    if self.match_Comment(context, token):
        build(context, token);
            return 17
    if self.match_Empty(context, token):
        build(context, token);
            return 17


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
parser::match_token_at_18(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Empty(context, token):
        build(context, token);
            return 18
    if self.match_Comment(context, token):
        build(context, token);
            return 20
    if self.match_TableRow(context, token):
        start_rule(context, Rule_ExamplesTable);
        build(context, token);
            return 21
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 17
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 18
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        start_rule(context, Rule_Description);
        build(context, token);
            return 19


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
parser::match_token_at_19(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        end_rule(context, Rule_Description);
        build(context, token);
            return 20
    if self.match_TableRow(context, token):
        end_rule(context, Rule_Description);
        start_rule(context, Rule_ExamplesTable);
        build(context, token);
            return 21
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 17
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 18
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        build(context, token);
            return 19


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
parser::match_token_at_20(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        build(context, token);
            return 20
    if self.match_TableRow(context, token):
        start_rule(context, Rule_ExamplesTable);
        build(context, token);
            return 21
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 17
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 18
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Empty(context, token):
        build(context, token);
            return 20


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
parser::match_token_at_21(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_TableRow(context, token):
        build(context, token);
            return 21
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 17
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 18
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 21
    if self.match_Empty(context, token):
        build(context, token);
            return 21


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
parser::match_token_at_22(token& token, parser_context& context)
{
    if self.match_TagLine(context, token):
        build(context, token);
            return 22
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Tags);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 22
    if self.match_Empty(context, token):
        build(context, token);
            return 22


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
parser::match_token_at_23(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_RuleHeader);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Empty(context, token):
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 25
    if self.match_BackgroundLine(context, token):
        end_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Background);
        build(context, token);
            return 26
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_RuleHeader);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_RuleHeader);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        start_rule(context, Rule_Description);
        build(context, token);
            return 24


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
parser::match_token_at_24(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_RuleHeader);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        end_rule(context, Rule_Description);
        build(context, token);
            return 25
    if self.match_BackgroundLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Background);
        build(context, token);
            return 26
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_RuleHeader);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_RuleHeader);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        build(context, token);
            return 24


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
parser::match_token_at_25(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_RuleHeader);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        build(context, token);
            return 25
    if self.match_BackgroundLine(context, token):
        end_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Background);
        build(context, token);
            return 26
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_RuleHeader);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_RuleHeader);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Empty(context, token):
        build(context, token);
            return 25


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
parser::match_token_at_26(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Empty(context, token):
        build(context, token);
            return 26
    if self.match_Comment(context, token):
        build(context, token);
            return 28
    if self.match_StepLine(context, token):
        start_rule(context, Rule_Step);
        build(context, token);
            return 29
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        start_rule(context, Rule_Description);
        build(context, token);
            return 27


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
parser::match_token_at_27(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        end_rule(context, Rule_Description);
        build(context, token);
            return 28
    if self.match_StepLine(context, token):
        end_rule(context, Rule_Description);
        start_rule(context, Rule_Step);
        build(context, token);
            return 29
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        build(context, token);
            return 27


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
parser::match_token_at_28(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        build(context, token);
            return 28
    if self.match_StepLine(context, token):
        start_rule(context, Rule_Step);
        build(context, token);
            return 29
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Empty(context, token):
        build(context, token);
            return 28


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
parser::match_token_at_29(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_TableRow(context, token):
        start_rule(context, Rule_DataTable);
        build(context, token);
            return 30
    if self.match_DocStringSeparator(context, token):
        start_rule(context, Rule_DocString);
        build(context, token);
            return 45
    if self.match_StepLine(context, token):
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
            return 29
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 29
    if self.match_Empty(context, token):
        build(context, token);
            return 29


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
parser::match_token_at_30(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_TableRow(context, token):
        build(context, token);
            return 30
    if self.match_StepLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
            return 29
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 30
    if self.match_Empty(context, token):
        build(context, token);
            return 30


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
parser::match_token_at_31(token& token, parser_context& context)
{
    if self.match_TagLine(context, token):
        build(context, token);
            return 31
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Tags);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_Comment(context, token):
        build(context, token);
            return 31
    if self.match_Empty(context, token):
        build(context, token);
            return 31


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
parser::match_token_at_32(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Empty(context, token):
        build(context, token);
            return 32
    if self.match_Comment(context, token):
        build(context, token);
            return 34
    if self.match_StepLine(context, token):
        start_rule(context, Rule_Step);
        build(context, token);
            return 35
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 37
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 38
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        start_rule(context, Rule_Description);
        build(context, token);
            return 33


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
parser::match_token_at_33(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        end_rule(context, Rule_Description);
        build(context, token);
            return 34
    if self.match_StepLine(context, token):
        end_rule(context, Rule_Description);
        start_rule(context, Rule_Step);
        build(context, token);
            return 35
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_Description);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 37
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_Description);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 38
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        build(context, token);
            return 33


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
parser::match_token_at_34(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        build(context, token);
            return 34
    if self.match_StepLine(context, token):
        start_rule(context, Rule_Step);
        build(context, token);
            return 35
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 37
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 38
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Empty(context, token):
        build(context, token);
            return 34


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
parser::match_token_at_35(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_TableRow(context, token):
        start_rule(context, Rule_DataTable);
        build(context, token);
            return 36
    if self.match_DocStringSeparator(context, token):
        start_rule(context, Rule_DocString);
        build(context, token);
            return 43
    if self.match_StepLine(context, token):
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
            return 35
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_Step);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 37
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_Step);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 38
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 35
    if self.match_Empty(context, token):
        build(context, token);
            return 35


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
parser::match_token_at_36(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_TableRow(context, token):
        build(context, token);
            return 36
    if self.match_StepLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
            return 35
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 37
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 38
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_DataTable);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 36
    if self.match_Empty(context, token):
        build(context, token);
            return 36


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
parser::match_token_at_37(token& token, parser_context& context)
{
    if self.match_TagLine(context, token):
        build(context, token);
            return 37
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_Tags);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 38
    if self.match_Comment(context, token):
        build(context, token);
            return 37
    if self.match_Empty(context, token):
        build(context, token);
            return 37


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
parser::match_token_at_38(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Empty(context, token):
        build(context, token);
            return 38
    if self.match_Comment(context, token):
        build(context, token);
            return 40
    if self.match_TableRow(context, token):
        start_rule(context, Rule_ExamplesTable);
        build(context, token);
            return 41
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 37
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 38
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        start_rule(context, Rule_Description);
        build(context, token);
            return 39


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
parser::match_token_at_39(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        end_rule(context, Rule_Description);
        build(context, token);
            return 40
    if self.match_TableRow(context, token):
        end_rule(context, Rule_Description);
        start_rule(context, Rule_ExamplesTable);
        build(context, token);
            return 41
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 37
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
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
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 38
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Description);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Other(context, token):
        build(context, token);
            return 39


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
parser::match_token_at_40(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_Comment(context, token):
        build(context, token);
            return 40
    if self.match_TableRow(context, token):
        start_rule(context, Rule_ExamplesTable);
        build(context, token);
            return 41
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 37
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 38
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Empty(context, token):
        build(context, token);
            return 40


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
parser::match_token_at_41(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_TableRow(context, token):
        build(context, token);
            return 41
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 37
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
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
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 38
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_ExamplesTable);
        end_rule(context, Rule_Examples);
        end_rule(context, Rule_ExamplesDefinition);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 41
    if self.match_Empty(context, token):
        build(context, token);
            return 41


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
parser::match_token_at_43(token& token, parser_context& context)
{
    if self.match_DocStringSeparator(context, token):
        build(context, token);
            return 44
    if self.match_Other(context, token):
        build(context, token);
            return 43


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
parser::match_token_at_44(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_StepLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
            return 35
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 37
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 38
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 44
    if self.match_Empty(context, token):
        build(context, token);
            return 44


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
parser::match_token_at_45(token& token, parser_context& context)
{
    if self.match_DocStringSeparator(context, token):
        build(context, token);
            return 46
    if self.match_Other(context, token):
        build(context, token);
            return 45


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
parser::match_token_at_46(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_StepLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
            return 29
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 31
    if self.match_TagLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 32
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Rule);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 46
    if self.match_Empty(context, token):
        build(context, token);
            return 46


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
parser::match_token_at_47(token& token, parser_context& context)
{
    if self.match_DocStringSeparator(context, token):
        build(context, token);
            return 48
    if self.match_Other(context, token):
        build(context, token);
            return 47


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
parser::match_token_at_48(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_StepLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
            return 15
    if self.match_TagLine(context, token):
        if self.lookahead_1(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 17
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ExamplesLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_ExamplesDefinition);
        start_rule(context, Rule_Examples);
        build(context, token);
            return 18
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Scenario);
        end_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 48
    if self.match_Empty(context, token):
        build(context, token);
            return 48


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
parser::match_token_at_49(token& token, parser_context& context)
{
    if self.match_DocStringSeparator(context, token):
        build(context, token);
            return 50
    if self.match_Other(context, token):
        build(context, token);
            return 49


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
parser::match_token_at_50(token& token, parser_context& context)
{
    if self.match_EOF(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        end_rule(context, Rule_Feature);
        build(context, token);
            return 42
    if self.match_StepLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        start_rule(context, Rule_Step);
        build(context, token);
            return 9
    if self.match_TagLine(context, token):
        if self.lookahead_0(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 11
    if self.match_TagLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        start_rule(context, Rule_Tags);
        build(context, token);
            return 22
    if self.match_ScenarioLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_ScenarioDefinition);
        start_rule(context, Rule_Scenario);
        build(context, token);
            return 12
    if self.match_RuleLine(context, token):
        end_rule(context, Rule_DocString);
        end_rule(context, Rule_Step);
        end_rule(context, Rule_Background);
        start_rule(context, Rule_Rule);
        start_rule(context, Rule_RuleHeader);
        build(context, token);
            return 23
    if self.match_Comment(context, token):
        build(context, token);
            return 50
    if self.match_Empty(context, token):
        build(context, token);
            return 50


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


    def lookahead_0(self, context, currentToken):
        currentToken.detach
        token = None
        queue = []
        match = False
        while True:
            token = self.read_token(context)
            token.detach
            queue.append(token)

            if (self.match_ScenarioLine(context, token) or False):
                match = True
                break

            if not (self.match_Empty(context, token) or self.match_Comment(context, token) or self.match_TagLine(context, token) or False):
                break

        context.token_queue.extend(queue)

        return match
    def lookahead_1(self, context, currentToken):
        currentToken.detach
        token = None
        queue = []
        match = False
        while True:
            token = self.read_token(context)
            token.detach
            queue.append(token)

            if (self.match_ExamplesLine(context, token) or False):
                match = True
                break

            if not (self.match_Empty(context, token) or self.match_Comment(context, token) or self.match_TagLine(context, token) or False):
                break

        context.token_queue.extend(queue)

        return match
    # private

    def handle_ast_error(self, context, argument, action):
        self.handle_external_error(context, True, argument, action)

    def handle_external_error(self, context, default_value, argument, action):
        if self.stop_at_first_error:
            return action(argument)

        try:
            return action(argument)
        except CompositeParserException as e:
            for error in e.errors:
                self.add_error(context, error)
        except ParserException as e:
            self.add_error(context, e)
        return default_value

