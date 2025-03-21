package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import java.util.stream.Stream;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import java.lang.reflect.Method;
import io.cucumber.gherkin.Parser.TokenType;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertFalse;
import java.util.List;
import java.util.Arrays;
import java.util.stream.Collectors;
import static org.junit.jupiter.api.Assertions.assertNotNull;

class GherkinInMarkdownTokenMatcherTest {

    private enum HeaderType {
        FEATURE(TokenType.FeatureLine, "Feature", "match_FeatureLine"),
        RULE(TokenType.RuleLine, "Rule", "match_RuleLine"),
        BACKGROUND(TokenType.BackgroundLine, "Background", "match_BackgroundLine"),
        EXAMPLES(TokenType.ExamplesLine, "Examples", "match_ExamplesLine"),
        SCENARIO(TokenType.ScenarioLine, "Scenario", "match_ScenarioLine"),
        SCENARIO_OUTLINE(TokenType.ScenarioLine, "Scenario Outline", "match_ScenarioLine");

        private final TokenType tokenType;
        private final String keyword;
        private final String methodName;

        HeaderType(TokenType tokenType, String keyword, String methodName) {
            this.tokenType = tokenType;
            this.keyword = keyword;
            this.methodName = methodName;
        }
    }

    @ParameterizedTest(name = "line ''{0}'' should match: {1}")
    @MethodSource("headerLineTestCases")
    void testHeaderLineMatching(HeaderType headerType, String line, boolean shouldMatch, TokenType expectedType,
            String expectedKeyword, String expectedText, Integer expectedIndent) throws Exception {
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher("en");
        Token token = new Token(new GherkinLine(line, 1), new Location(1, 1));

        Method method = matcher.getClass().getMethod(headerType.methodName, Token.class);
        boolean result = (boolean) method.invoke(matcher, token);

        assertEquals(shouldMatch, result,
                String.format("Line '%s' should%s match a feature line",
                        line, shouldMatch ? "" : " not"));
        if (shouldMatch) {
            assertEquals(expectedKeyword, token.matchedKeyword);
            assertEquals(expectedText, token.matchedText);
            assertEquals(expectedIndent, token.matchedIndent);
            assertEquals("en", token.matchedGherkinDialect.getLanguage());
            assertEquals(expectedType, token.matchedType);
        }
    }

    @ParameterizedTest(name = "should match {0} feature keyword in {1}")
    @MethodSource("featureDialectTestCases")
    void testFeatureLineDialectMatching(String keyword, String dialect, boolean shouldMatch) {
        // Arrange
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher(dialect);
        String line = "# " + keyword + ": hello";
        Token token = new Token(new GherkinLine(line, 1), new Location(1, 1));

        // Act
        boolean result = matcher.match_FeatureLine(token);

        // Assert
        assertEquals(shouldMatch, result,
                String.format("'%s' should%s match as feature in dialect '%s'",
                        line, shouldMatch ? "" : " not", dialect));
    }

    @Test
    void testInvalidDialect() {
        assertThrows(NullPointerException.class, () -> {
            new GherkinInMarkdownTokenMatcher("xx");
        });
    }

    @Test
    void testMatchEOF() {
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher("en");
        Token token = new Token(null, new Location(1, 0));
        assertTrue(matcher.match_EOF(token), "Should match EOF when line is empty");
    }

    @Test
    void testMatchNonEOF() {
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher("en");
        Token token = new Token(new GherkinLine("hello", 1), new Location(1, 1));
        assertFalse(matcher.match_EOF(token), "Is not EOF");
    }

    @ParameterizedTest(name = "step ''{0}'' should match: {1}")
    @MethodSource("stepLineTestCases")
    void testMatchStepLine(String line, boolean shouldMatch, String expectedKeyword, String expectedText) {
        // Arrange
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher("en");
        Token token = new Token(new GherkinLine(line, 1), new Location(1, 1));

        // Act
        boolean result = matcher.match_StepLine(token);

        // Assert
        assertEquals(shouldMatch, result,
                String.format("Line '%s' should%s match a step", line, shouldMatch ? "" : " not"));
        if (shouldMatch) {
            assertEquals(TokenType.StepLine, token.matchedType);
            assertEquals(expectedKeyword, token.matchedKeyword);
            assertEquals(expectedText, token.matchedText);
            assertEquals("en", token.matchedGherkinDialect.getLanguage());
        }
    }

