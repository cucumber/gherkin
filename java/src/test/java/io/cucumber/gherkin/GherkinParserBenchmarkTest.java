package io.cucumber.gherkin;

import io.cucumber.messages.types.Envelope;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.runner.Runner;
import org.openjdk.jmh.runner.RunnerException;
import org.openjdk.jmh.runner.options.Options;
import org.openjdk.jmh.runner.options.OptionsBuilder;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.stream.Stream;
@State(Scope.Thread)
@org.openjdk.jmh.annotations.Measurement(time = 1, timeUnit = java.util.concurrent.TimeUnit.SECONDS) // 150 -> 1
@org.openjdk.jmh.annotations.Warmup(time = 1, timeUnit = java.util.concurrent.TimeUnit.SECONDS) // 40 -> 1
public class GherkinParserBenchmarkTest {

    //@Benchmark
    public Stream<Envelope> parse() throws IOException {
        GherkinParser gherkinParser = GherkinParser.builder()
                .idGenerator(new IncrementingIdGenerator())
                .build();
        return gherkinParser.parse(Paths.get("../testdata/good/very_long.feature"));
    }

    @Benchmark
    public Stream<Envelope> startsWith() throws IOException {
        Constants.DEFAULT_LANGUAGE="en-StartsWith";
        GherkinParser gherkinParser = GherkinParser.builder()
                .idGenerator(new IncrementingIdGenerator())
                .build();
        return gherkinParser.parse(Paths.get("../testdata/good/very_long.feature"));
    }

    @Benchmark
    public Stream<Envelope> startsWithFirstChar() throws IOException {
        Constants.DEFAULT_LANGUAGE="en-StartsWithFirstChar";
        GherkinParser gherkinParser = GherkinParser.builder()
                .idGenerator(new IncrementingIdGenerator())
                .build();
        return gherkinParser.parse(Paths.get("../testdata/good/very_long.feature"));
    }

    @Benchmark
    public Stream<Envelope> startsWithLanguageAdaptative() throws IOException {
        Constants.DEFAULT_LANGUAGE="en-StartsWithLanguageAdaptative";
        GherkinParser gherkinParser = GherkinParser.builder()
                .idGenerator(new IncrementingIdGenerator())
                .build();
        return gherkinParser.parse(Paths.get("../testdata/good/very_long.feature"));
    }

    @Benchmark
    public Stream<Envelope> startsWithFirstCharAndLastChar() throws IOException {
        Constants.DEFAULT_LANGUAGE="en-StartsWithFirstCharAndLastChar";
        GherkinParser gherkinParser = GherkinParser.builder()
                .idGenerator(new IncrementingIdGenerator())
                .build();
        return gherkinParser.parse(Paths.get("../testdata/good/very_long.feature"));
    }

    @Benchmark
    public Stream<Envelope> startsWithFirstCharAndTitleKeywordWithLength() throws IOException {
        Constants.DEFAULT_LANGUAGE="en-StartsWithFirstCharAndTitleKeywordWithLength";
        GherkinParser gherkinParser = GherkinParser.builder()
                .idGenerator(new IncrementingIdGenerator())
                .build();
        return gherkinParser.parse(Paths.get("../testdata/good/very_long.feature"));
    }


    @Benchmark
    public Stream<Envelope> startsWithLastChar() throws IOException {
        Constants.DEFAULT_LANGUAGE="en-StartsWithLastChar";
        GherkinParser gherkinParser = GherkinParser.builder()
                .idGenerator(new IncrementingIdGenerator())
                .build();
        return gherkinParser.parse(Paths.get("../testdata/good/very_long.feature"));
    }

    @Benchmark
    public Stream<Envelope> startsWithTitleKeyword() throws IOException {
        Constants.DEFAULT_LANGUAGE="en-StartsWithTitleKeyword";
        GherkinParser gherkinParser = GherkinParser.builder()
                .idGenerator(new IncrementingIdGenerator())
                .build();
        return gherkinParser.parse(Paths.get("../testdata/good/very_long.feature"));
    }

    @Benchmark
    public Stream<Envelope> startsWithTitleKeywordWithLength() throws IOException {
        Constants.DEFAULT_LANGUAGE="en-StartsWithTitleKeywordWithLength";
        GherkinParser gherkinParser = GherkinParser.builder()
                .idGenerator(new IncrementingIdGenerator())
                .build();
        return gherkinParser.parse(Paths.get("../testdata/good/very_long.feature"));
    }

    /**
     * Entry point for JMH
     */
    /*public static void main(String[] args) throws RunnerException {
        Options opt = new OptionsBuilder()
                .include(GherkinParserBenchmarkTest.class.getSimpleName())
                .forks(1)
                .build();

        new Runner(opt).run();
    }*/

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
        //Constants.DEFAULT_LANGUAGE="en-StartsWithTitleKeyword";
        Constants.DEFAULT_LANGUAGE="en-StartsWithLanguageAdaptative";
        for (int i = 0; i < 10_000; i++) {
            parse();
        }
    }
}
