#include "cucumber/gherkin/Exceptions.hpp"
#include "cucumber/gherkin/Line.hpp"
#include "cucumber/gherkin/Regex.hpp"
#include "cucumber/gherkin/Types.hpp"
#include "cucumber/gherkin/Utils.hpp"
#include <array>
#include <exception>
#include <gtest/gtest.h>
#include <string>
#include <string_view>

namespace cucumber::gherkin
{
    TEST(Regex, MatchesWholeExpressionAndExtractsCaptures)
    {
        const Regex regex(R"(([a-z]+)-([0-9]+))");
        std::string word;
        int number = 0;
        EXPECT_TRUE(FullMatch("abc-42", regex, word, number));
        EXPECT_EQ(word, "abc");
        EXPECT_EQ(number, 42);
        EXPECT_FALSE(FullMatch("abc-42 extra", regex));
        EXPECT_TRUE(FullMatch("abc-42", R"([a-z]+-[0-9]+)"));
    }

    TEST(Regex, SearchesAndExtractsViews)
    {
        const std::string source = "before abc-42 after";
        std::string_view word;
        int number = 0;
        EXPECT_TRUE(PartialMatch(source, R"(([a-z]+)-([0-9]+))", word, number));
        EXPECT_EQ(word, "abc");
        EXPECT_EQ(word.data(), source.data() + 7);
        EXPECT_EQ(number, 42);
        StringViews captures;
        EXPECT_TRUE(PartialMatch(source, Regex(R"(([a-z]+)-([0-9]+))"), captures));
        EXPECT_EQ(captures, (StringViews{ "abc", "42" }));
        EXPECT_FALSE(PartialMatch(source, R"(\d{3})"));
    }

    TEST(Regex, HandlesEmptyExpressionsAndOptionalCaptures)
    {
        EXPECT_TRUE(FullMatch(std::string_view{}, Regex("")));
        EXPECT_TRUE(FullMatch(std::string_view{}, Regex(std::string_view{})));
        EXPECT_TRUE(PartialMatch(std::string_view{}, ""));
        EXPECT_FALSE(FullMatch(std::string_view{}, Regex(".")));
        StringViews captures;
        EXPECT_TRUE(FullMatch("b", Regex("(a)?b"), captures));
        ASSERT_EQ(captures.size(), 1);
        EXPECT_TRUE(captures[0].empty());
    }

    TEST(Regex, SplitsLikeRegexTokenIterator)
    {
        EXPECT_EQ(Split("@", "@one@two@"), (Strings{ "", "one", "two" }));
        EXPECT_EQ(Split("@", "@@"), (Strings{ "", "" }));
        EXPECT_EQ(Split("@", "one"), (Strings{ "one" }));
        EXPECT_TRUE(Split("@", "").empty());
        EXPECT_EQ(Split("", "ab"), (Strings{ "", "a", "b" }));
        Strings result{ "old" };
        Split(",", "a,,b", result);
        EXPECT_EQ(result, (Strings{ "a", "", "b" }));
    }

    TEST(Regex, SubstitutesWithStandardReplacementSyntax)
    {
        EXPECT_EQ(Substitute(std::string("abc-42 abc-7"), R"(([a-z]+)-(\d+))", "$2:$1"), "42:abc 7:abc");
        EXPECT_EQ(Substitute(std::string("aba"), "a", "$$[$&]"), "$[a]b$[a]");
        EXPECT_EQ(Substitute(std::string("aba"), "a", "$`:$'"), ":babb:");
        EXPECT_EQ(Substitute(std::string("x"), "(x)", "$01/$10/$0"), "x//x");
        EXPECT_EQ(Substitute(std::string("ab"), "", "-"), "-a-b-");
        EXPECT_EQ(Substitute(std::string("a"), "a*", "-"), "--");
        EXPECT_EQ(Substitute(std::string{}, "", "-"), "-");
        EXPECT_EQ(Substitute(std::wstring(L"\u4e16\u754c"), L"", L"-"), L"-\u4e16-\u754c-");
        std::string source = "abc123";
        Substitute(source, R"(\d+)", "!");
        EXPECT_EQ(source, "abc!");
    }

