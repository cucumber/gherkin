package io.cucumber.gherkin;

import org.junit.jupiter.api.Disabled;
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
    void testRtrim_multiline() {
        assertEquals("\n" + WHITESPACE + "\n" + WHITESPACE + CUCUMBER,
                StringUtils.rtrim("\n" + WHITESPACE + "\n" + WHITESPACE + CUCUMBER + WHITESPACE + "\n" + WHITESPACE + "\n"));
    }

    @Test
    void testRtrimKeepNewlines() {
        assertEquals(WHITESPACE + CUCUMBER + "\n", StringUtils.rtrimKeepNewLines(WHITESPACE + CUCUMBER + "\n" + WHITESPACE));
    }

    @Test
    void testLtrim() {
        assertEquals(CUCUMBER + WHITESPACE, StringUtils.ltrim(WHITESPACE + CUCUMBER + WHITESPACE));
    }

    @Test
    void testLtrim_multiline() {
        assertEquals(CUCUMBER + WHITESPACE + "\n" + WHITESPACE + "\n",
                StringUtils.ltrim("\n" + WHITESPACE + "\n" + WHITESPACE + CUCUMBER + WHITESPACE + "\n" + WHITESPACE + "\n"));
    }

    @Test
    void testLtrimKeepNewlines() {
        assertEquals("\n" + CUCUMBER + WHITESPACE, StringUtils.ltrimKeepNewLines(WHITESPACE + "\n" + CUCUMBER + WHITESPACE));
    }

    @Test
    void testTrim() {
        assertEquals(CUCUMBER, StringUtils.trim(WHITESPACE + CUCUMBER + WHITESPACE));
    }

    @Test
    void testTrim_multiline() {
        assertEquals(CUCUMBER,
                StringUtils.trim("\n" + WHITESPACE + "\n" + WHITESPACE + CUCUMBER + WHITESPACE + "\n" + WHITESPACE + "\n"));
    }

    @Test
    void testTrim_empty() {
        assertEquals("",
                StringUtils.trim(""));
    }
}
