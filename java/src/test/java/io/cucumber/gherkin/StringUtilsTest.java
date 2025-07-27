package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

class StringUtilsTest {
    private static final String WHITESPACE = "\u00A0 \t";
    private static final String CUCUMBER = "🥒";

    @Test
    void trimAndIndent() {
        // When
        StringUtils.IndentedText trimmedIndent = StringUtils.trimAndIndent(WHITESPACE + CUCUMBER + WHITESPACE);

        // Then
        assertEquals(CUCUMBER, trimmedIndent.getText());
        assertEquals(WHITESPACE.codePointCount(0, WHITESPACE.length()), trimmedIndent.getIndent());
    }

    @Test
    void trimAndIndent_multiline() {
        // When
        StringUtils.IndentedText trimmedIndent = StringUtils.trimAndIndent("\n" + WHITESPACE + "\n" + WHITESPACE + CUCUMBER + WHITESPACE + "\n" + WHITESPACE + "\n");

        // Then
        assertEquals(CUCUMBER, trimmedIndent.getText());
        assertEquals(2 + 2 * WHITESPACE.codePointCount(0, WHITESPACE.length()), trimmedIndent.getIndent());
    }

    @Test
    void trimAndIndent_empty() {
        // When
        StringUtils.IndentedText trimmedIndent = StringUtils.trimAndIndent("");

        // Then
        assertEquals("", trimmedIndent.getText());
        assertEquals(0, trimmedIndent.getIndent());
    }

}
