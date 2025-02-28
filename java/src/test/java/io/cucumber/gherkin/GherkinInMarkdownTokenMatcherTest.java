package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import java.util.stream.Stream;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import io.cucumber.gherkin.Parser.TokenType;

class GherkinInMarkdownTokenMatcherTest {

    @ParameterizedTest(name = "line ''{0}'' should match: {1}")
    @MethodSource("featureLineTestCases")
    void testFeatureLineMatching(String line, boolean shouldMatch, TokenType expectedType, String expectedKeyword, String expectedText, Integer expectedIndent) {
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher("en");
        Token token = new Token(new GherkinLine(line, 1), new Location(1, 1));

        boolean result = matcher.matchFeatureLine(token);

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
        boolean result = matcher.matchFeatureLine(token);

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

    private static Stream<Arguments> featureLineTestCases() {
        return Stream.of(
                // Valid cases
                Arguments.of("# Feature: hello", true, TokenType.FeatureLine, "Feature", "hello", 2),
                Arguments.of("## Feature: hello", true, TokenType.FeatureLine, "Feature", "hello", 3),
                Arguments.of("### Feature: hello", true, TokenType.FeatureLine, "Feature", "hello", 4),
                Arguments.of("#### Feature: hello", true, TokenType.FeatureLine, "Feature", "hello", 5),
                Arguments.of("##### Feature: hello", true, TokenType.FeatureLine, "Feature", "hello", 6),
                Arguments.of("###### Feature: hello", true, TokenType.FeatureLine, "Feature", "hello", 7),

                // Test cases for testing indentations
                Arguments.of("  # Feature: indentation with spaces", true, TokenType.FeatureLine, "Feature", "indentation with spaces", 2),
                Arguments.of("\t# Feature: indentation with tabs", true, TokenType.FeatureLine, "Feature", "indentation with tabs", 2),
                Arguments.of("  \t  # Feature: mixed indentation with spaces", true, TokenType.FeatureLine, "Feature", "mixed indentation with spaces", 2),
                Arguments.of("  ## Feature: indentation with different header level", true, TokenType.FeatureLine, "Feature", "indentation with different header level", 3),

                // Invalid cases
                Arguments.of("Feature: Missing header", false, null, null, null, null ), // Missing header
                Arguments.of("####### Feature: too many #s", false, null, null, null, null), // Too many #s
                Arguments.of("#Feature: Missing space after #", false, null, null, null, null), // No space after #
                Arguments.of("#  Feature: Extra space after #", false, null, null, null, null), // Extra after #
                Arguments.of("# feature: lower case feature", false, null, null, null, null), // lowercase 'feature'
                Arguments.of("# Features: plural", false, null, null, null, null), // Plural
                Arguments.of("# Something: wrong keyword", false, null, null, null, null), // Wrong keyword
                Arguments.of("#", false, null, null, null, null), // Just a hash
                Arguments.of("Mising keyword", false, null, null, null, null) // No feature line at all
        );
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