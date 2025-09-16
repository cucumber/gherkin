package io.cucumber.gherkin;

import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.runner.Runner;
import org.openjdk.jmh.runner.RunnerException;
import org.openjdk.jmh.runner.options.Options;
import org.openjdk.jmh.runner.options.OptionsBuilder;

import java.util.Collection;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class IsWhiteSpaceBenchmarkTest {

    private static final char[] featureFileLinePrefixes = createLinePrefixes();

    /**
     * Construct a string of all potential valid prefixes in a feature file.
     * <p>
     * StringUtils.isWhitespace is primarily used to trim lines. A line will
     * typically consist of 0 and 8 spaces, followed by the first character
     * from a keyword. It's performance should be optimized with that in mind.
     * <p>
     * To keep things simple we take every starting character from every keyword
     * and prefix it with 4 spaces.
     */
    private static char[] createLinePrefixes() {
        return GherkinDialects.getDialects().stream()
                .flatMap(gherkinDialect -> Stream.of(
                        gherkinDialect.getFeatureKeywords(),
                        gherkinDialect.getRuleKeywords(),
                        gherkinDialect.getScenarioOutlineKeywords(),
                        gherkinDialect.getScenarioKeywords(),
                        gherkinDialect.getExamplesKeywords(),
                        gherkinDialect.getBackgroundKeywords(),
                        gherkinDialect.getStepKeywords()
                ))
                .flatMap(Collection::stream)
                .map(keyword -> keyword.charAt(0))
                .distinct()
                .map(firstCharacter -> "    " + firstCharacter)
                .collect(Collectors.joining())
                .toCharArray();
    }

    @Benchmark
    public boolean benchmarkIsWhiteSpace() {
        boolean hasWhitespace = false;
        for (char c : featureFileLinePrefixes) {
            hasWhitespace |= StringUtils.isWhitespace(c);
        }
        return hasWhitespace;
    }

    @Benchmark
    public boolean benchmarkIsWhiteSpaceNoIf() {
        boolean hasWhitespace = false;
        for (char c : featureFileLinePrefixes) {
            hasWhitespace |= StringUtils.isWhitespaceNoIf(c);
        }
        return hasWhitespace;
    }

    @Benchmark
    public boolean benchmarkIsWhitespaceLt32OrRange5760To12288ThenSparseSpaces() {
        boolean hasWhitespace = false;
        for (char c : featureFileLinePrefixes) {
            hasWhitespace |= StringUtils.isWhitespaceLt32OrRange5760To12288ThenSparseSpaces(c);
        }
        return hasWhitespace;
    }

    @Benchmark
    public boolean benchmarkIsWhitespaceLt32OrRange5760To12288ThenSparseSpacesNoIf() {
        boolean hasWhitespace = false;
        for (char c : featureFileLinePrefixes) {
            hasWhitespace |= StringUtils.isWhitespaceLt32OrRange5760To12288ThenSparseSpacesNoIf(c);
        }
        return hasWhitespace;
    }

    @Benchmark
    public boolean benchmarkIsWhiteSpaceSlow() {
        boolean hasWhitespace = false;
        for (char c : featureFileLinePrefixes) {
            hasWhitespace |= isWhiteSpaceReferenceImplementation(c);
        }
        return hasWhitespace;
    }

    private static boolean isWhiteSpaceReferenceImplementation(char c) {
        return c == ' ' || c == '\t' || StringUtils.isWhiteSpaceSlow(c);
    }

    /**
     * Entry point for JMH
     */
    public static void main(String[] args) throws RunnerException {
        Options opt = new OptionsBuilder()
                .include(IsWhiteSpaceBenchmarkTest.class.getSimpleName())
                .forks(1)
                .build();

        new Runner(opt).run();
    }

    /**
     * Ensures we don't break the parse method in CI.
     */
    @Test
    public void testBenchmark() {
        benchmarkIsWhiteSpace();
        benchmarkIsWhiteSpaceSlow();
    }

    /**
     * Convenience method to run the profiler on.
     */
    @Test
    @Disabled
    public void profileBenchmark() {
        for (int i = 0; i < 10_0000; i++) {
            benchmarkIsWhiteSpace();
        }
    }

    @Test
    void all_implementations_behave_the_same() {
        for (char c = Character.MIN_VALUE; c < Character.MAX_VALUE; c++) {
            boolean bSlow = StringUtils.isWhiteSpaceSlow(c);
            boolean bRI = isWhiteSpaceReferenceImplementation(c);
            boolean b0 = StringUtils.isWhitespace(c);
            boolean b2 = StringUtils.isWhitespaceNoIf(c);
            boolean b3 = StringUtils.isWhitespaceLt32OrRange5760To12288ThenSparseSpaces(c);
            boolean b4 = StringUtils.isWhitespaceLt32OrRange5760To12288ThenSparseSpacesNoIf(c);
            assertEquals(bSlow, bRI, "Mismatch for char " + (int) c + " '" + c + "'");
            assertEquals(bSlow, b0, "Mismatch for char " + (int) c + " '" + c + "'");
            assertEquals(bSlow, b2, "Mismatch for char " + (int) c + " '" + c + "'");
            assertEquals(bSlow, b3, "Mismatch for char " + (int) c + " '" + c + "'");
            assertEquals(bSlow, b4, "Mismatch for char " + (int) c + " '" + c + "'");
        }
    }

}
