package io.cucumber.gherkin;

import java.util.Objects;

import static io.cucumber.messages.types.StepKeywordType.ACTION;
import static io.cucumber.messages.types.StepKeywordType.CONJUNCTION;
import static io.cucumber.messages.types.StepKeywordType.CONTEXT;
import static io.cucumber.messages.types.StepKeywordType.OUTCOME;
import static io.cucumber.messages.types.StepKeywordType.UNKNOWN;

final class KeywordMatchers {

    static KeywordMatcher getKeywordMatcher(String language) {
        Objects.requireNonNull(language);
        switch (language){
<#list dialects as name, matcher>
            case "${name}":
                return new ${matcher.className}();
</#list>
            default:
                throw new ParserException.NoSuchLanguageException(language, null);
        }
    }
<#list dialects as name, matcher>
    private static final class ${matcher.className} implements KeywordMatcher {
        @Override
        public Match matchStepKeyword(GherkinLine line) {
    <#list matcher.steps as step>
            if (line.startsWith("${step.keyword}")) {
                return new Match("${step.keyword}", ${step.length}, ${step.keywordType});
            }
    </#list>
            return null;
        }
    }
</#list>
}