    @ParameterizedTest(name = "table row ''{0}'' should match: {1}")
    @MethodSource("tableRowTestCases")
    void testMatchTableRow(String line, boolean shouldMatch, List<String> expectedCells) {
        // Arrange
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher("en");
        Token token = new Token(new GherkinLine(line, 1), new Location(1, 1));

        // Act
        boolean result = matcher.match_TableRow(token);

        // Assert
        assertEquals(shouldMatch, result,
                String.format("Line '%s' should%s match a table row", line, shouldMatch ? "" : " not"));
        if (shouldMatch) {
            assertEquals(TokenType.TableRow, token.matchedType);
            assertNotNull(token.matchedItems, "Table cells should not be null");
            List<String> actualCells = token.matchedItems.stream()
                    .map(item -> item.text)
                    .collect(Collectors.toList());
            assertEquals(expectedCells, actualCells, "Table cells should match");
        }
    }

    @ParameterizedTest(name = "line ''{0}'' should match empty: {1}")
    @MethodSource("emptyLineTestCases")
    void testMatchEmpty(String line, boolean shouldMatch) {
        // Arrange
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher("en");
        Token token = new Token(line != null ? new GherkinLine(line, 1) : null, new Location(1, 1));

        // Act
        boolean result = matcher.match_Empty(token);

        // Assert
        assertEquals(shouldMatch, result,
                String.format("Line '%s' should%s match empty",
                        line == null ? "null" : "'" + line + "'",
                        shouldMatch ? "" : " not"));
        if (shouldMatch) {
            assertEquals(TokenType.Empty, token.matchedType);
        }
    }

    @ParameterizedTest(name = "tag line ''{0}'' should match: {1}")
    @MethodSource("tagLineTestCases")
    void testMatchTagLine(String line, boolean shouldMatch, List<String> expectedTags) {
        // Arrange
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher("en");
        Token token = new Token(line != null ? new GherkinLine(line, 1) : null, new Location(1, 1));

        // Act
        boolean result = matcher.match_TagLine(token);

        // Assert
        assertEquals(shouldMatch, result,
                String.format("Line '%s' should%s match tags",
                        line == null ? "null" : "'" + line + "'",
                        shouldMatch ? "" : " not"));
        if (shouldMatch) {
            assertEquals(TokenType.TagLine, token.matchedType);
            assertNotNull(token.matchedItems, "Tags should not be null");
            List<String> actualTags = token.matchedItems.stream()
                    .map(item -> item.text)
                    .collect(Collectors.toList());
            assertEquals(expectedTags, actualTags, "Tags should match");
        }
    }

    @ParameterizedTest(name = "language line ''{0}'' should match: {1}")
    @MethodSource("languageLineTestCases")
    void testMatchLanguage(String line, boolean shouldMatch, String expectedLanguage) {
        // Arrange
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher("en");
        Token token = new Token(line != null ? new GherkinLine(line, 1) : null, new Location(1, 1));

        // Act
        boolean result = matcher.match_Language(token);

        // Assert
        assertEquals(shouldMatch, result,
                String.format("Line '%s' should%s match language",
                        line == null ? "null" : "'" + line + "'",
                        shouldMatch ? "" : " not"));
        if (shouldMatch) {
            assertEquals(TokenType.Language, token.matchedType);
            assertEquals(expectedLanguage, token.matchedText);
        }
    }

    @Test
    void testDocStringSeparatorSequence() {
        // Arrange
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher("en");

        // Test opening separator
        Token openingToken = new Token(new GherkinLine("```", 1), new Location(1, 1));
        boolean openingResult = matcher.match_DocStringSeparator(openingToken);
        assertTrue(openingResult, "Opening separator should match");
        assertEquals(TokenType.DocStringSeparator, openingToken.matchedType);
        assertEquals("", openingToken.matchedText);

        // Test content line (should not match)
        Token contentToken = new Token(new GherkinLine("some content", 2), new Location(2, 1));
        boolean contentResult = matcher.match_DocStringSeparator(contentToken);
        assertFalse(contentResult, "Content line should not match as separator");

        // Test closing separator
        Token closingToken = new Token(new GherkinLine("```", 3), new Location(3, 1));
        boolean closingResult = matcher.match_DocStringSeparator(closingToken);
        assertTrue(closingResult, "Closing separator should match");
        assertEquals(TokenType.DocStringSeparator, closingToken.matchedType);
        assertEquals(null, closingToken.matchedText);
    }

