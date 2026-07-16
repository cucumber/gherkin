
#include "cucumber/gherkin/token_matcher.hpp"
#include "cucumber/gherkin/dialect.hpp"
#include "cucumber/gherkin/exceptions.hpp"
#include "cucumber/gherkin/keywords.hpp"
#include "cucumber/gherkin/regex.hpp"
#include "cucumber/gherkin/rule_type.hpp"
#include "cucumber/gherkin/token.hpp"
#include "cucumber/gherkin/types.hpp"
#include "cucumber/gherkin/utils.hpp"
#include "cucumber/messages/StepKeywordType.hpp"
#include <algorithm>
#include <cucumber/messages/Location.hpp>
#include <optional>
#include <regex>
#include <string>
#include <string_view>
#include <utility>

namespace cucumber::gherkin
{

    static const std::regex language_re{ "^\\s*#\\s*language\\s*:\\s*([a-zA-Z\\-_]+)\\s*$" };

    TokenMatcher::TokenMatcher(const std::string& dialect_name)
    {
        change_dialect(dialect_name);
    }

    TokenMatcher::~TokenMatcher()
    {}

    void TokenMatcher::reset()
    {
        indent_to_remove_ = 0;
        active_doc_string_separator_.clear();
    }

    bool TokenMatcher::match_feature_line(Token& token)
    {
        return match_title_line(token, RuleType::feature_line, keywords("feature"));
    }

    bool TokenMatcher::match_rule_line(Token& token)
    {
        return match_title_line(token, RuleType::rule_line, keywords("rule"));
    }

    bool TokenMatcher::match_scenario_line(Token& token)
    {
        auto scenario_type = RuleType::scenario_line;

        return match_title_line(token, scenario_type, keywords("scenario")) || match_title_line(token, scenario_type, keywords("scenarioOutline"));
    }

    bool TokenMatcher::match_background_line(Token& token)
    {
        return match_title_line(token, RuleType::background_line, keywords("background"));
    }

    bool TokenMatcher::match_examples_line(Token& token)
    {
        return match_title_line(token, RuleType::examples_line, keywords("examples"));
    }

    bool TokenMatcher::match_table_row(Token& token)
    {
        if (!token.line.startswith("|"))
        {
            return false;
        }

        TokenInfo info;
        info.items = token.line.table_cells();
        set_token_matched(token, RuleType::table_row, info);

        return true;
    }

    bool TokenMatcher::match_language(Token& token)
    {
        std::string dialect_name;

        if (!full_match(token.line.line_text(), language_re, dialect_name))
        {
            return false;
        }

        set_token_matched(token, RuleType::language, { dialect_name });
        change_dialect(dialect_name);

        return true;
    }

    bool TokenMatcher::match_tag_line(Token& token)
    {
        if (!token.line.startswith("@"))
        {
            return false;
        }

        set_token_matched(token, RuleType::tag_line, { std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::move(token.line.tags()) });

        return true;
    }

    bool TokenMatcher::match_title_line(Token& token, RuleType token_type, string_views keywords)
    {
        for (const auto& keyword : keywords)
        {
            std::string keyword_str(keyword);

            if (!token.line.startswith_title_keyword(keyword_str))
            {
                continue;
            }

            set_token_matched(token, token_type, { token.line.get_keyword_trimmed(keyword_str), keyword_str });

            return true;
        }

        return false;
    }

    bool TokenMatcher::match_e_o_f(Token& token)
    {
        if (!token.eof)
        {
            return false;
        }

        set_token_matched(token, RuleType::e_o_f);

        return true;
    }

    bool TokenMatcher::match_empty(Token& token)
    {
        if (!token.line.is_empty())
        {
            return false;
        }

        set_token_matched(token, RuleType::empty, { std::nullopt, std::nullopt, std::nullopt, 0 });

        return true;
    }

    bool TokenMatcher::match_comment(Token& token)
    {
        if (!token.line.startswith("#"))
        {
            return false;
        }

        auto comment_text = std::string(token.line.get_line_text(0));

        subst(comment_text, "[\\r\\n]+$");

        set_token_matched(token, RuleType::comment, { comment_text, std::nullopt, std::nullopt, 0 });

        return true;
    }

    bool TokenMatcher::match_other(Token& token)
    {
        std::string text = std::string(token.line.get_line_text(indent_to_remove_));

        set_token_matched(token, RuleType::other, { unescape_docstring(text), std::nullopt, std::nullopt, 0 });

        return true;
    }

