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
        assertThrows(ParserException.class, () -> {
            new GherkinInMarkdownTokenMatcher("xx");
        });
    }

    private static Stream<Arguments> headerLineTestCases() {
        return Stream.of(HeaderType.values()).flatMap(headerType -> Stream.of(
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
                Arguments.of(headerType, "  \t  # " + headerType.keyword + ": mixed indentation with spaces", true,
                        headerType.tokenType, headerType.keyword, "mixed indentation with spaces", 2),
                Arguments.of(headerType, "  ## " + headerType.keyword + ": indentation with different header level",
                        true, headerType.tokenType, headerType.keyword, "indentation with different header level", 3),

                // Invalid cases
                Arguments.of(headerType, "" + headerType.keyword + ": Missing header", false, null, null, null, null), // Missing
                                                                                                                       // header
                Arguments.of(headerType, "####### " + headerType.keyword + ": too many #s", false, null, null, null,
                        null), // Too many #s
                Arguments.of(headerType, "#" + headerType.keyword + ": Missing space after #", false, null, null, null,
                        null), // No space after #
                Arguments.of(headerType, "#  " + headerType.keyword + ": Extra space after #", false, null, null, null,
                        null), // Extra after #
                Arguments.of(headerType, "# " + headerType.keyword.toLowerCase() + ": lower case feature", false, null,
                        null, null, null), // lowercase 'feature'
                Arguments.of(headerType, "# " + headerType.keyword + "s: plural", false, null, null, null, null), // Plural
                Arguments.of(headerType, "# Something: wrong keyword", false, null, null, null, null), // Wrong keyword
                Arguments.of(headerType, "#", false, null, null, null, null), // Just a hash
                Arguments.of(headerType, "Mising keyword", false, null, null, null, null) // No feature line at all

        ));

    }

    private static Stream<Arguments> featureDialectTestCases() {
        return Stream.of(
                // English
                Arguments.of("Feature", "en", true),
                // French
                Arguments.of("Fonctionnalité", "fr", true),
                Arguments.of("Feature", "fr", false),
                // Spanish
                Arguments.of("Característica", "es", true),
                Arguments.of("Feature", "es", false));
    }
}