    @ParameterizedTest(name = "docstring separator ''{0}'' should match: {1}")
    @MethodSource("docStringSeparatorTestCases")
    void testMatchDocStringSeparator(String line, boolean shouldMatch, String expectedContentType) {
        // Arrange
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher("en");
        Token token = new Token(line != null ? new GherkinLine(line, 1) : null, new Location(1, 1));

        // Act
        boolean result = matcher.match_DocStringSeparator(token);

        // Assert
        assertEquals(shouldMatch, result,
                String.format("Line '%s' should%s match doc string separator",
                        line == null ? "null" : "'" + line + "'",
                        shouldMatch ? "" : " not"));
        if (shouldMatch) {
            assertEquals(TokenType.DocStringSeparator, token.matchedType);
            assertEquals(expectedContentType, token.matchedText);
        }
    }

    @ParameterizedTest(name = "other line ''{0}'' with indent to remove {1} should match with text: {2}")
    @MethodSource("otherLineTestCases")
    void testMatchOther(String line, int indentToRemove, String expectedText) {
        // Arrange
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher("en");
        Token token = new Token(line != null ? new GherkinLine(line, 1) : null, new Location(1, 1));

        // Set indentToRemove via DocString sequence if needed
        if (indentToRemove > 0) {
            // First match the DocString start to set indentToRemove
            Token docStart = new Token(new GherkinLine("   ```", 1), new Location(1, 1));
            matcher.match_DocStringSeparator(docStart);
        }

        // Act
        boolean result = matcher.match_Other(token);

        // Assert
        if (line != null) {
            assertTrue(result, "Should match any non-null line");
            assertEquals(TokenType.Other, token.matchedType);
            assertEquals(expectedText, token.matchedText);
            assertEquals(0, token.matchedIndent);
        } else {
            assertFalse(result, "Should not match null line");
        }
    }

    @ParameterizedTest(name = "comment line ''{0}'' should match: {1}")
    @MethodSource("commentLineTestCases")
    void testMatchComment(String line, boolean shouldMatch, String expectedText) {
        // Arrange
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher("en");
        Token token = new Token(line != null ? new GherkinLine(line, 1) : null, new Location(1, 1));

        // Act
        boolean result = matcher.match_Comment(token);

        // Assert
        assertEquals(shouldMatch, result,
                String.format("Line '%s' should%s match comment",
                        line == null ? "null" : "'" + line + "'",
                        shouldMatch ? "" : " not"));
        if (shouldMatch) {
            assertEquals(TokenType.Comment, token.matchedType);
            assertEquals(expectedText, token.matchedText);
        }
    }

    private static Stream<Arguments> stepLineTestCases() {
        return Stream.of(
                // Valid Given steps
                Arguments.of("* Given there is a test", true, "Given ", "there is a test"),
                Arguments.of("- Given I have a step", true, "Given ", "I have a step"),
                Arguments.of("+ Given some precondition", true, "Given ", "some precondition"),

                // Valid When steps
                Arguments.of("* When something happens", true, "When ", "something happens"),
                Arguments.of("- When I do an action", true, "When ", "I do an action"),
                Arguments.of("+ When executing the test", true, "When ", "executing the test"),

                // Valid Then steps
                Arguments.of("* Then I see results", true, "Then ", "I see results"),
                Arguments.of("- Then I verify outcome", true, "Then ", "I verify outcome"),
                Arguments.of("+ Then something is done", true, "Then ", "something is done"),

                // Valid And steps
                Arguments.of("* And another condition", true, "And ", "another condition"),
                Arguments.of("- And one more thing", true, "And ", "one more thing"),

                // Valid But steps
                Arguments.of("* But there is an exception", true, "But ", "there is an exception"),
                Arguments.of("- But something else", true, "But ", "something else"),

                // Valid with indentation
                Arguments.of("  * Given indented step", true, "Given ", "indented step"),
                Arguments.of("\t- When tabbed step", true, "When ", "tabbed step"),

                // Valid * steps
                Arguments.of("* * indented step", true, "* ", "indented step"),

                // Invalid cases
                Arguments.of("Given no bullet point", false, null, null),
                Arguments.of("* given lowercase keyword", false, null, null),
                Arguments.of("*  extra space after * ", false, null, null),
                Arguments.of("* Invalid keyword", false, null, null),
                Arguments.of("** Given double asterisk", false, null, null),
                Arguments.of("*Given no space after bullet", false, null, null),
                Arguments.of("* ", false, null, null), // Empty step
                Arguments.of("", false, null, null), // Empty line
                Arguments.of("Some random text", false, null, null) // No keyword
        );
    }

