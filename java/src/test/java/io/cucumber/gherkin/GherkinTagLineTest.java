package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;
import org.junit.jupiter.api.Test;

import java.util.Collections;
import java.util.List;

import static io.cucumber.gherkin.GherkinTagLine.parseTags;
import static java.util.Arrays.asList;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

class GherkinTagLineTest {
    final Location line = Locations.atLine(12);

    @Test
    void allows_any_non_space_characters_in_a_tag() {
        List<GherkinLineSpan> gherkinLineSpans = parseTags(3, "@foo:bar  @zap\uD83E\uDD52yo", line);

        assertEquals(asList(
                new GherkinLineSpan(4, "@foo:bar"),
                new GherkinLineSpan(14, "@zap\uD83E\uDD52yo")
        ), gherkinLineSpans);
    }

    @Test
    void finds_tags() {
        List<GherkinLineSpan> gherkinLineSpans = parseTags(0, "@this @is @a @tag", line);

        assertEquals(asList(
                new GherkinLineSpan(1, "@this"),
                new GherkinLineSpan(7, "@is"),
                new GherkinLineSpan(11, "@a"),
                new GherkinLineSpan(14, "@tag")
        ), gherkinLineSpans);
    }

    @Test
    void throws_on_tags_with_spaces() {
        assertThrows(ParserException.class, () -> parseTags(0, "@this @is @a space separated @tag", line));
    }

    @Test
    void throws_on_tags_with_leading_spaces() {
        assertThrows(ParserException.class, () -> parseTags(0, "@ leadingSpace", line));
    }

    @Test
    void ignores_empty_tag() {
        List<GherkinLineSpan> gherkinLineSpans = parseTags(0, "@", line);
        assertEquals(Collections.emptyList(), gherkinLineSpans);
    }

    @Test
    void ignores_empty_tags() {
        List<GherkinLineSpan> gherkinLineSpans = parseTags(0, "@@", line);
        assertEquals(Collections.emptyList(), gherkinLineSpans);
    }

    @Test
    void finds_tags__trim_whitespace() {
        List<GherkinLineSpan> gherkinLineSpans = parseTags(4, "@this @is  @a @tag", line);
        assertEquals(asList(
                new GherkinLineSpan(5, "@this"),
                new GherkinLineSpan(11, "@is"),
                new GherkinLineSpan(16, "@a"),
                new GherkinLineSpan(19, "@tag")
        ), gherkinLineSpans);
    }

    @Test
    void finds_tags__comment_after_tag() {
        List<GherkinLineSpan> gherkinLineSpans = parseTags(0, "@this @is #acomment", line);
        assertEquals(asList(
                new GherkinLineSpan(1, "@this"),
                new GherkinLineSpan(7, "@is")
        ), gherkinLineSpans);
    }

    @Test
    void finds_tags__comment_inside_tag_preceded_by_nbsp() {
        List<GherkinLineSpan> gherkinLineSpans = parseTags(0, "@this @is\u202F#acomment", line);
        assertEquals(asList(
                new GherkinLineSpan(1, "@this"),
                new GherkinLineSpan(7, "@is")
        ), gherkinLineSpans);
    }

    @Test
    void finds_tags__comment_inside_tag() {
        List<GherkinLineSpan> gherkinLineSpans = parseTags(0, "@comment_tag#2 #a comment", line);
        assertEquals(asList(
                new GherkinLineSpan(1, "@comment_tag#2")
        ), gherkinLineSpans);
    }

    @Test
    void finds_tags__commented_before_tag() {
        List<GherkinLineSpan> gherkinLineSpans = parseTags(0, "@this @is #@a commented tag", line);
        assertEquals(asList(
                new GherkinLineSpan(1, "@this"),
                new GherkinLineSpan(7, "@is")
        ), gherkinLineSpans);
    }

    @Test
    void finds_tags__commented_multiple_tags() {
        List<GherkinLineSpan> gherkinLineSpans = parseTags(0, "@this @is #@a @commented @sequence of tags", line);
        assertEquals(asList(
                new GherkinLineSpan(1, "@this"),
                new GherkinLineSpan(7, "@is")
        ), gherkinLineSpans);
    }

    @Test
    void finds_tags_with_number() {
        List<GherkinLineSpan> gherkinLineSpans = parseTags(0, "@ISSUE#123", line);
        assertEquals(asList(
                new GherkinLineSpan(1, "@ISSUE#123")
        ), gherkinLineSpans);
    }

    @Test
    void parseTags_returns_empty_list_when_empty_line() {
        List<GherkinLineSpan> gherkinLineSpans = parseTags(0, "", line);
        assertEquals(Collections.emptyList(), gherkinLineSpans);
    }
}
