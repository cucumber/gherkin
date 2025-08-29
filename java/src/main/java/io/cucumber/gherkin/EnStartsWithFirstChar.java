package io.cucumber.gherkin;

import static io.cucumber.gherkin.Constants.TITLE_KEYWORD_SEPARATOR;
import static io.cucumber.gherkin.Constants.TITLE_KEYWORD_SEPARATOR_LENGTH;
import static io.cucumber.messages.types.StepKeywordType.*;

final class EnStartsWithFirstChar implements KeywordMatcher {
    @Override
    public Match matchFeatureKeyword(Line line) {
        if (line.isEmpty()) {
            return null;
        }
        if (line.startsWith('B', "usiness Need" + TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Business Need", 13 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWith('A', "bility" + TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Ability", 7 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWith('F', "eature" + TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Feature", 7 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchBackgroundKeyword(Line line) {
        if (line.isEmpty()) {
            return null;
        }
        if (line.startsWith('B', "ackground" + TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Background", 10 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchRuleKeyword(Line line) {
        if (line.isEmpty()) {
            return null;
        }
        if (line.startsWith('R', "ule" + TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Rule", 4 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchScenarioKeyword(Line line) {
        if (line.isEmpty()) {
            return null;
        }
        if (line.startsWith('S', "cenario Template" + TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Scenario Template", 17 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWith('S', "cenario Outline" + TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Scenario Outline", 16 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWith('S', "cenario" + TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Scenario", 8 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWith('E', "xample" + TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Example", 7 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchExampleKeyword(Line line) {
        if (line.isEmpty()) {
            return null;
        }
        if (line.startsWith('S', "cenarios" + TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Scenarios", 9 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWith('E', "xamples" + TITLE_KEYWORD_SEPARATOR)) {
            return new Match("Examples", 8 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public StepMatch matchStepKeyword(Line line) {
        if (line.isEmpty()) {
            return null;
        }
        if (line.startsWith('G', "iven ")) {
            return new StepMatch("Given ", 6, CONTEXT);
        }
        if (line.startsWith('T', "hen ")) {
            return new StepMatch("Then ", 5, OUTCOME);
        }
        if (line.startsWith('W', "hen ")) {
            return new StepMatch("When ", 5, ACTION);
        }
        if (line.startsWith('B', "ut ")) {
            return new StepMatch("But ", 4, CONJUNCTION);
        }
        if (line.startsWith('A', "nd ")) {
            return new StepMatch("And ", 4, CONJUNCTION);
        }
        if (line.startsWith('*', " ")) {
            return new StepMatch("* ", 2, UNKNOWN);
        }
        return null;
    }
}