    private static Stream<Arguments> headerLineTestCases() {
        return Stream.of(HeaderType.values()).filter(headerType -> headerType != HeaderType.FEATURE)
                .flatMap(headerType -> Stream.of(
                        // Valid cases
                        Arguments.of(headerType, "# " + headerType.keyword + ": hello", true, headerType.tokenType,
                                headerType.keyword, "hello", 2),
                        Arguments.of(headerType, "# " + headerType.keyword + ": hello", true, headerType.tokenType,
                                headerType.keyword, "hello", 2),
                        Arguments.of(headerType, "## " + headerType.keyword + ": hello", true, headerType.tokenType,
                                headerType.keyword, "hello", 3),
                        Arguments.of(headerType, "### " + headerType.keyword + ": hello", true, headerType.tokenType,
                                headerType.keyword, "hello", 4),
                        Arguments.of(headerType, "#### " + headerType.keyword + ": hello", true, headerType.tokenType,
                                headerType.keyword, "hello", 5),
                        Arguments.of(headerType, "##### " + headerType.keyword + ": hello", true, headerType.tokenType,
                                headerType.keyword, "hello", 6),
                        Arguments.of(headerType, "###### " + headerType.keyword + ": hello", true, headerType.tokenType,
                                headerType.keyword, "hello", 7),
                        // Test cases for testing indentations
                        Arguments.of(headerType, "  # " + headerType.keyword + ": indentation with spaces", true,
                                headerType.tokenType, headerType.keyword, "indentation with spaces", 2),
                        Arguments.of(headerType, "\t# " + headerType.keyword + ": indentation with tabs", true,
                                headerType.tokenType, headerType.keyword, "indentation with tabs", 2),
                        Arguments.of(headerType, "  \t  # " + headerType.keyword + ": mixed indentation with spaces",
                                true,
                                headerType.tokenType, headerType.keyword, "mixed indentation with spaces", 2),
                        Arguments.of(headerType,
                                "  ## " + headerType.keyword + ": indentation with different header level",
                                true, headerType.tokenType, headerType.keyword,
                                "indentation with different header level", 3),

                        // Invalid cases
                        Arguments.of(headerType, "" + headerType.keyword + ": Missing header", false, null, null, null,
                                null), // Missing
                                       // header
                        Arguments.of(headerType, "####### " + headerType.keyword + ": too many #s", false, null, null,
                                null,
                                null), // Too many #s
                        Arguments.of(headerType, "#" + headerType.keyword + ": Missing space after #", false, null,
                                null, null,
                                null), // No space after #
                        Arguments.of(headerType, "#  " + headerType.keyword + ": Extra space after #", false, null,
                                null, null,
                                null), // Extra after #
                        Arguments.of(headerType, "# " + headerType.keyword.toLowerCase() + ": lower case feature",
                                false, null,
                                null, null, null), // lowercase 'feature'
                        Arguments.of(headerType, "# " + headerType.keyword + "s: plural", false, null, null, null,
                                null), // Plural
                        Arguments.of(headerType, "# Something: wrong keyword", false, null, null, null, null), // Wrong
                                                                                                               // keyword
                        Arguments.of(headerType, "#", false, null, null, null, null), // Just a hash
                        Arguments.of(headerType, "Mising keyword", false, null, null, null, null) // No feature line at
                                                                                                  // all

                ));

    }

    private static Stream<Arguments> featureDialectTestCases() {
        return Stream.of(
                // English
                Arguments.of("Feature", "en", true),
                // French
                Arguments.of("Fonctionnalité", "fr", true),
                Arguments.of("Feature", "fr", true),
                // Spanish
                Arguments.of("Característica", "es", true),
                Arguments.of("Feature", "es", true));
    }

