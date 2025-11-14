package io.cucumber.gherkin;

import io.cucumber.messages.types.Envelope;
import io.cucumber.messages.types.Feature;
import io.cucumber.messages.types.GherkinDocument;
import io.cucumber.messages.types.ParseError;
import io.cucumber.messages.types.Pickle;
import io.cucumber.messages.types.PickleStep;
import io.cucumber.messages.types.Scenario;
import io.cucumber.messages.types.Source;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.Optional;
import java.util.stream.Stream;

import static io.cucumber.messages.types.SourceMediaType.TEXT_X_CUCUMBER_GHERKIN_PLAIN;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

class GherkinParserTest {

    final String feature = """
            Feature: Minimal
            
              Scenario: minimalistic
                Given the minimalism
            """;
    final Envelope envelope = Envelope.of(new Source("minimal.feature", feature, TEXT_X_CUCUMBER_GHERKIN_PLAIN));

    @Test
    void use_this_in_readme() {
        GherkinParser parser = GherkinParser.builder().build();
        Stream<Envelope> pickles = parser.parse(envelope).filter(envelope -> envelope.getPickle().isPresent());
        assertEquals(1, pickles.count());
    }

    @Test
    void can_parse_streams() throws IOException {
        InputStream is = new ByteArrayInputStream(feature.getBytes(StandardCharsets.UTF_8));
        GherkinParser parser = GherkinParser.builder()
                .includeSource(false)
                .includeGherkinDocument(false)
                .build();
        List<Envelope> pickles = parser.parse("minimal.feature", is).toList();
        assertTrue(pickles.get(0).getPickle().isPresent());
    }

    @Test
    void provides_access_to_the_ast() {
        // Get the AST
        GherkinDocument gherkinDocument = GherkinParser.builder()
                .includeSource(false)
                .includePickles(false)
                .build()
                .parse(envelope)
                .findFirst().get()
                .getGherkinDocument().get();

        // Get the Feature node of the AST
        Feature feature = gherkinDocument.getFeature().get();
        assertEquals("Minimal", feature.getName());

        // Get the first Scenario node of the Feature node
        Scenario scenario = feature.getChildren().get(0).getScenario().get();
        assertEquals("minimalistic", scenario.getName());
    }

    @Test
    void provides_access_to_pickles_which_are_compiled_from_the_ast() {
        // Get the first pickle
        Pickle pickle = GherkinParser.builder()
                .includeSource(false)
                .includeGherkinDocument(false)
                .build()
                .parse(envelope)
                .findFirst().get()
                .getPickle().get();

        // Get the first step of the pickle
        PickleStep step = pickle.getSteps().get(0);
        assertEquals("the minimalism", step.getText());
    }

    @Test
    void parses_supplied_source() {
        GherkinDocument gherkinDocument = GherkinParser.builder()
                .includeSource(false)
                .includePickles(false)
                .build()
                .parse(envelope)
                .findFirst().get()
                .getGherkinDocument().get();

        Feature feature = gherkinDocument.getFeature().get();
        assertEquals("Minimal", feature.getName());
    }

    @Test
    void parser_always_includes_errors() {
        Envelope singleParseError = Envelope.of(new Source("single_parser_error.feature",
                """
                        
                        invalid line here
                        
                        Feature: Single parser error
                        
                          Scenario: minimalistic
                            Given the minimalism
                        """,
                TEXT_X_CUCUMBER_GHERKIN_PLAIN));
        Optional<ParseError> parseError = GherkinParser.builder()
                .includeSource(false)
                .includePickles(false)
                .includeGherkinDocument(false)
                .build()
                .parse(singleParseError)
                .findFirst().get()
                .getParseError();

        assertTrue(parseError.isPresent());
    }
}
