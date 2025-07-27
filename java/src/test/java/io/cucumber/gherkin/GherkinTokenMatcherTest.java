package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertTrue;

class GherkinTokenMatcherTest {

    @Test
    void each_language_must_have_at_least_6_keywords_for_unrolling() {
        GherkinDialects.DIALECTS.forEach((language, dialect) -> {
            assertTrue(dialect.getStepKeywords().size() >= 6,
                    "Language '" + language + "' must have at least 6 keywords for unrolling, but has " + dialect.getStepKeywords().size());
        });
    }

    @Test
    void match_Language_change_the_language() {
        // Given
        GherkinTokenMatcher matcher = new GherkinTokenMatcher("en");
        matcher.match_Language(Token.createGherkinLine("# language: ht", Locations.atLine(1)));

        // When
        boolean isStepLine = matcher.match_StepLine(Token.createGherkinLine("    Le sa a there should be agent J", Locations.atLine(2)));

        // Then
        assertTrue(isStepLine, "Expected step line to match with language 'ht'");
    }
}