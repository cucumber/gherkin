package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import java.util.List;
import java.util.stream.Collectors;

import static io.cucumber.gherkin.TableRowLine.parse;
import static org.junit.jupiter.api.Assertions.assertEquals;

class TableRowLineTest {

    @SuppressWarnings({"UnnecessaryUnicodeEscape", "UnicodeEscape"})
    @Test
    void finds_table_cells() {
        // The cells below has the following whitespace characters on each side:
        // - U+00A0 (non-breaking space)
        // - U+0020 (space)
        // - U+0009 (tab)
        // This is generated with `ruby -e 'STDOUT.write "\u00A0\u0020\u0009".encode("utf-8")' | pbcopy`
        // and pasted.
        List<LineSpan> tableCells = parse(6, "|  \tred  \t|  \tblue  \t|  \t\uD83E\uDD52\uD83E\uDD52\uD83E\uDD52  \t|  \tgreen  \t|");
        LineSpan redSpan = tableCells.get(0);
        LineSpan blueSpan = tableCells.get(1);
        LineSpan emojiSpan = tableCells.get(2);
        LineSpan greenSpan = tableCells.get(3);

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
        List<LineSpan> tableCells = parse(6, "| \\|æ\\\\n     | \\o\\no\\  | \\\\\\|a\\\\\\\\n | ø\\\\\\nø\\\\|");
        List<String> texts = tableCells.stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(List.of("|æ\\n", "\\o\no\\", "\\|a\\\\n", "ø\\\nø\\"), texts);
    }

    @Test
    void preserve_escaped_new_lines_at_start_and_end() {
        List<LineSpan> tableCells = parse(6, "|  \nraindrops--\nher last kiss\ngoodbye.\n  |");
        List<String> texts = tableCells.stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(List.of("""
                
                raindrops--
                her last kiss
                goodbye.
                """
        ), texts);
    }

    @Test
    void escapes_backslash() {
        List<LineSpan> tableCells = parse(0, "|\\\\o\\no\\||");
        List<String> texts = tableCells.stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(List.of("\\o\no|"), texts);
    }

    @Test
    void throws_on_illegal_escapes_backslash() {
        List<LineSpan> tableCells = parse(0, "|\\o\\no\\||");
        List<String> texts = tableCells.stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(List.of("\\o\no|"), texts);
    }

    @Test
    void correctly_trims_white_spaces_before_cell_content() {
        List<LineSpan> tableCells = parse(0, "|   \t spaces before|");
        List<String> texts = tableCells.stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(List.of("spaces before"), texts);
    }

    @Test
    void correctly_trims_white_spaces_after_cell_content() {
        List<LineSpan> tableCells = parse(0, "|spaces after   |");
        List<String> texts = tableCells.stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(List.of("spaces after"), texts);
    }

    @Test
    void correctly_trims_white_spaces_around_cell_content() {
        List<LineSpan> tableCells = parse(0, "|   \t spaces everywhere   \t|");
        List<String> texts = tableCells.stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(List.of("spaces everywhere"), texts);
    }

    @Test
    void does_not_drop_white_spaces_inside_a_cell() {
        List<LineSpan> tableCells = parse(0, "| foo()\n  bar\nbaz |");
        List<String> texts = tableCells.stream().map(span -> span.text).collect(Collectors.toList());
        assertEquals(List.of("foo()\n  bar\nbaz"), texts);
    }
}
