package io.cucumber.gherkin;

import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.State;

@State(Scope.Thread)
@org.openjdk.jmh.annotations.Measurement(time = 22, timeUnit = java.util.concurrent.TimeUnit.SECONDS) // 20 -> 1
@org.openjdk.jmh.annotations.Warmup(time = 2, timeUnit = java.util.concurrent.TimeUnit.SECONDS) // 2 -> 1
public class KeyworkMatcherBenchmarkTest {

    private static final Line stepLine = new Line("    And some additional condition");
    private static final Line exampleLine = new Line("    Examples: Sample examples");
    private static final Line featureLine = new Line("    Feature: Sample feature");
    private static final Line scenarioLine = new Line("    Scenario: Sample scenario");
    EnStartsWithFirstChar matcherStartsWithFirstChar = new EnStartsWithFirstChar();
    EnStartsWithFirstCharAndTitleKeywordWithLength matcherStartsWithFirstCharAndTitleKeywordWithLength = new EnStartsWithFirstCharAndTitleKeywordWithLength();
    EnStartsWithLastChar matcherStartsWithLastChar = new EnStartsWithLastChar();
    EnStartsWithFirstCharAndLastChar matcherStartsWithFirstCharAndLastChar = new EnStartsWithFirstCharAndLastChar();
    EnStartsWithLanguageAdaptative matcherStartsWithLanguageAdaptative = new EnStartsWithLanguageAdaptative();
    EnStartsWith matcherStartsWith = new EnStartsWith();
    EnStartsWithTitleKeyword matcherStartsWithTitleKeyword = new EnStartsWithTitleKeyword();
    EnStartsWithTitleKeywordWithLength matcherStartsWithTitleKeywordWithLength = new EnStartsWithTitleKeywordWithLength();

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

