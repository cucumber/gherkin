#include "cucumber/gherkin/Exceptions.hpp"
#include "cucumber/gherkin/Line.hpp"
#include "cucumber/gherkin/Regex.hpp"
#include "cucumber/gherkin/Types.hpp"
#include "cucumber/gherkin/Utils.hpp"
#include <array>
#include <cstddef>
#include <exception>
#include <regex>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iterator>
#include <limits>
#include <string>
#include <string_view>

namespace cucumber::gherkin
{
    namespace
    {

        template<typename CharT>
        void CheckTrimPatterns(const std::basic_string<CharT>& text)
        {
            constexpr std::array patterns{
                RePattern::none,
                RePattern::allSpaces,
                RePattern::spacesNoNl,
                RePattern::crlf,
                RePattern::cr,
                RePattern::bol,
                RePattern::eol,
            };

            for (const auto pattern : patterns)
            {
                SCOPED_TRACE(static_cast<int>(pattern));

                const auto view = AsView(text);
                const auto left = Strip(view, StripPattern<CharT>(RePattern::bol, RePatterns<CharT>::Get(pattern)));
                const auto right = Strip(view, StripPattern<CharT>(RePatterns<CharT>::Get(pattern), RePattern::eol));

                EXPECT_THAT(Lstrip(text, pattern), testing::Eq(left));
                EXPECT_THAT(Rstrip(text, pattern), testing::Eq(right));
                EXPECT_THAT(Strip(text, pattern), testing::Eq(Lstrip(right, pattern)));
            }
        }
    }

    TEST(Regex, MatchesWholeExpressionAndExtractsCaptures)
    {
        const Regex regex(R"(([a-z]+)-([0-9]+))");
        std::string word;
        int number = 0;

        EXPECT_THAT(FullMatch("abc-42", regex, word, number), testing::IsTrue());
        EXPECT_THAT(word, testing::Eq("abc"));
        EXPECT_THAT(number, testing::Eq(42));

        EXPECT_THAT(FullMatch("abc-42 extra", regex), testing::IsFalse());
        EXPECT_THAT(FullMatch("abc-42", R"([a-z]+-[0-9]+)"), testing::IsTrue());
    }

    TEST(Regex, SearchesAndExtractsViews)
    {
        const std::string source = "before abc-42 after";
        std::string_view word;
        int number = 0;

        EXPECT_THAT(PartialMatch(source, R"(([a-z]+)-([0-9]+))", word, number), testing::IsTrue());
        EXPECT_THAT(word, testing::Eq("abc"));
        EXPECT_THAT(word.data(), testing::Eq(std::next(source.data(), 7)));
        EXPECT_THAT(number, testing::Eq(42));

        StringViews captures;

        EXPECT_THAT(PartialMatch(source, Regex(R"(([a-z]+)-([0-9]+))"), captures), testing::IsTrue());
        EXPECT_THAT(captures, testing::Eq((StringViews{ "abc", "42" })));

        EXPECT_THAT(PartialMatch(source, R"(\d{3})"), testing::IsFalse());
    }

    TEST(Regex, HandlesEmptyExpressionsAndOptionalCaptures)
    {
        EXPECT_THAT(FullMatch(std::string_view{}, Regex("")), testing::IsTrue());
        EXPECT_THAT(FullMatch(std::string_view{}, Regex(std::string_view{})), testing::IsTrue());
        EXPECT_THAT(PartialMatch(std::string_view{}, ""), testing::IsTrue());
        EXPECT_THAT(FullMatch(std::string_view{}, Regex(".")), testing::IsFalse());

        StringViews captures;

        EXPECT_THAT(FullMatch("b", Regex("(a)?b"), captures), testing::IsTrue());
        ASSERT_THAT(captures.size(), testing::Eq(1));
        EXPECT_THAT(captures.at(0).empty(), testing::IsTrue());
    }

