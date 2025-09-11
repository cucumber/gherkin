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
                /*
                 Misses four characters (from Unicode category "B"):
                    - FS (File Separator): Code point 28 (0x1C), used to separate files.
                    - GS (Group Separator): Code point 29 (0x1D), used to separate groups of records.
                    - RS (Record Separator): Code point 30 (0x1E), used to separate records within a file.
                    - US (Unit Separator): Code point 31 (0x1F), used to separate units of data or fields.
                */
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

    @Test
    void isWhitespace_contains_all_whitespaces_and_no_non_whitespace_chars() {
        for (char c = Character.MIN_VALUE; c < Character.MAX_VALUE; c++) {
            assertEquals(isCharacterTypeSpace(c) || isDirectionalitySpace(c), StringUtils.isWhitespace(c),
                    "Mismatch for char " + (int) c + " '" + c + "'");
        }
    }

    private static boolean isCharacterTypeSpace(char c) {
        return (((
                (1 << Character.SPACE_SEPARATOR)
                        // Not in the definition, but a subset of isDirectionalitySpace
                        | (1 << Character.LINE_SEPARATOR)
                        // Not in the definition, but a subset of isDirectionalitySpace
                        | (1 << Character.PARAGRAPH_SEPARATOR)
        ) >> Character.getType(c)) & 1) != 0;
    }

    private static boolean isDirectionalitySpace(char c) {
        return (
                (((1 << Character.DIRECTIONALITY_WHITESPACE)
                        | (1 << Character.DIRECTIONALITY_PARAGRAPH_SEPARATOR)
                        | (1 << Character.DIRECTIONALITY_SEGMENT_SEPARATOR)
                ) >> Character.getDirectionality(c)) & 1) != 0;
    }

}
