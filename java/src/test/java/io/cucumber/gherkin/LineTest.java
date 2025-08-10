package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

class LineTest {
    private static final String WHITESPACE = "\u00A0 \t";
    private static final String CUCUMBER = "🥒";

    @Test
    void startsWithTitleKeyword_corresponding_keyword_match() {
        // Given
        Line gherkinLine = new Line("Feature: Hello");

        // When/Then
        assertTrue(gherkinLine.startsWithTitleKeyword("Feature", "Feature".length()));
    }

    @Test
    void startsWithTitleKeyword_non_corresponding_keyword_does_not_match() {
        // Given
        Line gherkinLine = new Line("Rule: X");

        // When/Then
        assertFalse(gherkinLine.startsWithTitleKeyword("Background", "Background".length())); // not the same keyword
        assertFalse(gherkinLine.startsWithTitleKeyword("Rule: X", "Rule: X".length())); // same keyword but with colon
        assertFalse(gherkinLine.startsWithTitleKeyword("Rul", "Rul".length())); // shorter than keyword
    }

    @Test
    void startsWithTitleKeyword_keyword_without_colon_does_not_match() {
        // Given
        Line gherkinLine = new Line("Rule");

        // When/Then
        assertFalse(gherkinLine.startsWithTitleKeyword("Rule", "Rule".length()));
    }

    @Test
    void substringTrimmed_empty_idempotence() {
        // Given
        Line gherkinLine = new Line("");

        // When/Then
        assertEquals("", gherkinLine.substringTrimmed(0));
    }

    @Test
    void substringTrimmed_regular_spaces_after_index_are_trimmed() {
        // Given
        Line gherkinLine = new Line("Rule:    my rule name ");

        // When/Then
        assertEquals("my rule name", gherkinLine.substringTrimmed(5));
    }

    @Test
    void substringTrimmed_unicode_spaces_after_index_are_trimmed() {
        // Given
        Line gherkinLine = new Line("Rule:" + WHITESPACE + CUCUMBER + WHITESPACE);

        // When/Then
        assertEquals(CUCUMBER, gherkinLine.substringTrimmed(5));
    }

    @Test
    void getRawTextSubstring_substring_from_beginning() {
        // Given
        Line gherkinLine = new Line("    some text");

        // When/Then
        assertEquals("    some text", gherkinLine.getRawTextSubstring(0));
    }

    @Test
    void getRawTextSubstring_substring_from_middle() {
        // Given
        Line gherkinLine = new Line("    some text");

        // When/Then
        assertEquals(" some text", gherkinLine.getRawTextSubstring(3));
    }


}
