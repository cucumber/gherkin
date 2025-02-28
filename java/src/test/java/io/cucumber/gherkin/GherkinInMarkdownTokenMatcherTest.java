package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import java.util.stream.Stream;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

class GherkinInMarkdownTokenMatcherTest {

    @ParameterizedTest(name = "line ''{0}'' should match: {1}")
    @MethodSource("featureLineTestCases")
    void testFeatureLineMatching(String line, boolean shouldMatch) {
        GherkinInMarkdownTokenMatcher matcher = new GherkinInMarkdownTokenMatcher("en");
        Token token = new Token(new GherkinLine(line, 1), new Location(1, 1));

        boolean result = matcher.matchFeatureLine(token);

        assertEquals(shouldMatch, result,
                String.format("Line '%s' should%s match a feature line",
                        line, shouldMatch ? "" : " not"));
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
                Arguments.of("# Feature: hello", true),
                Arguments.of("## Feature: hello", true),
                Arguments.of("### Feature: hello", true),
                Arguments.of("#### Feature: hello", true),
                Arguments.of("##### Feature: hello", true),
                Arguments.of("###### Feature: hello", true),

                // Test cases for testing indentations
                Arguments.of("  # Feature: indentation with spaces", true),
                Arguments.of("\t# Feature: indentation with tabs", true),
                Arguments.of("  \t  # Feature: mixed indentation with spaces", true),
                Arguments.of("  ## Feature: indentation with different header level", true),

                // Invalid cases
                Arguments.of("Feature: Missing header", false), // Missing header
                Arguments.of("####### Feature: too many #s", false), // Too many #s
                Arguments.of("#Feature: Missing space after #", false), // No space after #
                Arguments.of("#  Feature: Extra space after #", false), // Extra after #
                Arguments.of("# feature: lower case feature", false), // lowercase 'feature'
                Arguments.of("# Features: plural", false), // Plural
                Arguments.of("# Something: wrong keyword", false), // Wrong keyword
                Arguments.of("#", false), // Just a hash
                Arguments.of("Mising keyword", false) // No feature line at all
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