    private static Stream<Arguments> tableRowTestCases() {
        return Stream.of(
                // Valid table rows
                Arguments.of("  | header1 | header2 |", true, Arrays.asList("header1", "header2")),
                Arguments.of("   |col1|col2|", true, Arrays.asList("col1", "col2")),
                Arguments.of("    | data 1 | data 2 |", true, Arrays.asList("data 1", "data 2")),
                Arguments.of("     |   spaced   |   cells   |", true, Arrays.asList("spaced", "cells")),

                // Valid with indentation
                Arguments.of("  | indented | row |", true, Arrays.asList("indented", "row")),
                Arguments.of("\t\t| tabbed | row |", true, Arrays.asList("tabbed", "row")),

                // Valid empty cells
                Arguments.of("  | | empty cell |", true, Arrays.asList("", "empty cell")),
                Arguments.of("  | cell | |", true, Arrays.asList("cell", "")),
                Arguments.of("  |||", true, Arrays.asList("", "")),

                // Invalid table rows less 2 or greater than 5 spaces indenting
                Arguments.of(" | header1 | header2 |", false, null),
                Arguments.of("|col1|col2|", false, null),
                Arguments.of("      |   spaced   |   cells   |", false, null),
                // Invalid cases
                Arguments.of("not a table row", false, null),
                Arguments.of("|incomplete", false, null),
                Arguments.of("incomplete|", false, null),
                Arguments.of("", false, null),
                Arguments.of("|", false, null),
                Arguments.of("||", false, null) // Requires at least one character between pipes

        );
    }

    private static Stream<Arguments> emptyLineTestCases() {
        return Stream.of(
                // Valid empty lines
                Arguments.of("", true),
                Arguments.of(" ", true),
                Arguments.of("   ", true),
                Arguments.of("\t", true),
                Arguments.of(" \t ", true),

                // Invalid cases (non-empty lines)
                Arguments.of("not empty", false),
                Arguments.of("  text  ", false),
                Arguments.of("\ttext", false),
                Arguments.of("# Heading", false),
                Arguments.of("* bullet", false),
                Arguments.of("|table|", false),
                Arguments.of(null, false));
    }

    private static Stream<Arguments> tagLineTestCases() {
        return Stream.of(
                // Valid tag lines
                Arguments.of("`@tag`", true, Arrays.asList("@tag")),
                Arguments.of("`@tag1` `@tag2`", true, Arrays.asList("@tag1", "@tag2")),
                Arguments.of("`@feature` `@important` `@test`", true, Arrays.asList("@feature", "@important", "@test")),

                // Valid with indentation
                Arguments.of("   `@tag`", true, Arrays.asList("@tag")),
                Arguments.of("\t`@tag`", true, Arrays.asList("@tag")),
                Arguments.of("  `@tag1`   `@tag2`  ", true, Arrays.asList("@tag1", "@tag2")),

                // Valid complex tags
                Arguments.of("`@with.dot`", true, Arrays.asList("@with.dot")),
                Arguments.of("`@with_underscore`", true, Arrays.asList("@with_underscore")),
                Arguments.of("`@with-dash`", true, Arrays.asList("@with-dash")),
                Arguments.of("`@with123`", true, Arrays.asList("@with123")),

                // Valid with separated tags
                Arguments.of("`@tag1`,`@tag2`", true, Arrays.asList("@tag1", "@tag2")),
                Arguments.of("`@tag#invalid`", true, Arrays.asList("@tag#invalid")),

                // Invalid cases
                Arguments.of("@tag", false, null), // Missing backticks
                Arguments.of("`@tag", false, null), // Missing closing backtick
                Arguments.of("@tag`", false, null), // Missing opening backtick
                Arguments.of("`@ invalid`", false, null), // Invalid tag format
                Arguments.of("`@`", false, null), // Just @ symbol
                Arguments.of("` @tag `", false, null), // Space after backtick
                Arguments.of("not a tag", false, null),
                Arguments.of("", false, null),
                Arguments.of(null, false, null),
                Arguments.of("`#@tag`", false, null) // Must start with @
        );
    }

