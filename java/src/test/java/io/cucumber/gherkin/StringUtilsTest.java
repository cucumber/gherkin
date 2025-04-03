package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class StringUtilsTest {
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
        assertEquals("\n" + WHITESPACE + "\n" + WHITESPACE + CUCUMBER,
                StringUtils.rtrim("\n" + WHITESPACE + "\n" + WHITESPACE + CUCUMBER + WHITESPACE + "\n" + WHITESPACE + "\n"));
    }

    @Test
    void testTrimAndIndent() {
        // Given
        MockIndentable trimmable = new MockIndentable();

        // When
        StringUtils.trimAndIndent(WHITESPACE + CUCUMBER + WHITESPACE, trimmable);

        // Then
        assertEquals(CUCUMBER, trimmable.trimmed);
        assertEquals(WHITESPACE.codePointCount(0, WHITESPACE.length()), trimmable.indent);
    }

    @Test
    void testTrimAndIndent_multiline() {
        // Given
        MockIndentable trimmable = new MockIndentable();

        // When
        StringUtils.trimAndIndent("\n" + WHITESPACE + "\n" + WHITESPACE + CUCUMBER + WHITESPACE + "\n" + WHITESPACE + "\n", trimmable);

        // Then
        assertEquals(CUCUMBER, trimmable.trimmed);
        assertEquals(2 + 2 * WHITESPACE.codePointCount(0, WHITESPACE.length()), trimmable.indent);
    }

    @Test
    void testTrimAndIndent_empty() {
        // Given
        MockIndentable trimmable = new MockIndentable();

        // When
        StringUtils.trimAndIndent("", trimmable);

        // Then
        assertEquals("", trimmable.trimmed);
        assertEquals(0, trimmable.indent);
    }


    @Test
    void testTrimAndIndent_null() {
        // Given
        MockIndentable trimmable = new MockIndentable();

        // When
        StringUtils.trimAndIndent(null, trimmable);

        // Then
        assertEquals("", trimmable.trimmed);
        assertEquals(0, trimmable.indent);
    }

    @Test
    void removeComments() {
        assertEquals("@this @is", StringUtils.removeComments("@this @is #@a @commented @sequence of tags"));
        assertEquals("@this @is @a @commented @sequence of tags", StringUtils.removeComments("@this @is @a @commented @sequence of tags #"));
        assertEquals("@this @is @a @commented @sequence of tags", StringUtils.removeComments("@this @is @a @commented @sequence of tags"));
    }

    private static class MockIndentable implements Indentable {
        int indent;
        String trimmed;

        @Override
        public void indent(int indent, String trimmed) {
            this.indent = indent;
            this.trimmed = trimmed;
        }
    }

}
