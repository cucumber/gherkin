package io.cucumber.gherkin;

import io.cucumber.messages.types.StepKeywordType;

interface KeywordMatcher {

    Match matchStepKeyword(GherkinLine line);
    
    final class Match {
        private final String keyword;
        private final int keywordLength;
        private final StepKeywordType keywordType;

        Match(String keyword, int keywordLength, StepKeywordType keywordType) {
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

}