    /*
            case "en-StartsWith":
                return new EnStartsWith();
            case "en-StartsWithFirstChar":
                return new EnStartsWithFirstChar();
            case "en-StartsWithFirstCharAndLastChar":
                return new EnStartsWithFirstCharAndLastChar();
            case "en-StartsWithLanguageAdaptative":
                return new EnStartsWithLanguageAdaptative();
            case "en-StartsWithFirstCharAndTitleKeywordWithLength":
                return new EnStartsWithFirstCharAndTitleKeywordWithLength();
            case "en-StartsWithLastChar":
                return new EnStartsWithLastChar();
            case "en-StartsWithTitleKeyword":
                return new EnStartsWithTitleKeyword();
            case "en-StartsWithTitleKeywordWithLength":
                return new EnStartsWithTitleKeywordWithLength();
     */


// -------------------------------- FeatureKeyword -------------------------------------------
    @Benchmark
    public KeywordMatcher.Match matchFeatureKeywordStartsWithFirstChar() {
        return matcherStartsWithFirstChar.matchFeatureKeyword(featureLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchFeatureKeywordStartsWithLastChar() {
        return matcherStartsWithLastChar.matchFeatureKeyword(featureLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchFeatureKeywordStartsWithFirstCharAndLastChar() {
        return matcherStartsWithFirstCharAndLastChar.matchFeatureKeyword(featureLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchFeatureKeywordStartsWithFirstCharAndTitleKeywordWithLength() {
        return matcherStartsWithFirstCharAndTitleKeywordWithLength.matchFeatureKeyword(featureLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchFeatureKeywordStartsWithLanguageAdaptative() {
        return matcherStartsWithLanguageAdaptative.matchFeatureKeyword(featureLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchFeatureKeywordStartsWith() {
        return matcherStartsWith.matchFeatureKeyword(featureLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchFeatureKeywordStartsWithTitleKeywordWithLength() {
        return matcherStartsWithTitleKeywordWithLength.matchFeatureKeyword(featureLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchFeatureKeywordStartsWithTitleKeyword() {
        return matcherStartsWithTitleKeyword.matchFeatureKeyword(featureLine);
    }



// -------------------------------- ScenarioKeyword -------------------------------------------

    @Benchmark
    public KeywordMatcher.Match matchScenarioKeywordStartsWithFirstChar() {
        return matcherStartsWithFirstChar.matchScenarioKeyword(scenarioLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchScenarioKeywordStartsWithLastChar() {
        return matcherStartsWithLastChar.matchScenarioKeyword(scenarioLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchScenarioKeywordStartsWithFirstCharAndLastChar() {
        return matcherStartsWithFirstCharAndLastChar.matchScenarioKeyword(scenarioLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchScenarioKeywordStartsWithFirstCharAndTitleKeywordWithLength() {
        return matcherStartsWithFirstCharAndTitleKeywordWithLength.matchScenarioKeyword(scenarioLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchScenarioKeywordStartsWithLanguageAdaptative() {
        return matcherStartsWithLanguageAdaptative.matchScenarioKeyword(scenarioLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchScenarioKeywordStartsWith() {
        return matcherStartsWith.matchScenarioKeyword(scenarioLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchScenarioKeywordStartsWithTitleKeywordWithLength() {
        return matcherStartsWithTitleKeywordWithLength.matchScenarioKeyword(scenarioLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchScenarioKeywordStartsWithTitleKeyword() {
        return matcherStartsWithTitleKeyword.matchScenarioKeyword(scenarioLine);
    }



// -------------------------------- StepKeyword -------------------------------------------

    @Benchmark
    public KeywordMatcher.StepMatch matchStepKeywordStartsWithFirstChar() {
        return matcherStartsWithFirstChar.matchStepKeyword(stepLine);
    }

    @Benchmark
    public KeywordMatcher.StepMatch matchStepKeywordStartsWithLastChar() {
        return matcherStartsWithLastChar.matchStepKeyword(stepLine);
    }

    @Benchmark
    public KeywordMatcher.StepMatch matchStepKeywordStartsWithFirstCharAndLastChar() {
        return matcherStartsWithFirstCharAndLastChar.matchStepKeyword(stepLine);
    }

    @Benchmark
    public KeywordMatcher.StepMatch matchStepKeywordStartsWithFirstCharAndTitleKeywordWithLength() {
        return matcherStartsWithFirstCharAndTitleKeywordWithLength.matchStepKeyword(stepLine);
    }

    @Benchmark
    public KeywordMatcher.StepMatch matchStepKeywordStartsWithLanguageAdaptative() {
        return matcherStartsWithLanguageAdaptative.matchStepKeyword(stepLine);
    }

    @Benchmark
    public KeywordMatcher.StepMatch matchStepKeywordStartsWith() {
        return matcherStartsWith.matchStepKeyword(stepLine);
    }

    @Benchmark
    public KeywordMatcher.StepMatch matchStepKeywordStartsWithTitleKeywordWithLength() {
        return matcherStartsWithTitleKeywordWithLength.matchStepKeyword(stepLine);
    }

    @Benchmark
    public KeywordMatcher.StepMatch matchStepKeywordStartsWithTitleKeyword() {
        return matcherStartsWithTitleKeyword.matchStepKeyword(stepLine);
    }


// -------------------------------- ExampleKeyword -------------------------------------------
    @Benchmark
    public KeywordMatcher.Match matchExampleKeywordStartsWithFirstChar() {
        return matcherStartsWithFirstChar.matchExampleKeyword(exampleLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchExampleKeywordStartsWithLastChar() {
        return matcherStartsWithLastChar.matchExampleKeyword(exampleLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchExampleKeywordStartsWithFirstCharAndLastChar() {
        return matcherStartsWithFirstCharAndLastChar.matchExampleKeyword(exampleLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchExampleKeywordStartsWithFirstCharAndTitleKeywordWithLength() {
        return matcherStartsWithFirstCharAndTitleKeywordWithLength.matchExampleKeyword(exampleLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchExampleKeywordStartsWithLanguageAdaptative() {
        return matcherStartsWithLanguageAdaptative.matchExampleKeyword(exampleLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchExampleKeywordStartsWith() {
        return matcherStartsWith.matchExampleKeyword(exampleLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchExampleKeywordStartsWithTitleKeywordWithLength() {
        return matcherStartsWithTitleKeywordWithLength.matchExampleKeyword(exampleLine);
    }

    @Benchmark
    public KeywordMatcher.Match matchExampleKeywordStartsWithTitleKeyword() {
        return matcherStartsWithTitleKeyword.matchExampleKeyword(exampleLine);
    }



}
