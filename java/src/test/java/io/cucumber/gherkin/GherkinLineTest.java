package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;
import org.junit.jupiter.api.Test;

import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

import static java.util.Arrays.asList;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

class GherkinLineTest {

    final Location line = Locations.atLine(12);

    @Test
    void allows_any_non_space_characters_in_a_tag() {
        GherkinLine gherkinLine = new GherkinLine("   @foo:bar  @zap\uD83E\uDD52yo", line);
        List<GherkinLineSpan> gherkinLineSpans = gherkinLine.parseTags();

        assertEquals(asList(
                new GherkinLineSpan(4, "@foo:bar"),
                new GherkinLineSpan(14, "@zap\uD83E\uDD52yo")
        ), gherkinLineSpans);
    }


    @Test
    void finds_tags() {
        GherkinLine gherkinLine = new GherkinLine("@this @is @a @tag", line);
        List<GherkinLineSpan> gherkinLineSpans = gherkinLine.parseTags();

        assertEquals(asList(
                new GherkinLineSpan(1, "@this"),
                new GherkinLineSpan(7, "@is"),
                new GherkinLineSpan(11, "@a"),
                new GherkinLineSpan(14, "@tag")
        ), gherkinLineSpans);
    }

    @Test
    void throws_on_tags_with_spaces() {
        GherkinLine gherkinLine = new GherkinLine("@this @is @a space separated @tag", line);
        assertThrows(ParserException.class, gherkinLine::parseTags);
    }

    @Test
    void throws_on_tags_with_leading_spaces() {
        GherkinLine gherkinLine = new GherkinLine("@ leadingSpace", line);
        assertThrows(ParserException.class, gherkinLine::parseTags);
    }

    @Test
    void ignores_empty_tag() {
        GherkinLine gherkinLine = new GherkinLine("@", line);
        List<GherkinLineSpan> gherkinLineSpans = gherkinLine.parseTags();

        assertEquals(Collections.emptyList(), gherkinLineSpans);
    }

    @Test
    void ignores_empty_tags() {
        GherkinLine gherkinLine = new GherkinLine("@@", line);
        List<GherkinLineSpan> gherkinLineSpans = gherkinLine.parseTags();

        assertEquals(Collections.emptyList(), gherkinLineSpans);
    }

    @Test
    void finds_tags__trim_whitespace() {
        GherkinLine gherkinLine = new GherkinLine("    @this @is  @a @tag  ", line);
        List<GherkinLineSpan> gherkinLineSpans = gherkinLine.parseTags();

        assertEquals(asList(
                new GherkinLineSpan(5, "@this"),
                new GherkinLineSpan(11, "@is"),
                new GherkinLineSpan(16, "@a"),
                new GherkinLineSpan(19, "@tag")
        ), gherkinLineSpans);
    }

    @Test
    void finds_tags__comment_after_tag() {
        GherkinLine gherkinLine = new GherkinLine("@this @is #acomment  ", line);
        List<GherkinLineSpan> gherkinLineSpans = gherkinLine.parseTags();

        assertEquals(asList(
                new GherkinLineSpan(1, "@this"),
                new GherkinLineSpan(7, "@is")
        ), gherkinLineSpans);
    }

    @Test
    void finds_tags__comment_inside_tag() {
        GherkinLine gherkinLine = new GherkinLine("@comment_tag#2 #a comment", line);
        List<GherkinLineSpan> gherkinLineSpans = gherkinLine.parseTags();

        assertEquals(asList(
                new GherkinLineSpan(1, "@comment_tag#2")
        ), gherkinLineSpans);
    }

    @Test
    void finds_tags__commented_before_tag() {
        GherkinLine gherkinLine = new GherkinLine("@this @is #@a commented tag", line);
        List<GherkinLineSpan> gherkinLineSpans = gherkinLine.parseTags();

        assertEquals(asList(
                new GherkinLineSpan(1, "@this"),
                new GherkinLineSpan(7, "@is")
        ), gherkinLineSpans);
    }

    @Test
    void finds_tags__commented_multiple_tags() {
        GherkinLine gherkinLine = new GherkinLine("@this @is #@a @commented @sequence of tags", line);
        List<GherkinLineSpan> gherkinLineSpans = gherkinLine.parseTags();

        assertEquals(asList(
                new GherkinLineSpan(1, "@this"),
                new GherkinLineSpan(7, "@is")
        ), gherkinLineSpans);
    }

