package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import java.util.Map.Entry;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

class StringUtilsTest {
    private static final String WHITESPACE = "\u00A0 \t";
    private static final String CUCUMBER = "🥒";

    @Test
    void rtrim() {
        assertEquals(WHITESPACE + CUCUMBER, StringUtils.rtrim(WHITESPACE + CUCUMBER + WHITESPACE));
    }

    @Test
    void rtrim_one_space() {
        assertEquals("", StringUtils.rtrim(" "));
    }

    @Test
    void rtrim_multiline() {
        assertEquals("\n" + WHITESPACE + "\n" + WHITESPACE + CUCUMBER, StringUtils.rtrim("\n" + WHITESPACE + "\n" + WHITESPACE + CUCUMBER + WHITESPACE + "\n" + WHITESPACE + "\n"));
    }

    @Test
    void trimAndIndent() {
        // When
        Entry<String, Integer> trimmedIndent = StringUtils.trimAndIndent(WHITESPACE + CUCUMBER + WHITESPACE);

        // Then
        assertEquals(CUCUMBER, trimmedIndent.getKey());
        assertEquals(WHITESPACE.codePointCount(0, WHITESPACE.length()), trimmedIndent.getValue());
    }

    @Test
    void trimAndIndent_multiline() {
        // When
        Entry<String, Integer> trimmedIndent = StringUtils.trimAndIndent("\n" + WHITESPACE + "\n" + WHITESPACE + CUCUMBER + WHITESPACE + "\n" + WHITESPACE + "\n");

        // Then
        assertEquals(CUCUMBER, trimmedIndent.getKey());
        assertEquals(2 + 2 * WHITESPACE.codePointCount(0, WHITESPACE.length()), trimmedIndent.getValue());
    }

    @Test
    void trimAndIndent_empty() {
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

    @Test
    void isWhiteSpace() {
        char[] whitespace = new char[]{
                '\t',
                '\n',
                '\u000B',
                '\f',
                '\r',
                ' ',
                '\u0085',
                '\u00A0',
                '\u1680',
                '\u2000',
                '\u2001',
                '\u2002',
                '\u2003',
                '\u2004',
                '\u2005',
                '\u2006',
                '\u2007',
                '\u2008',
                '\u2009',
                '\u200A',
                '\u2028',
                '\u2029',
                '\u202F',
                '\u205F',
                '\u3000'
        };

        for (char c : whitespace) {
            assertTrue(StringUtils.isWhiteSpace(c), Character.getName(c) + " was not whitespace");
        }
    }

}
