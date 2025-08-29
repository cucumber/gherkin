package io.cucumber.gherkin;

import static io.cucumber.gherkin.Constants.TITLE_KEYWORD_SEPARATOR;
import static io.cucumber.gherkin.Constants.TITLE_KEYWORD_SEPARATOR_LENGTH;
import static io.cucumber.messages.types.StepKeywordType.*;

final class EnStartsWithLanguageAdaptative implements KeywordMatcher {
    @Override
    public Match matchFeatureKeyword(Line line) {
        // first char
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
        // first char + titleKeywordWithLength (=last char with a fixed last char, so there is less parameter passing)
        if (line.startsWith('B', "ackground", 10)) {
            return new Match("Background", 10 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchRuleKeyword(Line line) {
        // first char + titleKeywordWithLength (=last char with a fixed last char, so there is less parameter passing)
        if (line.startsWith('R', "ule", 4)) {
            return new Match("Rule", 4 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchScenarioKeyword(Line line) {
        // titleKeyword (=last char with a fixed last char, so there is less parameter passing)
        if (line.startsWithTitleKeyword("Scenario Template", 17)) {
            return new Match("Scenario Template", 17 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWithTitleKeyword("Scenario Outline", 16)) {
            return new Match("Scenario Outline", 16 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWithTitleKeyword("Scenario", 8)) {
            return new Match("Scenario", 8 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWithTitleKeyword("Example", 7)) {
            return new Match("Example", 7 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchExampleKeyword(Line line) {
        // first char and last char can work, so we select last char because rule/scenario/example are frequently used in chain in Parser
        if (line.startsWith('S', "cenarios", 9)) {
            return new Match("Scenarios", 9 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWith('E', "xamples", 8)) {
            return new Match("Examples", 8 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public StepMatch matchStepKeyword(Line line) {
        // startsWith
        if (line.startsWith("Given ")) {
            return new StepMatch("Given ", 6, CONTEXT);
        }
        if (line.startsWith("Then ")) {
            return new StepMatch("Then ", 5, OUTCOME);
        }
        if (line.startsWith("When ")) {
            return new StepMatch("When ", 5, ACTION);
        }
        if (line.startsWith("But ")) {
            return new StepMatch("But ", 4, CONJUNCTION);
        }
        if (line.startsWith("And ")) {
            return new StepMatch("And ", 4, CONJUNCTION);
        }
        if (line.startsWith("* ")) {
            return new StepMatch("* ", 2, UNKNOWN);
        }
        return null;
    }
}
