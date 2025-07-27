package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

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

    @Test
    void isWhitespace() {
        // https://en.wikipedia.org/wiki/Whitespace_character#Unicode
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
            assertTrue(StringUtils.isWhitespace(c), Character.getName(c) + " was not whitespace");
        }
    }

}
