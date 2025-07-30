package io.cucumber.gherkin;

import io.cucumber.gherkin.KeywordMatcher.StepMatch;
import io.cucumber.messages.types.StepKeywordType;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.List;
import java.util.Optional;
import java.util.Set;
import java.util.stream.Collectors;

import static io.cucumber.gherkin.Constants.TITLE_KEYWORD_SEPARATOR_LENGTH;
import static org.assertj.core.api.Assertions.assertThat;
import static org.junit.jupiter.api.Assertions.assertAll;

class KeywordMatchersTest {

    static final GherkinDialectProvider dialectProvider = new GherkinDialectProvider();

    static List<GherkinDialect> languages() {
        return dialectProvider.getLanguages().stream()
                .map(dialectProvider::getDialect)
                .filter(Optional::isPresent)
                .map(Optional::get)
                .collect(Collectors.toList());
    }

    @ParameterizedTest
    @MethodSource("languages")
    void featureKeywordsAreConsistent(GherkinDialect dialect) {
        KeywordMatcher matcher = KeywordMatchers.of(dialect.getLanguage());
        assertThat(matcher).isNotNull();

        for (String keyword : dialect.getFeatureKeywords()) {
            Line line = new Line(keyword + ": some text");
            KeywordMatcher.Match match = matcher.matchFeatureKeyword(line);
            assertAll(
                    () -> assertThat(match.getKeyword()).isEqualTo(keyword),
                    () -> assertThat(match.getKeywordLength()).isEqualTo(keyword.length() + TITLE_KEYWORD_SEPARATOR_LENGTH)
            );
        }
    }

    @ParameterizedTest
    @MethodSource("languages")
    void backgroundKeywordsAreConsistent(GherkinDialect dialect) {
        KeywordMatcher matcher = KeywordMatchers.of(dialect.getLanguage());
        assertThat(matcher).isNotNull();

        for (String keyword : dialect.getBackgroundKeywords()) {
            Line line = new Line(keyword + ": some text");
            KeywordMatcher.Match match = matcher.matchBackgroundKeyword(line);
            assertAll(
                    () -> assertThat(match.getKeyword()).isEqualTo(keyword),
                    () -> assertThat(match.getKeywordLength()).isEqualTo(keyword.length() + TITLE_KEYWORD_SEPARATOR_LENGTH)
            );
        }
    }

    @ParameterizedTest
    @MethodSource("languages")
    void ruleKeywordsAreConsistent(GherkinDialect dialect) {
        KeywordMatcher matcher = KeywordMatchers.of(dialect.getLanguage());
        assertThat(matcher).isNotNull();

        for (String keyword : dialect.getRuleKeywords()) {
            Line line = new Line(keyword + ": some text");
            KeywordMatcher.Match match = matcher.matchRuleKeyword(line);
            assertAll(
                    () -> assertThat(match.getKeyword()).isEqualTo(keyword),
                    () -> assertThat(match.getKeywordLength()).isEqualTo(keyword.length() + TITLE_KEYWORD_SEPARATOR_LENGTH)
            );
        }
    }

    @ParameterizedTest
    @MethodSource("languages")
    void scenarioKeywordsAreConsistent(GherkinDialect dialect) {
        KeywordMatcher matcher = KeywordMatchers.of(dialect.getLanguage());
        assertThat(matcher).isNotNull();

        for (String keyword : dialect.getScenarioKeywords()) {
            Line line = new Line(keyword + ": some text");
            KeywordMatcher.Match match = matcher.matchScenarioKeyword(line);
            assertAll(
                    () -> assertThat(match.getKeyword()).isEqualTo(keyword),
                    () -> assertThat(match.getKeywordLength()).isEqualTo(keyword.length() + TITLE_KEYWORD_SEPARATOR_LENGTH)
            );
        }
        for (String keyword : dialect.getScenarioOutlineKeywords()) {
            Line line = new Line(keyword + ": some text");
            KeywordMatcher.Match match = matcher.matchScenarioKeyword(line);
            assertAll(
                    () -> assertThat(match.getKeyword()).isEqualTo(keyword),
                    () -> assertThat(match.getKeywordLength()).isEqualTo(keyword.length() + TITLE_KEYWORD_SEPARATOR_LENGTH)
            );
        }
    }

    @ParameterizedTest
    @MethodSource("languages")
    void exampleKeywordsAreConsistent(GherkinDialect dialect) {
        KeywordMatcher matcher = KeywordMatchers.of(dialect.getLanguage());
        assertThat(matcher).isNotNull();

        for (String keyword : dialect.getExamplesKeywords()) {
            Line line = new Line(keyword + ": some text");
            KeywordMatcher.Match match = matcher.matchExampleKeyword(line);
            assertAll(
                    () -> assertThat(match.getKeyword()).isEqualTo(keyword),
                    () -> assertThat(match.getKeywordLength()).isEqualTo(keyword.length() + TITLE_KEYWORD_SEPARATOR_LENGTH)
            );
        }
    }

    @ParameterizedTest
    @MethodSource("languages")
    void stepKeywordsAreConsistent(GherkinDialect dialect) {
        KeywordMatcher matcher = KeywordMatchers.of(dialect.getLanguage());
        assertThat(matcher).isNotNull();

        for (String keyword : dialect.getStepKeywords()) {
            Line line = new Line(keyword + "some text");
            StepMatch match = matcher.matchStepKeyword(line);

            assertAll(
                    () -> assertThat(match.getKeyword()).isEqualTo(keyword),
                    () -> assertThat(match.getKeywordLength()).isEqualTo(keyword.length()),
                    () -> {
                        Set<StepKeywordType> stepKeywordTypesSet = dialect.getStepKeywordTypesSet(keyword);
                        StepKeywordType expected = stepKeywordTypesSet.size() != 1 ? StepKeywordType.UNKNOWN : stepKeywordTypesSet.iterator().next();
                        assertThat(match.getKeywordType()).isEqualTo(expected);
                    });
        }
    }
}