    TEST(Regex, SplitsLikeRegexTokenIterator)
    {
        EXPECT_THAT(Split("@", "@one@two@"), testing::Eq((Strings{ "", "one", "two" })));
        EXPECT_THAT(Split("@", "@@"), testing::Eq((Strings{ "", "" })));
        EXPECT_THAT(Split("@", "one"), testing::Eq((Strings{ "one" })));
        EXPECT_THAT(Split("@", "").empty(), testing::IsTrue());
        EXPECT_THAT(Split("", "ab"), testing::Eq((Strings{ "", "a", "b" })));

        Strings result{ "old" };

        Split(",", "a,,b", result);

        EXPECT_THAT(result, testing::Eq((Strings{ "a", "", "b" })));
    }

    TEST(Regex, SubstitutesWithStandardReplacementSyntax)
    {
        EXPECT_THAT(Substitute(std::string("abc-42 abc-7"), R"(([a-z]+)-(\d+))", "$2:$1"), testing::Eq("42:abc 7:abc"));
        EXPECT_THAT(Substitute(std::string("aba"), "a", "$$[$&]"), testing::Eq("$[a]b$[a]"));
        EXPECT_THAT(Substitute(std::string("aba"), "a", "$`:$'"), testing::Eq(":babb:"));
        EXPECT_THAT(Substitute(std::string("x"), "(x)", "$01/$10/$&"), testing::Eq("x//x"));

        EXPECT_THAT(Substitute(std::string("ab"), "", "-"), testing::Eq("-a-b-"));
        EXPECT_THAT(Substitute(std::string("a"), "a+", "-"), testing::Eq("-"));
        EXPECT_THAT(Substitute(std::string{}, "", "-"), testing::Eq("-"));
        EXPECT_THAT(Substitute(std::wstring(L"\u4e16\u754c"), L"", L"-"), testing::Eq(L"-\u4e16-\u754c-"));

        std::string source = "abc123";

        Substitute(source, R"(\d+)", "!");

        EXPECT_THAT(source, testing::Eq("abc!"));
    }

    TEST(Regex, PreservesBackendReplacementEdgeCases)
    {
#ifdef GHERKIN_TEST_RE2
        EXPECT_THAT(Substitute(std::string("x"), "(x)", "$01/$10/$0"), testing::Eq("x//x"));
        EXPECT_THAT(Substitute(std::string("a"), "a*", "-"), testing::Eq("--"));
#else
        EXPECT_THAT(Substitute(std::string("x"), "(x)", "$01/$10/$0"),
            testing::Eq(std::regex_replace(std::string("x"), std::regex("(x)"), "$01/$10/$0")));
        EXPECT_THAT(Substitute(std::string("a"), "a*", "-"),
            testing::Eq(std::regex_replace(std::string("a"), std::regex("a*"), "-")));
#endif
    }

    TEST(Regex, RejectsInvalidPatterns)
    {
        EXPECT_THAT(
            [&]
            {
                (void)Regex("[");
            },
            testing::Throws<std::exception>());
    }

    TEST(Regex, PreservesByteMatchingAndAsciiWhitespace)
    {
        EXPECT_THAT(FullMatch("\xc3\xa9", Regex("..")), testing::IsTrue());
        EXPECT_THAT(FullMatch("\v", Regex(R"(\s)")), testing::IsTrue());
        EXPECT_THAT(FullMatch("\v", Regex(R"(\S)")), testing::IsFalse());

        EXPECT_THAT(Strip(std::string(" \t\vtext\r\n")), testing::Eq("text"));
        EXPECT_THAT(Strip(std::wstring(L" \t\v\u0085\u00a0text\u00a0\u0085\r\n")), testing::Eq(L"text"));
        EXPECT_THAT(Lstrip(std::wstring(L" \u00a0\u4e16\u754c ")), testing::Eq(L"\u4e16\u754c "));
        EXPECT_THAT(Strip(std::string("\x85\xa0text\xa0\x85")), testing::Eq("text"));
    }

