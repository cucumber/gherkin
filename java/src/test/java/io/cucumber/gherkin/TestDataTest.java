package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.stream.Stream;

public class TestDataTest {
    @Test
    void testdata_features_are_parsed_without_NPE() throws IOException {
        GherkinParser gherkinParser = GherkinParser.builder()
                .idGenerator(new IncrementingIdGenerator())
                .build();
        try (Stream<Path> list = Stream.of(
                Files.list(Paths.get("../testdata/good/")),
                Files.list(Paths.get("../testdata/bad/")))
                .flatMap(s -> s)) {
            list
            .filter(path -> path.toString().endsWith(".feature"))
            .forEach(source -> {
                try {
                    gherkinParser.parse(source);
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            });
        }
    }
}
