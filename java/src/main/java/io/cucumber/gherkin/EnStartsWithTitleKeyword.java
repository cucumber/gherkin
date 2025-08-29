package io.cucumber.gherkin;

import static io.cucumber.gherkin.Constants.TITLE_KEYWORD_SEPARATOR_LENGTH;
import static io.cucumber.messages.types.StepKeywordType.*;

final class EnStartsWithTitleKeyword implements KeywordMatcher {
    @Override
    public Match matchFeatureKeyword(Line line) {
        if (line.startsWithTitleKeyword("Business Need")) {
            return new Match("Business Need", 13 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWithTitleKeyword("Ability")) {
            return new Match("Ability", 7 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWithTitleKeyword("Feature")) {
            return new Match("Feature", 7 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchBackgroundKeyword(Line line) {
        if (line.startsWithTitleKeyword("Background")) {
            return new Match("Background", 10 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchRuleKeyword(Line line) {
        if (line.startsWithTitleKeyword("Rule")) {
            return new Match("Rule", 4 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchScenarioKeyword(Line line) {
        if (line.startsWithTitleKeyword("Scenario Template")) {
            return new Match("Scenario Template", 17 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWithTitleKeyword("Scenario Outline")) {
            return new Match("Scenario Outline", 16 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWithTitleKeyword("Scenario")) {
            return new Match("Scenario", 8 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWithTitleKeyword("Example")) {
            return new Match("Example", 7 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public Match matchExampleKeyword(Line line) {
        if (line.startsWithTitleKeyword("Scenarios")) {
            return new Match("Scenarios", 9 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        if (line.startsWithTitleKeyword("Examples")) {
            return new Match("Examples", 8 + TITLE_KEYWORD_SEPARATOR_LENGTH);
        }
        return null;
    }

    @Override
    public StepMatch matchStepKeyword(Line line) {
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