    private static Stream<Arguments> languageLineTestCases() {
        return Stream.of(
                // Valid language lines
                Arguments.of("# language: en", true, "en"),
                Arguments.of("# language: fr", true, "fr"),
                Arguments.of("# language: es", true, "es"),
                Arguments.of("#language:pt", true, "pt"), // No spaces

                // Valid with indentation
                Arguments.of("   # language: de", true, "de"),
                Arguments.of("\t# language: nl", true, "nl"),

                // Invalid cases
                Arguments.of("# Language: en", false, null), // Capital L
                Arguments.of("#language en", false, null), // Missing colon
                Arguments.of("# language:", false, null), // Missing language code
                Arguments.of("# language: ", false, null), // Empty language code
                Arguments.of("language: en", false, null), // Missing #
                Arguments.of("# something: en", false, null), // Wrong keyword
                Arguments.of("", false, null),
                Arguments.of(null, false, null));
    }

    private static Stream<Arguments> docStringSeparatorTestCases() {
        return Stream.of(
                // Valid separators
                Arguments.of("```", true, ""), // Basic separator
                Arguments.of("  ```  ", true, ""), // Extra spaces
                Arguments.of("`````", true, ""), // More than 3 backticks

                // Invalid cases
                Arguments.of("``", false, null), // Too few backticks
                Arguments.of("~~~", false, null), // Wrong characters
                Arguments.of("``` python", false, null), // Space after backticks
                Arguments.of("```python script", false, null), // Space in content type
                Arguments.of("", false, null), // Empty line
                Arguments.of(null, false, null) // Null line
        );
    }

    private static Stream<Arguments> otherLineTestCases() {
        return Stream.of(
                // Basic text lines
                Arguments.of("Simple text", 0, "Simple text"),
                Arguments.of("  Indented text", 0, "  Indented text"),
                Arguments.of("\tTabbed text", 0, "\tTabbed text"),

                // DocString content (with indentToRemove)
                Arguments.of("   Some content", 3, "Some content"),
                Arguments.of("     More content", 3, "  More content"),
                Arguments.of("  Less content", 3, "Less content"),

                // Special characters
                Arguments.of("Text with * asterisk", 0, "Text with * asterisk"),
                Arguments.of("Text with # hash", 0, "Text with # hash"),
                Arguments.of("Text with ``` backticks", 0, "Text with ``` backticks"),

                // Edge cases
                Arguments.of("", 0, ""),
                Arguments.of("   ", 0, "   "),
                Arguments.of(null, 0, null));
    }

    private static Stream<Arguments> commentLineTestCases() {
        return Stream.of(
                // Valid GFM table separators - Basic
                Arguments.of("| --- |", true, "| --- |"),
                Arguments.of("| --- | --- |", true, "| --- | --- |"),
                Arguments.of("|---|---|", true, "|---|---|"),

                // Valid GFM table separators - Alignment syntax
                Arguments.of("|:---|", true, "|:---|"), // Left align
                Arguments.of("|---:|", true, "|---:|"), // Right align
                Arguments.of("|:---:|", true, "|:---:|"), // Center align
                Arguments.of("|:--- |:--- |", true, "|:--- |:--- |"), // Multiple columns
                Arguments.of("| :---: | :---: |", true, "| :---: | :---: |"),

                // Valid with different dash counts
                Arguments.of("| ---- |", true, "| ---- |"), // More dashes
                Arguments.of("| - |", true, "| - |"), // Single dash

                // Valid with indentation
                Arguments.of("  | --- |", true, "  | --- |"),
                Arguments.of("\t| --- |", true, "\t| --- |"),

                // Invalid cases
                Arguments.of("| abc |", false, null), // Not a separator
                Arguments.of("| --- abc |", false, null), // Mixed content
                Arguments.of("| -- - |", false, null), // Broken separator
                Arguments.of("| :-- : |", false, null), // Invalid alignment
                Arguments.of("|", false, null), // Just pipe
                Arguments.of("---", false, null), // No pipes
                Arguments.of("# Comment", false, null), // Regular comment
                Arguments.of("", false, null), // Empty line
                Arguments.of(null, false, null), // Null line

                // Edge cases
                Arguments.of("| :---: | abc |", false, null), // Mixed separator and content
                Arguments.of("| --- || --- |", false, null), // Double pipe
                Arguments.of("|::---|", false, null), // Multiple colons
                Arguments.of("| ---- :", false, null) // Missing end pipe

        );
    }
}