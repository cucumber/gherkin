package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.State;

import static io.cucumber.gherkin.Constants.TITLE_KEYWORD_SEPARATOR;
import static io.cucumber.gherkin.Constants.TITLE_KEYWORD_SEPARATOR_LENGTH;
import static io.cucumber.messages.types.StepKeywordType.*;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

@State(Scope.Thread)
@org.openjdk.jmh.annotations.Measurement(time = 1, timeUnit = java.util.concurrent.TimeUnit.SECONDS) // 60
@org.openjdk.jmh.annotations.Warmup(time = 1, timeUnit = java.util.concurrent.TimeUnit.SECONDS) // 20
public class LineBenchmarkTest {

    private static final String SAMPLE_LINE = "    Feature: Sample feature";
    private static final Line line = new Line(SAMPLE_LINE);
    /*
@Deprecated // for performance tests only
boolean startsWith(String prefix, int indexLastChar, char expectedLastChar) {
    return textLength > indexLastChar &&
            text.charAt(indexLastChar) == expectedLastChar &&
            text.startsWith(prefix);
}
@Deprecated // for performance tests only
boolean startsWithTitleKeyword(String keyword) {
    int keywordLength = keyword.length();
    return textLength > keywordLength &&
            text.charAt(keywordLength) == TITLE_KEYWORD_SEPARATOR &&
            text.startsWith(keyword);
}
     */
    @Benchmark
    public boolean benchmarkStartsWithFirstCharTrue() {
        return line.startsWith('F', "eature:");
    }

    @Benchmark
    public boolean benchmarkStartsWithLastCharTrue() {
        return line.startsWith("Feature", 7, ':');

    }

    @Benchmark
    public boolean benchmarkStartsWithTrue() {
        return line.startsWith("Feature:");
    }

    @Benchmark
    public boolean benchmarkStartsWithTitleKeywordWithLengthTrue() {
        return line.startsWithTitleKeyword("Feature", 7);
    }

    @Benchmark
    public boolean benchmarkStartsWithTitleKeywordTrue() {
        return line.startsWithTitleKeyword("Feature");
    }

    // ----------------------- negative tests -----------------------
    @Benchmark
    public boolean benchmarkStartsWithFirstCharFalse() {
        return line.startsWith('B', "ackground:");
    }

    @Benchmark
    public boolean benchmarkStartsWithLastCharFalse() {
        return line.startsWith("Background:", 10, ':');
    }

    @Benchmark
    public boolean benchmarkStartsWithFalse() {
        return line.startsWith("Background:");
    }

    @Benchmark
    public boolean benchmarkStartsWithTitleKeywordWithLengthFalse() {
        return line.startsWithTitleKeyword("Background", 10);
    }

    @Benchmark
    public boolean benchmarkStartsWithTitleKeywordFalse() {
        return line.startsWithTitleKeyword("Background");
    }

    @Test
    void x() {
        // assert that all benchmark methods give the same result
        assertTrue(benchmarkStartsWithFirstCharTrue());
        assertTrue(benchmarkStartsWithLastCharTrue());
        assertTrue(benchmarkStartsWithTrue());
        assertTrue(benchmarkStartsWithTitleKeywordTrue());
        assertTrue(benchmarkStartsWithTitleKeywordWithLengthTrue());
        assertFalse(benchmarkStartsWithFirstCharFalse());
        assertFalse(benchmarkStartsWithLastCharFalse());
        assertFalse(benchmarkStartsWithFalse());
        assertFalse(benchmarkStartsWithTitleKeywordFalse());
        assertFalse(benchmarkStartsWithTitleKeywordWithLengthFalse());

    }

}
