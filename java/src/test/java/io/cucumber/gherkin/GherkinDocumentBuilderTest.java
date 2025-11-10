package io.cucumber.gherkin;

import io.cucumber.messages.IdGenerator;
import io.cucumber.messages.types.Comment;
import io.cucumber.messages.types.FeatureChild;
import io.cucumber.messages.types.GherkinDocument;
import io.cucumber.messages.types.Location;
import io.cucumber.messages.types.Pickle;
import io.cucumber.messages.types.TableRow;
import org.assertj.core.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

class GherkinDocumentBuilderTest {
    private final IdGenerator idGenerator = new IncrementingIdGenerator();

    @Test
    void is_reusable() {
        var parser = new Parser<>(new GherkinDocumentBuilder(idGenerator, "test.feature"));
        GherkinTokenMatcher matcher = new GherkinTokenMatcher();

        GherkinDocument d1 = parser.parse("Feature: 1", matcher, "1.feature");
        GherkinDocument d2 = parser.parse("Feature: 2", matcher, "2.feature");

        assertEquals("1", d1.getFeature().get().getName());
        assertEquals("2", d2.getFeature().get().getName());
    }

    @Test
    void parses_rules() {
        var parser = new Parser<>(new GherkinDocumentBuilder(idGenerator, "test.feature"));
        String data = """
                Feature: Some rules
                
                  Background:
                    Given fb
                
                  Rule: A
                    The rule A description
                
                    Background:
                      Given ab
                
                    Example: Example A
                      Given a
                
                  Rule: B
                    The rule B description
                
                    Example: Example B
                      Given b
                """;
        GherkinDocument doc = parser.parse(data, "test.feature");

        List<FeatureChild> children = doc.getFeature().get().getChildren();
        assertEquals(3, children.size());

        IdGenerator idGenerator = new IncrementingIdGenerator();
        PickleCompiler pickleCompiler = new PickleCompiler(idGenerator);
        List<Pickle> pickles = pickleCompiler.compile(doc, "hello.feature");
        assertEquals(2, pickles.size());

        assertEquals(3, pickles.get(0).getSteps().size());

        assertEquals(2, pickles.get(1).getSteps().size());

    }

    @Test
    void parses_just_comments() {
        var parser = new Parser<>(new GherkinDocumentBuilder(idGenerator, "test.feature"));
        GherkinDocument doc = parser.parse("# Just a comment", "test.feature");
        List<Comment> children = doc.getComments();
        assertEquals(1, children.size());
    }

    @Test
    void sets_empty_table_cells() {
        var parser = new Parser<>(new GherkinDocumentBuilder(idGenerator, "test.feature"));
        GherkinDocument doc = parser.parse("""
                        Feature:
                          Scenario:
                            Given a table
                              |a||b|
                        """,
                "test.feature"
        );
        List<FeatureChild> children = doc.getFeature().get().getChildren();
        assertEquals(1, children.size());
        TableRow row = children.get(0).getScenario().get().getSteps().get(0).getDataTable().get().getRows().get(0);
        assertEquals("a", row.getCells().get(0).getValue());
        assertEquals("", row.getCells().get(1).getValue());
        assertEquals("b", row.getCells().get(2).getValue());
    }

    @Test
    void table_cells_with_different_size_throws_exception() {
        // Given
        var parser = new Parser<>(new GherkinDocumentBuilder(idGenerator, "test.feature"));

        // When
        ParserException.CompositeParserException compositeParserException = assertThrows(ParserException.CompositeParserException.class, () -> parser.parse("""
                        Feature:
                          Scenario:
                            Given a table
                              |a|b|
                              |c|d|e|
                        """,
                "test.feature"
        ));

        // Then
        Assertions.assertThat(compositeParserException).hasMessageContaining("inconsistent cell count within the table");
        Assertions.assertThat(compositeParserException.errors)
                .singleElement()
                .extracting(e -> e.location)
                        .isEqualTo(new Location(5, 7));
    }

}