    TEST(Regex, RejectsInvalidPatterns)
    {
        EXPECT_THROW((void)Regex("["), std::exception);
    }

    TEST(Regex, PreservesByteMatchingAndAsciiWhitespace)
    {
        EXPECT_TRUE(FullMatch(std::string("\xc3\xa9"), Regex("..")));
        EXPECT_TRUE(FullMatch("\v", Regex(R"(\s)")));
        EXPECT_FALSE(FullMatch("\v", Regex(R"(\S)")));
        EXPECT_EQ(Strip(std::string(" \t\vtext\r\n")), "text");
        EXPECT_EQ(Strip(std::wstring(L" \t\v\u0085\u00a0text\u00a0\u0085\r\n")), L"text");
        EXPECT_EQ(Lstrip(std::wstring(L" \u00a0\u4e16\u754c ")), L"\u4e16\u754c ");
        EXPECT_EQ(Strip(std::string("\x85\xa0text\xa0\x85")), "text");
    }

    TEST(Regex, PreservesTableEscapesAndTagValidation)
    {
        const auto cells = Line(R"(  | a\|b | c\n d | e\\f |)", 1).TableCells();
        ASSERT_EQ(cells.size(), 3);
        EXPECT_EQ(cells[0].text, "a|b");
        EXPECT_EQ(cells[1].text, "c\n d");
        EXPECT_EQ(cells[2].text, "e\\f");
        const auto tags = Line("  @one @two # comment", 1).Tags();
        ASSERT_EQ(tags.size(), 2);
        EXPECT_EQ(tags[0].text, "@one");
        EXPECT_EQ(tags[1].text, "@two");
        EXPECT_THROW((void)Line("@not a tag", 1).Tags(), ParserError);
    }

    TEST(Regex, ReusesCompiledWidePatterns)
    {
        const WideRegex regex(L"([a-z]+)-([0-9]+)");
        for (int i = 0; i < 3; ++i)
        {
            EXPECT_EQ(regex.Replace(L"abc-42 def-7", L"$2:$1"), L"42:abc 7:def");
        }
        EXPECT_EQ(WideRegex(L"").Replace(L"\u4e16\u754c", L"-"), L"-\u4e16-\u754c-");
        EXPECT_EQ(WideRegex(std::wstring_view{}).Replace(L"", L"-"), L"-");
        EXPECT_THROW((void)WideRegex(L"["), std::exception);
    }

    TEST(Regex, PreservesTableWhitespaceUnicodeAndColumns)
    {
        const auto cells = Line("  | \t\xc2\xa0\xc2\x85"
                                "one\xc2\xa0 | \xc3\xa9 | \xe4\xb8\x96\xe7\x95\x8c | \\ntext\\n |   |",
            1)
                               .TableCells();
        ASSERT_EQ(cells.size(), 5);
        EXPECT_EQ(cells[0].text, "one");
        EXPECT_EQ(cells[0].column, 8);
        EXPECT_EQ(cells[1].text, "\xc3\xa9");
        EXPECT_EQ(cells[1].column, 15);
        EXPECT_EQ(cells[2].text, "\xe4\xb8\x96\xe7\x95\x8c");
        EXPECT_EQ(cells[2].column, 19);
        EXPECT_EQ(cells[3].text, "\ntext\n");
        EXPECT_EQ(cells[3].column, 24);
        EXPECT_TRUE(cells[4].text.empty());
        EXPECT_EQ(cells[4].column, 37);
    }

    TEST(Regex, DecodesTableEscapesExactlyOnce)
    {
        const auto cells = Line(R"(| \\n | \\\n | \\ | \| | \q | \\\| | \\\\ | $1 |)", 1).TableCells();
        const Strings expected{ R"(\n)", "\\\n", "\\", "|", R"(\q)", "\\|", "\\\\", "$1" };
        ASSERT_EQ(cells.size(), expected.size());
        for (std::size_t i = 0; i < expected.size(); ++i)
        {
            EXPECT_EQ(cells[i].text, expected[i]);
        }
        EXPECT_TRUE(Line("no separators", 1).TableCells().empty());
        const auto emptyCells = Line("||", 1).TableCells();
        ASSERT_EQ(emptyCells.size(), 1);
        EXPECT_TRUE(emptyCells[0].text.empty());
        EXPECT_EQ(emptyCells[0].column, 2);
    }