    @Test
    void finds_tags_with_number() {
        GherkinLine gherkinLine = new GherkinLine("@ISSUE#123", line);
        List<GherkinLineSpan> gherkinLineSpans = gherkinLine.parseTags();

        assertEquals(asList(
                new GherkinLineSpan(1, "@ISSUE#123")
        ), gherkinLineSpans);
    }

    @Test
    void finds_table_cells() {
        // The cells below has the following whitespace characters on each side:
        // - U+00A0 (non-breaking space)
        // - U+0020 (space)
        // - U+0009 (tab)
        // This is generated with `ruby -e 'STDOUT.write "\u00A0\u0020\u0009".encode("utf-8")' | pbcopy`
        // and pasted.
        GherkinLine gherkinLine = new GherkinLine("      |  \tred  \t|  \tblue  \t|  \t\uD83E\uDD52\uD83E\uDD52\uD83E\uDD52  \t|  \tgreen  \t|", line);
        
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
        GherkinLine gherkinLine = new GherkinLine("      | \\|æ\\\\n     | \\o\\no\\  | \\\\\\|a\\\\\\\\n | ø\\\\\\nø\\\\|", line);

        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("|æ\\n", "\\o\no\\", "\\|a\\\\n", "ø\\\nø\\"), texts);
    }

    @Test
    void preserve_escaped_new_lines_at_start_and_end() {
        GherkinLine gherkinLine = new GherkinLine("      |  \nraindrops--\nher last kiss\ngoodbye.\n  |", line);
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
        GherkinLine gherkinLine = new GherkinLine("|\\\\o\\no\\||", line);
        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("\\o\no|"), texts);
    }

    @Test
    void throws_on_illegal_escapes_backslash() {
        GherkinLine gherkinLine = new GherkinLine("|\\o\\no\\||", line);
        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("\\o\no|"), texts);
    }

    @Test
    void correctly_trims_white_spaces_before_cell_content() {
        GherkinLine gherkinLine = new GherkinLine("|   \t spaces before|", line);
        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("spaces before"), texts);
    }

    @Test
    void correctly_trims_white_spaces_after_cell_content() {
        GherkinLine gherkinLine = new GherkinLine("|spaces after   |", line);
        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("spaces after"), texts);
    }

    @Test
    void correctly_trims_white_spaces_around_cell_content() {
        GherkinLine gherkinLine = new GherkinLine("|   \t spaces everywhere   \t|", line);
        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("spaces everywhere"), texts);
    }

    @Test
    void does_not_drop_white_spaces_inside_a_cell() {
        GherkinLine gherkinLine = new GherkinLine("| foo()\n  bar\nbaz |", line);
        List<String> texts = gherkinLine.parseTableCells().stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(asList("foo()\n  bar\nbaz"), texts);
    }

    @Test
    void startsWithTitleKeyword_corresponding_keyword_match() {
        // Given
        GherkinLine gherkinLine = new GherkinLine("Feature: Hello", line);

        // When/Then
        assertTrue(gherkinLine.startsWithTitleKeyword("Feature"));
    }

    @Test
    void startsWithTitleKeyword_non_corresponding_keyword_does_not_match() {
        // Given
        GherkinLine gherkinLine = new GherkinLine("Rule: X", line);

        // When/Then
        assertFalse(gherkinLine.startsWithTitleKeyword("Background")); // not the same keyword
        assertFalse(gherkinLine.startsWithTitleKeyword("Rule: X")); // same keyword but with colon
        assertFalse(gherkinLine.startsWithTitleKeyword("Rul")); // shorter than keyword
    }

    @Test
    void startsWithTitleKeyword_keyword_without_colon_does_not_match() {
        // Given
        GherkinLine gherkinLine = new GherkinLine("Rule", line);

        // When/Then
        assertFalse(gherkinLine.startsWithTitleKeyword("Rule"));
    }

    @Test
    void parseTags_returns_empty_list_when_empty_line() {
        // Given
        GherkinLine gherkinLine = new GherkinLine("", line);

        // When/Then
        assertTrue(gherkinLine.parseTags().isEmpty());
    }

    @Test
    void substringTrimmed_empty_idempotence() {
        // Given
        GherkinLine gherkinLine = new GherkinLine("", line);

        // When/Then
        assertEquals("", gherkinLine.substringTrimmed(0));
    }

    @Test
    void substringTrimmed_spaces_after_index_are_removed() {
        // Given
        GherkinLine gherkinLine = new GherkinLine("Rule:    my rule name", line);

        // When/Then
        assertEquals("my rule name", gherkinLine.substringTrimmed(5));
    }

}
