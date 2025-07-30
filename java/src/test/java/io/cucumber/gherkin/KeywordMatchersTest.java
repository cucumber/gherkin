package io.cucumber.gherkin;

import io.cucumber.messages.types.StepKeywordType;
import org.junit.jupiter.api.Test;

import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertEquals;

class KeywordMatchersTest {

    final GherkinDialectProvider dialectProvider = new GherkinDialectProvider();
    
    @Test
    void stepKeywordsAreConsistentWithGherkinDialect(){
        for (String language : dialectProvider.getLanguages()) {
            GherkinDialect dialect = dialectProvider.getDialect(language).get();
            KeywordMatcher matcher = KeywordMatchers.getKeywordMatcher(language);
            for (String keyword : dialect.getStepKeywords()) {
                GherkinLine line = new GherkinLine(keyword + "some text");
                KeywordMatcher.StepMatch match = matcher.matchStepKeyword(line);
                assertEquals(keyword, match.getKeyword());
                assertEquals(keyword.length(), match.getKeywordLength());
                Set<StepKeywordType> stepKeywordTypesSet = dialect.getStepKeywordTypesSet(keyword);
                StepKeywordType expected = stepKeywordTypesSet.size() != 1 ? StepKeywordType.UNKNOWN : stepKeywordTypesSet.iterator().next();
                assertEquals(expected, match.getKeywordType());
            }
        }
    }
}