    TEST(Regex, PreservesTableEscapesAndTagValidation)
    {
        const auto cells = Line(R"(  | a\|b | c\n d | e\\f |)", 1).TableCells();

        ASSERT_THAT(cells.size(), testing::Eq(3));
        EXPECT_THAT(cells.at(0).text, testing::Eq("a|b"));
        EXPECT_THAT(cells.at(1).text, testing::Eq("c\n d"));
        EXPECT_THAT(cells.at(2).text, testing::Eq("e\\f"));

        const auto tags = Line("  @one @two # comment", 1).Tags();

        ASSERT_THAT(tags.size(), testing::Eq(2));
        EXPECT_THAT(tags.at(0).text, testing::Eq("@one"));
        EXPECT_THAT(tags.at(1).text, testing::Eq("@two"));

        EXPECT_THAT(
            [&]
            {
                (void)Line("@not a tag", 1).Tags();
            },
            testing::Throws<ParserError>());
    }

    TEST(Regex, ReusesCompiledWidePatterns)
    {
        const WideRegex regex(L"([a-z]+)-([0-9]+)");

        for (int i = 0; i < 3; ++i)
        {
            EXPECT_THAT(regex.Replace(L"abc-42 def-7", L"$2:$1"), testing::Eq(L"42:abc 7:def"));
        }

        EXPECT_THAT(WideRegex(L"").Replace(L"\u4e16\u754c", L"-"), testing::Eq(L"-\u4e16-\u754c-"));
        EXPECT_THAT(WideRegex(std::wstring_view{}).Replace(L"", L"-"), testing::Eq(L"-"));
        EXPECT_THAT(
            [&]
            {
                (void)WideRegex(L"[");
            },
            testing::Throws<std::exception>());
    }

    TEST(Regex, PreservesTableWhitespaceUnicodeAndColumns)
    {
        const auto cells = Line("  | \t\xc2\xa0\xc2\x85"
                                "one\xc2\xa0 | \xc3\xa9 | \xe4\xb8\x96\xe7\x95\x8c | \\ntext\\n |   |",
            1)
                               .TableCells();

        ASSERT_THAT(cells.size(), testing::Eq(5));

        EXPECT_THAT(cells.at(0).text, testing::Eq("one"));
        EXPECT_THAT(cells.at(0).column, testing::Eq(8));

        EXPECT_THAT(cells.at(1).text, testing::Eq("\xc3\xa9"));
        EXPECT_THAT(cells.at(1).column, testing::Eq(15));

        EXPECT_THAT(cells.at(2).text, testing::Eq("\xe4\xb8\x96\xe7\x95\x8c"));
        EXPECT_THAT(cells.at(2).column, testing::Eq(19));

        EXPECT_THAT(cells.at(3).text, testing::Eq("\ntext\n"));
        EXPECT_THAT(cells.at(3).column, testing::Eq(24));

        EXPECT_THAT(cells.at(4).text.empty(), testing::IsTrue());
        EXPECT_THAT(cells.at(4).column, testing::Eq(37));
    }

    TEST(Regex, DecodesTableEscapesExactlyOnce)
    {
        const auto cells = Line(R"(| \\n | \\\n | \\ | \| | \q | \\\| | \\\\ | $1 |)", 1).TableCells();
        const Strings expected{ R"(\n)", "\\\n", "\\", "|", R"(\q)", "\\|", "\\\\", "$1" };

        ASSERT_THAT(cells.size(), testing::Eq(expected.size()));

        for (std::size_t i = 0; i < expected.size(); ++i)
        {
            EXPECT_THAT(cells.at(i).text, testing::Eq(expected.at(i)));
        }

        EXPECT_THAT(Line("no separators", 1).TableCells().empty(), testing::IsTrue());

        const auto emptyCells = Line("||", 1).TableCells();

        ASSERT_THAT(emptyCells.size(), testing::Eq(1));
        EXPECT_THAT(emptyCells.at(0).text.empty(), testing::IsTrue());
        EXPECT_THAT(emptyCells.at(0).column, testing::Eq(2));
    }

