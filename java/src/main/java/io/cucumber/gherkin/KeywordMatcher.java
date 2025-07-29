package io.cucumber.gherkin;

import io.cucumber.messages.types.StepKeywordType;

interface KeywordMatcher {

    Match matchStepKeyword(GherkinLine line);
    
    final class Match {
        private final String keyword;
        private final StepKeywordType keywordType;

        Match(String keyword, StepKeywordType keywordType) {
            this.keyword = keyword;
            this.keywordType = keywordType;
        }

        String getKeyword() {
            return keyword;
        }

        StepKeywordType getKeywordType() {
            return keywordType;
        }
    }

}
