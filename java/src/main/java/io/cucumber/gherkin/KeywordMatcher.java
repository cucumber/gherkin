package io.cucumber.gherkin;

import io.cucumber.messages.types.StepKeywordType;
import org.jspecify.annotations.Nullable;

interface KeywordMatcher {

    @Nullable Match matchFeatureKeyword(Line line);
    @Nullable Match matchBackgroundKeyword(Line line);
    @Nullable Match matchRuleKeyword(Line line);
    @Nullable Match matchScenarioKeyword(Line line);
    @Nullable Match matchExampleKeyword(Line line);
    @Nullable StepMatch matchStepKeyword(Line line);

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
