package io.cucumber.gherkin;

import io.cucumber.messages.types.Envelope;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.runner.Runner;
import org.openjdk.jmh.runner.RunnerException;
import org.openjdk.jmh.runner.options.Options;
import org.openjdk.jmh.runner.options.OptionsBuilder;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.stream.Stream;

public class GherkinParserBenchmarkTest {

    @Benchmark
    public Stream<Envelope> parse() throws IOException {
        GherkinParser gherkinParser = GherkinParser.builder()
                .idGenerator(new IncrementingIdGenerator())
                .build();
        return gherkinParser.parse(Paths.get("../testdata/good/very_long.feature"));
    }

    /**
     * Entry point for JMH
     */
    public static void main(String[] args) throws RunnerException {
        Options opt = new OptionsBuilder()
                .include(GherkinParserBenchmarkTest.class.getSimpleName())
                .forks(1)
                .build();

        new Runner(opt).run();
    }

    /**
     * Ensures we don't break the parse method in CI.
     */
    @Test
    public void testParse() throws IOException {
        parse();
    }

    /**
     * Convenience method to run the profiler on.
     */
    @Test
    @Disabled
    public void profileParse() throws IOException {
        for (int i = 0; i < 1000; i++) {
            parse();
        }
    }
}
