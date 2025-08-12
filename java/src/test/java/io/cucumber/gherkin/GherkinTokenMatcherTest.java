package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertTrue;

class GherkinTokenMatcherTest {

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


    @Test
    void reset_after_match_Language_change_the_language() {
        // Given
        GherkinTokenMatcher matcher = new GherkinTokenMatcher("en");
        matcher.match_Language(Token.createGherkinLine("# language: ht", Locations.atLine(1)));
        matcher.reset();

        // When
        boolean isStepLine = matcher.match_StepLine(Token.createGherkinLine("    Given there should be agent J", Locations.atLine(2)));

        // Then
        assertTrue(isStepLine, "Expected step line to match with language 'en'");
    }
}