    TEST(Regex, ConvertsNonOwningUnicodeViews)
    {
        EXPECT_TRUE(ToWide(std::string_view{}).empty());
        EXPECT_TRUE(ToNarrow(std::wstring_view{}).empty());
        const std::string narrow = "x\xe4\xb8\x96\xe7\x95\x8c"
                                   "y";
        const std::wstring wide = L"x\u4e16\u754cy";
        EXPECT_EQ(ToWide(std::string_view(narrow).substr(1, 6)), L"\u4e16\u754c");
        EXPECT_EQ(ToNarrow(std::wstring_view(wide).substr(1, 2)), "\xe4\xb8\x96\xe7\x95\x8c");
    }

    TEST(Regex, HandlesLargeCaptureCountsAndRepeatedOptionalCaptures)
    {
        const Regex regex("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)");
        StringViews captures;
        EXPECT_TRUE(FullMatch("abcdefghij", regex, captures));
        EXPECT_EQ(captures, (StringViews{ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" }));
        EXPECT_EQ(regex.Replace("abcdefghij abcdefghij", "$10$1"), "ja ja");
        EXPECT_EQ(Regex("(a)?b").Replace("ab b ab", "<$1>"), "<a> <> <a>");
        EXPECT_EQ(Regex("(,)").Split("a,b,,c"), (Strings{ "a", "b", "", "c" }));
    }

    template<typename CharT>
    void CheckTrimPatterns(const std::basic_string<CharT>& text)
    {
        constexpr std::array patterns{ RePattern::none, RePattern::allSpaces, RePattern::spacesNoNl, RePattern::crlf, RePattern::cr,
            RePattern::bol, RePattern::eol };
        for (const auto pattern : patterns)
        {
            SCOPED_TRACE(static_cast<int>(pattern));
            const auto view = AsView(text);
            const auto left = Strip(view, StripPattern<CharT>(RePattern::bol, RePatterns<CharT>::Get(pattern)));
            const auto right = Strip(view, StripPattern<CharT>(RePatterns<CharT>::Get(pattern), RePattern::eol));
            EXPECT_EQ(Lstrip(text, pattern), left);
            EXPECT_EQ(Rstrip(text, pattern), right);
            EXPECT_EQ(Strip(text, pattern), Lstrip(right, pattern));
        }
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
        EXPECT_EQ(Strip(std::string_view("abc123def"), StripPattern<char>(R"([0-9]+)")), "abcdef");
        EXPECT_EQ(Strip(std::wstring_view(L"abc123def"), StripPattern<wchar_t>(LR"([0-9]+)")), L"abcdef");
    }

    TEST(Regex, DirectTrimmingPreservesBoundaryCharacters)
    {
        for (unsigned int code = 0; code <= 255; ++code)
        {
            const std::string edge(1, static_cast<char>(code));
            CheckTrimPatterns(edge + edge + "text" + edge + edge);
            const std::wstring wideEdge(1, static_cast<wchar_t>(code));
            CheckTrimPatterns(wideEdge + wideEdge + L"text" + wideEdge + wideEdge);
        }
        EXPECT_EQ(Lstrip(std::string("\r\rtext"), RePattern::cr), "\rtext");
        EXPECT_EQ(Rstrip(std::string("text\r\r"), RePattern::cr), "text\r");
        EXPECT_EQ(Rstrip(std::string("text\r\n"), RePattern::crlf), "text\r\n");
        EXPECT_EQ(Strip(std::string("\n text \n"), RePattern::spacesNoNl), "\n text \n");
        EXPECT_EQ(Strip(std::wstring(L"\u2003text\u2003")), L"\u2003text\u2003");
    }
}
