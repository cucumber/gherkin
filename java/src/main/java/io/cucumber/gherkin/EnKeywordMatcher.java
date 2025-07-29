package io.cucumber.gherkin;

import io.cucumber.messages.types.StepKeywordType;

class EnKeywordMatcher implements KeywordMatcher {

    private final String keyword0 = "Given ";
    private final int keyword0Length = 6;
    private final StepKeywordType keywordType0 = StepKeywordType.CONTEXT;
    private final String keyword1 = "Then ";
    private final int keyword1Length = 5;
    private final StepKeywordType keywordType1 = StepKeywordType.OUTCOME;
    private final String keyword2 = "When ";
    private final int keyword2Length = 5;
    private final StepKeywordType keywordType2 = StepKeywordType.ACTION;
    private final String keyword3 = "But ";
    private final int keyword3Length = 4;
    private final StepKeywordType keywordType3 = StepKeywordType.CONJUNCTION;
    private final String keyword4 = "And ";
    private final int keyword4Length = 4;
    private final StepKeywordType keywordType4 = StepKeywordType.CONJUNCTION;
    private final String keyword5 = "* ";
    private final int keyword5Length = 2;
    private final StepKeywordType keywordType5 = StepKeywordType.UNKNOWN;

    @Override
    public Match matchStepKeyword(GherkinLine line) {
        if (line.startsWith(keyword0)) {
            // Object not actually created.
            return new Match(keyword0, keyword0Length, keywordType0);
        }

        if (line.startsWith(keyword1)) {
            return new Match(keyword1, keyword1Length, keywordType1);
        }

        if (line.startsWith(keyword2)) {
            return new Match(keyword2, keyword2Length, keywordType2);
        }

        if (line.startsWith(keyword3)) {
            return new Match(keyword3, keyword3Length, keywordType3);
        }

        if (line.startsWith(keyword4)) {
            return new Match(keyword4, keyword4Length, keywordType4);
        }

        if (line.startsWith(keyword5)) {
            return new Match(keyword5, keyword5Length, keywordType5);
        }
        
        return null;
    }
}
