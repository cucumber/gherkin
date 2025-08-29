package io.cucumber.gherkin;

import static io.cucumber.gherkin.Constants.TITLE_KEYWORD_SEPARATOR;
import static io.cucumber.gherkin.Constants.TITLE_KEYWORD_SEPARATOR_LENGTH;
import static io.cucumber.messages.types.StepKeywordType.*;

final class EnStartsWithLastChar implements KeywordMatcher {
    @Override
    public Match matchFeatureKeyword(Line line) {
        if (line.startsWith("Business Need", 13, TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Business Need", 13 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWith("Ability", 7, TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Ability", 7 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWith("Feature", 7, TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Feature", 7 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchBackgroundKeyword(Line line) {
        if (line.startsWith("Background", 10, TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Background", 10 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchRuleKeyword(Line line) {
        if (line.startsWith("Rule", 4, TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Rule", 4 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchScenarioKeyword(Line line) {
        if (line.startsWith("Scenario Template", 17, TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Scenario Template", 17 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWith("Scenario Outline", 16, TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Scenario Outline", 16 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWith("Scenario", 8, TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Scenario", 8 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWith("Example", 7, TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Example", 7 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchExampleKeyword(Line line) {
        if (line.startsWith("Scenarios", 9, TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Scenarios", 9 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWith("Examples", 8, TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Examples", 8 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public StepMatch matchStepKeyword(Line line) {
        if (line.startsWith("Given", 5, ' ')) {
            return new StepMatch("Given ", 6, CONTEXT);
        }
        if (line.startsWith("Then", 4, ' ')) {
            return new StepMatch("Then ", 5, OUTCOME);
        }
        if (line.startsWith("When", 4, ' ')) {
            return new StepMatch("When ", 5, ACTION);
        }
        if (line.startsWith("But", 3, ' ')) {
            return new StepMatch("But ", 4, CONJUNCTION);
        }
        if (line.startsWith("And", 3, ' ')) {
            return new StepMatch("And ", 4, CONJUNCTION);
        }
        if (line.startsWith("*", 1, ' ')) {
            return new StepMatch("* ", 2, UNKNOWN);
        }
        return null;
    }
}
