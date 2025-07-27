package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import java.util.List;
import java.util.stream.Collectors;

import static java.util.Arrays.asList;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

class GherkinLineTest {
    private static final String WHITESPACE = "\u00A0 \t";
    private static final String CUCUMBER = "🥒";

    @Test
    void finds_table_cells() {
        // The cells below has the following whitespace characters on each side:
        // - U+00A0 (non-breaking space)
        // - U+0020 (space)
        // - U+0009 (tab)
        // This is generated with `ruby -e 'STDOUT.write "\u00A0\u0020\u0009".encode("utf-8")' | pbcopy`
        // and pasted.
        GherkinLine gherkinLine = new GherkinLine("      |  \tred  \t|  \tblue  \t|  \t\uD83E\uDD52\uD83E\uDD52\uD83E\uDD52  \t|  \tgreen  \t|");

        List<GherkinLineSpan> tableCells = gherkinLine.parseTableCells();
        GherkinLineSpan redSpan = tableCells.get(0);
        GherkinLineSpan blueSpan = tableCells.get(1);
        GherkinLineSpan emojiSpan = tableCells.get(2);
        GherkinLineSpan greenSpan = tableCells.get(3);

        assertEquals("red", redSpan.text);
        assertEquals(11, redSpan.column);

        assertEquals("blue", blueSpan.text);
        assertEquals(21, blueSpan.column);

        assertEquals("\uD83E\uDD52\uD83E\uDD52\uD83E\uDD52", emojiSpan.text);
        assertEquals(32, emojiSpan.column);

        assertEquals("green", greenSpan.text);
        assertEquals(42, greenSpan.column);
    }

    @Test
    void finds_escaped_table_cells() {
        GherkinLine gherkinLine = new GherkinLine("      | \\|æ\\\\n     | \\o\\no\\  | \\\\\\|a\\\\\\\\n | ø\\\\\\nø\\\\|");

        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("|æ\\n", "\\o\no\\", "\\|a\\\\n", "ø\\\nø\\"), texts);
    }

    @Test
    void preserve_escaped_new_lines_at_start_and_end() {
        GherkinLine gherkinLine = new GherkinLine("      |  \nraindrops--\nher last kiss\ngoodbye.\n  |");
        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("" +
                "\n" +
                "raindrops--\n" +
                "her last kiss\n" +
                "goodbye.\n"
        ), texts);
    }

    @Test
    void escapes_backslash() {
        GherkinLine gherkinLine = new GherkinLine("|\\\\o\\no\\||");
        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("\\o\no|"), texts);
    }

    @Test
    void throws_on_illegal_escapes_backslash() {
        GherkinLine gherkinLine = new GherkinLine("|\\o\\no\\||");
        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("\\o\no|"), texts);
    }

    @Test
    void correctly_trims_white_spaces_before_cell_content() {
        GherkinLine gherkinLine = new GherkinLine("|   \t spaces before|");
        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("spaces before"), texts);
    }

    @Test
    void correctly_trims_white_spaces_after_cell_content() {
        GherkinLine gherkinLine = new GherkinLine("|spaces after   |");
        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("spaces after"), texts);
    }

    @Test
    void correctly_trims_white_spaces_around_cell_content() {
        GherkinLine gherkinLine = new GherkinLine("|   \t spaces everywhere   \t|");
        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("spaces everywhere"), texts);
    }

    @Test
    void does_not_drop_white_spaces_inside_a_cell() {
        GherkinLine gherkinLine = new GherkinLine("| foo()\n  bar\nbaz |");
        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("foo()\n  bar\nbaz"), texts);
    }

    @Test
    void startsWithTitleKeyword_corresponding_keyword_match() {
        // Given
        GherkinLine gherkinLine = new GherkinLine("Feature: Hello");

        // When/Then
        assertTrue(gherkinLine.startsWithTitleKeyword("Feature"));
    }

    @Test
    void startsWithTitleKeyword_non_corresponding_keyword_does_not_match() {
        // Given
        GherkinLine gherkinLine = new GherkinLine("Rule: X");

        // When/Then
        assertFalse(gherkinLine.startsWithTitleKeyword("Background")); // not the same keyword
        assertFalse(gherkinLine.startsWithTitleKeyword("Rule: X")); // same keyword but with colon
        assertFalse(gherkinLine.startsWithTitleKeyword("Rul")); // shorter than keyword
    }

    @Test
    void startsWithTitleKeyword_keyword_without_colon_does_not_match() {
        // Given
        GherkinLine gherkinLine = new GherkinLine("Rule");

        // When/Then
        assertFalse(gherkinLine.startsWithTitleKeyword("Rule"));
    }

    @Test
    void substringTrimmed_empty_idempotence() {
        // Given
        GherkinLine gherkinLine = new GherkinLine("");

        // When/Then
        assertEquals("", gherkinLine.substringTrimmed(0));
    }

    @Test
    void substringTrimmed_regular_spaces_after_index_are_trimmed() {
        // Given
        GherkinLine gherkinLine = new GherkinLine("Rule:    my rule name ");

        // When/Then
        assertEquals("my rule name", gherkinLine.substringTrimmed(5));
    }

    @Test
    void substringTrimmed_unicode_spaces_after_index_are_trimmed() {
        // Given
        GherkinLine gherkinLine = new GherkinLine("Rule:" + WHITESPACE + CUCUMBER + WHITESPACE);

        // When/Then
        assertEquals(CUCUMBER, gherkinLine.substringTrimmed(5));
    }

    @Test
    void getRawTextSubstring_substring_from_beginning() {
        // Given
        GherkinLine gherkinLine = new GherkinLine("    some text");

        // When/Then
        assertEquals("    some text", gherkinLine.getRawTextSubstring(0));
    }

    @Test
    void getRawTextSubstring_substring_from_middle() {
        // Given
        GherkinLine gherkinLine = new GherkinLine("    some text");

        // When/Then
        assertEquals(" some text", gherkinLine.getRawTextSubstring(3));
    }


}
