package io.cucumber.gherkin;

import io.cucumber.messages.types.Envelope;
import org.junit.jupiter.api.Test;

import java.nio.charset.StandardCharsets;
import java.util.stream.Stream;

class ExampleTest {

    @Test
    void test(){
        String feature = """
                Feature: Feature 2
                  # some comment
                  some description
                
                  Scenario: Scenario 1
                    * Wait 3s
                """;

        GherkinParser parser = GherkinParser.builder().build();

        Stream<Envelope> parse = parser.parse("example.feature", feature.getBytes(StandardCharsets.UTF_8));

        parse.forEach(System.out::println);

    }
}
