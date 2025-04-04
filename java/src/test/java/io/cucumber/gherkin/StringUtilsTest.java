package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import java.util.Map.Entry;

import static org.junit.jupiter.api.Assertions.assertEquals;

class StringUtilsTest {
    private static final String WHITESPACE = "\u00A0 \t";
    private static final String CUCUMBER = "🥒";

    @Test
    void testRtrim() {
        assertEquals(WHITESPACE + CUCUMBER, StringUtils.rtrim(WHITESPACE + CUCUMBER + WHITESPACE));
    }

    @Test
    void testRtrim_one_space() {
        assertEquals("", StringUtils.rtrim(" "));
    }

    @Test
    void testRtrim_multiline() {
        assertEquals("\n" + WHITESPACE + "\n" + WHITESPACE + CUCUMBER, StringUtils.rtrim("\n" + WHITESPACE + "\n" + WHITESPACE + CUCUMBER + WHITESPACE + "\n" + WHITESPACE + "\n"));
    }

    @Test
    void testTrimAndIndent() {
        // When
        Entry<String, Integer> trimmedIndent = StringUtils.trimAndIndent(WHITESPACE + CUCUMBER + WHITESPACE);

        // Then
        assertEquals(CUCUMBER, trimmedIndent.getKey());
        assertEquals(WHITESPACE.codePointCount(0, WHITESPACE.length()), trimmedIndent.getValue());
    }

    @Test
    void testTrimAndIndent_multiline() {
        // When
        Entry<String, Integer> trimmedIndent = StringUtils.trimAndIndent("\n" + WHITESPACE + "\n" + WHITESPACE + CUCUMBER + WHITESPACE + "\n" + WHITESPACE + "\n");

        // Then
        assertEquals(CUCUMBER, trimmedIndent.getKey());
        assertEquals(2 + 2 * WHITESPACE.codePointCount(0, WHITESPACE.length()), trimmedIndent.getValue());
    }

    @Test
    void testTrimAndIndent_empty() {
        // When
        Entry<String, Integer> trimmedIndent = StringUtils.trimAndIndent("");

        // Then
        assertEquals("", trimmedIndent.getKey());
        assertEquals(0, trimmedIndent.getValue());
    }

    @Test
    void removeComments() {
        assertEquals("", StringUtils.removeComments(""));
        assertEquals("@this @is", StringUtils.removeComments("@this @is #@a @commented @sequence of tags"));
        assertEquals("@this @is @a @sequence of tags", StringUtils.removeComments("@this @is @a @sequence of tags #with a comment"));
        assertEquals("@this @is @a @sequence of tags", StringUtils.removeComments("@this @is @a @sequence of tags"));
        assertEquals("@issue#1234 @issue#31415", StringUtils.removeComments("@issue#1234 @issue#31415"));
    }

}