    TEST(Regex, ConvertsNonOwningUnicodeViews)
    {
        EXPECT_THAT(ToWide(std::string_view{}).empty(), testing::IsTrue());
        EXPECT_THAT(ToNarrow(std::wstring_view{}).empty(), testing::IsTrue());

        const std::string narrow = "x\xe4\xb8\x96\xe7\x95\x8c"
                                   "y";
        const std::wstring wide = L"x\u4e16\u754cy";

        EXPECT_THAT(ToWide(std::string_view(narrow).substr(1, 6)), testing::Eq(L"\u4e16\u754c"));
        EXPECT_THAT(ToNarrow(std::wstring_view(wide).substr(1, 2)), testing::Eq("\xe4\xb8\x96\xe7\x95\x8c"));
    }

    TEST(Regex, HandlesLargeCaptureCountsAndRepeatedOptionalCaptures)
    {
        const Regex regex("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)");
        StringViews captures;

        EXPECT_THAT(FullMatch("abcdefghij", regex, captures), testing::IsTrue());
        EXPECT_THAT(captures, testing::Eq((StringViews{ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" })));

        EXPECT_THAT(regex.Replace("abcdefghij abcdefghij", "$10$1"), testing::Eq("ja ja"));
        EXPECT_THAT(Regex("(a)?b").Replace("ab b ab", "<$1>"), testing::Eq("<a> <> <a>"));
        EXPECT_THAT(Regex("(,)").Split("a,b,,c"), testing::Eq((Strings{ "a", "b", "", "c" })));
    }

    TEST(Regex, DirectTrimmingMatchesRegexPatterns)
    {
        const std::array<std::string, 6> inputs{ "", "text", " \t\v\f\r\n", "\x85\xa0text\xa0\x85", "\r\rtext\r\r\n", "a b\r\nc\t" };

        for (const auto& text : inputs)
        {
            CheckTrimPatterns(text);
            CheckTrimPatterns(ToWide(text));
        }

        CheckTrimPatterns(std::wstring(L" \t\u0085\u00a0\u4e16\u754c\u00a0\u0085\r\n"));

        EXPECT_THAT(Strip(std::string_view("abc123def"), StripPattern<char>(R"([0-9]+)")), testing::Eq("abcdef"));
        EXPECT_THAT(Strip(std::wstring_view(L"abc123def"), StripPattern<wchar_t>(LR"([0-9]+)")), testing::Eq(L"abcdef"));
    }

    TEST(Regex, DirectTrimmingPreservesBoundaryCharacters)
    {
        constexpr unsigned int maxByteValue = std::numeric_limits<unsigned char>::max();

        for (unsigned int code = 0; code <= maxByteValue; ++code)
        {
            const std::string edge(2, static_cast<char>(code));
            auto text = edge;
            text.append("text").append(edge);
            CheckTrimPatterns(text);

            const std::wstring wideEdge(2, static_cast<wchar_t>(code));
            auto wideText = wideEdge;
            wideText.append(L"text").append(wideEdge);
            CheckTrimPatterns(wideText);
        }

        EXPECT_THAT(Lstrip(std::string("\r\rtext"), RePattern::cr), testing::Eq("\rtext"));
        EXPECT_THAT(Rstrip(std::string("text\r\r"), RePattern::cr), testing::Eq("text\r"));
        EXPECT_THAT(Rstrip(std::string("text\r\n"), RePattern::crlf), testing::Eq("text\r\n"));
        EXPECT_THAT(Strip(std::string("\n text \n"), RePattern::spacesNoNl), testing::Eq("\n text \n"));
        EXPECT_THAT(Strip(std::wstring(L"\u2003text\u2003")), testing::Eq(L"\u2003text\u2003"));
    }
}
