#include "cucumber/gherkin/AstBuilder.hpp"
#include "cucumber/gherkin/Exceptions.hpp"
#include "cucumber/gherkin/Keywords.hpp"
#include "cucumber/gherkin/Parser.hpp"
#include "cucumber/gherkin/TokenMatcher.hpp"
#include "cucumber/gherkin/Utils.hpp"
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>

namespace cucumber::gherkin
{
    TEST(Parser, RefreshesStepKeywordsOnDialectChange)
    {
        TokenMatcher matcher;
        for (const auto& dialectName : { "en", "fr", "en", "en-lol", "fr" })
        {
            Token language;
            language.line = Line(std::string("# language: ") + dialectName, 1);
            ASSERT_TRUE(matcher.MatchLanguage(language));
            const auto keywords = Keywords(dialectName, StringViews{ "given", "when", "then", "and", "but" });
            for (const auto keyword : keywords)
            {
                Token step;
                step.line = Line(std::string(keyword) + "example", 2);
                ASSERT_TRUE(matcher.MatchStepLine(step));
                EXPECT_EQ(step.matchedKeyword, keyword);
                EXPECT_EQ(step.matchedText, "example");
            }
            matcher.Reset();
            Token step;
            step.line = Line(std::string(keywords.front()) + "after reset", 3);
            EXPECT_TRUE(matcher.MatchStepLine(step));
            EXPECT_EQ(step.matchedText, "after reset");
        }
    }

    TEST(Parser, MatchesGoodAstFixtures)
    {
        std::size_t count = 0;
        for (const auto& entry : std::filesystem::recursive_directory_iterator(std::filesystem::path(TESTDATA_SRC) / "good"))
        {
            if (entry.path().extension() != ".feature")
            {
                continue;
            }
            SCOPED_TRACE(entry.path().string());
            std::ifstream reference(entry.path().string() + ".ast.ndjson");
            ASSERT_TRUE(reference.is_open());
            nlohmann::json expected;
            reference >> expected;
            Parser<AstBuilder> parser;
            const auto document = parser.Parse(expected.at("gherkinDocument").at("uri").get<std::string>(), Slurp(entry.path().string()));
            nlohmann::json actual;
            document.to_json(actual["gherkinDocument"]);
            EXPECT_EQ(actual, expected);
            ++count;
        }
        EXPECT_GT(count, 0);
    }

    TEST(Parser, RejectsBadFixtures)
    {
        std::size_t count = 0;
        for (const auto& entry : std::filesystem::recursive_directory_iterator(std::filesystem::path(TESTDATA_SRC) / "bad"))
        {
            if (entry.path().extension() != ".feature")
            {
                continue;
            }
            SCOPED_TRACE(entry.path().string());
            Parser<AstBuilder> parser;
            EXPECT_THROW((void)parser.Parse(entry.path().string(), Slurp(entry.path().string())), ParserError);
            ++count;
        }
        EXPECT_GT(count, 0);
    }
}
