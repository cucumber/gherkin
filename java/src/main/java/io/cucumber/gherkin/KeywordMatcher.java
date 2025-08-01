package io.cucumber.gherkin;

import io.cucumber.messages.types.StepKeywordType;

interface KeywordMatcher {

    Match matchFeatureKeyword(Line line);
    Match matchBackgroundKeyword(Line line);
    Match matchRuleKeyword(Line line);
    Match matchScenarioKeyword(Line line);
    Match matchExampleKeyword(Line line);
    StepMatch matchStepKeyword(Line line);

    final class StepMatch {
        private final String keyword;
        private final int keywordLength;
        private final StepKeywordType keywordType;

        StepMatch(String keyword, int keywordLength, StepKeywordType keywordType) {
            this.keyword = keyword;
            this.keywordLength = keywordLength;
            this.keywordType = keywordType;
        }

        String getKeyword() {
            return keyword;
        }

        int getKeywordLength() {
            return keywordLength;
        }
        
        StepKeywordType getKeywordType() {
            return keywordType;
        }

    }
    
    final class Match {
        private final String keyword;
        private final int keywordLength;

        Match(String keyword, int keywordLength) {
            this.keyword = keyword;
            this.keywordLength = keywordLength;
        }

        String getKeyword() {
            return keyword;
        }

        int getKeywordLength() {
            return keywordLength;
        }
    }

}
