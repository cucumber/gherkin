package io.cucumber.gherkin;

class EnKeywordMatcher implements KeywordMatcher {

    private final String keyword0 = "Given ";
    private final String keyword1 = "Then ";
    private final String keyword2 = "When ";
    private final String keyword3 = "But ";
    private final String keyword4 = "And ";
    private final String keyword5 = "* ";

    @Override
    public String matchStepKeyword(GherkinLine line) {
        if (line.startsWith(keyword0)) {
            return keyword0;
        }

        if (line.startsWith(keyword1)) {
            return keyword1;
        }

        if (line.startsWith(keyword2)) {
            return keyword2;
        }

        if (line.startsWith(keyword3)) {
            return keyword3;
        }

        if (line.startsWith(keyword4)) {
            return keyword4;
        }

        if (line.startsWith(keyword5)) {
            return keyword5;
        }
        
        return null;
    }
}
