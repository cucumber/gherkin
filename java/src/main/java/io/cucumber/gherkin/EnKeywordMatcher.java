package io.cucumber.gherkin;

import io.cucumber.messages.types.StepKeywordType;

class EnKeywordMatcher implements KeywordMatcher {

    private final String keyword0 = "Given ";
    private final StepKeywordType keywordType0 = StepKeywordType.CONTEXT;
    private final String keyword1 = "Then ";
    private final StepKeywordType keywordType1 = StepKeywordType.OUTCOME;
    private final String keyword2 = "When ";
    private final StepKeywordType keywordType2 = StepKeywordType.ACTION;
    private final String keyword3 = "But ";
    private final StepKeywordType keywordType3 = StepKeywordType.CONJUNCTION;
    private final String keyword4 = "And ";
    private final StepKeywordType keywordType4 = StepKeywordType.CONJUNCTION;
    private final String keyword5 = "* ";
    private final StepKeywordType keywordType5 = StepKeywordType.UNKNOWN;

    @Override
    public Match matchStepKeyword(GherkinLine line) {
        if (line.startsWith(keyword0)) {
            // Object not actually created.
            return new Match(keyword0, keywordType0);
        }

        if (line.startsWith(keyword1)) {
            return new Match(keyword1, keywordType1);
        }

        if (line.startsWith(keyword2)) {
            return new Match(keyword2, keywordType2);
        }

        if (line.startsWith(keyword3)) {
            return new Match(keyword3, keywordType3);
        }

        if (line.startsWith(keyword4)) {
            return new Match(keyword4, keywordType4);
        }

        if (line.startsWith(keyword5)) {
            return new Match(keyword5, keywordType5);
        }
        
        return null;
    }
}