    bool TokenMatcher::match_step_line(Token& token)
    {
        string_views step_keyword_names = { "given", "when", "then", "and", "but" };
        auto keywords = cucumber::gherkin::keywords(dialect_name_, step_keyword_names);

        // Prefer the longest step keyword by sorting keywords in descending order
        // by length (in bytes, not codepoints or graphemes - adequate for dealing
        // with keywords that are prefixes of each other).
        std::sort(keywords.begin(), keywords.end(),
            [](const std::string_view& first, const std::string_view& second)
            {
                return first.length() > second.length();
            });

        for (const auto& keyword : keywords)
        {
            if (!token.line.startswith(keyword))
            {
                continue;
            }

            auto title = token.line.get_rest_trimmed(keyword.size());

            set_token_matched(token, RuleType::step_line, { title, std::string(keyword), keyword_type(keyword) });

            return true;
        }

        return false;
    }

    bool TokenMatcher::match_doc_string_separator(Token& token)
    {
        if (active_doc_string_separator_.empty())
        {
            return match_doc_string_separator_(token, "\"\"\"", true) || match_doc_string_separator_(token, "```", true);
        }

        return match_doc_string_separator_(token, active_doc_string_separator_, false);
    }

    bool TokenMatcher::match_doc_string_separator_(Token& token, std::string_view separator, bool is_open)
    {
        if (!token.line.startswith(separator))
        {
            return false;
        }

        std::string content_type;
        std::string tseparator = std::string(separator);

        if (is_open)
        {
            content_type = token.line.get_rest_trimmed(separator.size());
            active_doc_string_separator_ = tseparator;
            indent_to_remove_ = token.line.indent();
        }
        else
        {
            active_doc_string_separator_.clear();
            indent_to_remove_ = 0;
        }

        set_token_matched(token, RuleType::doc_string_separator, { content_type, tseparator });

        return true;
    }

    void TokenMatcher::set_token_matched(Token& token, RuleType matched_type, const TokenInfo& info)
    {
        using namespace std::literals;

        token.matched_type = matched_type;

        if (info.text)
        {
            token.matched_text.assign(rstrip(*info.text, RePattern::crlf));
        }

        if (info.keyword)
        {
            token.matched_keyword = *info.keyword;
        }

        if (info.keyword_type)
        {
            token.matched_keyword_type = *info.keyword_type;
        }

        if (info.indent)
        {
            token.matched_indent = *info.indent;
        }
        else
        {
            token.matched_indent = token.line.indent();
        }

        token.matched_items = std::move(info.items);
        token.location.column = token.matched_indent + 1;
        token.matched_gherkin_dialect = dialect_name_;
    }

    const string_views& TokenMatcher::keywords(std::string_view keyword) const
    {
        return cucumber::gherkin::keywords(dialect_name_, keyword);
    }

    cucumber::messages::StepKeywordType TokenMatcher::keyword_type(std::string_view keyword) const
    {
        auto found = keyword_types_.find(keyword);

        if (found != keyword_types_.end())
        {
            const auto& keyword_list = found->second;

            if (keyword_list.size() == 1)
            {
                return keyword_list[0];
            }
        }

        return cucumber::messages::StepKeywordType::UNKNOWN;
    }

    void TokenMatcher::change_dialect(const std::string& dialect_name, const cms::Location& location)
    {
        if (all_keywords().find(dialect_name) == all_keywords().end())
        {
            throw NoSuchLanguageError(dialect_name, location);
        }

        dialect_name_ = dialect_name;

        auto Dialect = get_dialect(dialect_name_);

        keyword_types_.clear();

        for (const auto& keyword : Dialect.given_keywords)
        {
            keyword_types_[keyword].push_back(cucumber::messages::StepKeywordType::CONTEXT);
        }

        for (const auto& keyword : Dialect.when_keywords)
        {
            keyword_types_[keyword].push_back(cucumber::messages::StepKeywordType::ACTION);
        }

        for (const auto& keyword : Dialect.then_keywords)
        {
            keyword_types_[keyword].push_back(cucumber::messages::StepKeywordType::OUTCOME);
        }

        for (const auto& keyword : Dialect.and_keywords)
        {
            keyword_types_[keyword].push_back(cucumber::messages::StepKeywordType::CONJUNCTION);
        }

        for (const auto& keyword : Dialect.but_keywords)
        {
            keyword_types_[keyword].push_back(cucumber::messages::StepKeywordType::CONJUNCTION);
        }
    }

    std::string TokenMatcher::unescape_docstring(const std::string& text) const
    {
        using namespace std::literals;

        std::string unescaped;

        if (active_doc_string_separator_ == "\"\"\"")
        {
            unescaped = subst(text, "\\\\\"\\\\\"\\\\\"", "\"\"\"");
        }
        else if (active_doc_string_separator_ == "```")
        {
            unescaped = subst(text, "\\\\`\\\\`\\\\`", "```");
        }
        else
        {
            unescaped = text;
        }

        return unescaped;
    }

}
