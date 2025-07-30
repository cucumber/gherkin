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
<#list matchers as name, matcher>
            case "${name}":
                return new ${matcher.className}();
</#list>
            default:
                throw new ParserException.NoSuchLanguageException(language, null);
        }
    }
<#list matchers as name, matcher>
    private static final class ${matcher.className} implements KeywordMatcher {
        @Override
        public Match matchFeatureKeyword(GherkinLine line) {
    <#list matcher.features as feature>
            if (line.startsWith("${feature.keyword}")) {
                return new Match("${feature.keyword}", ${feature.length});
            }
    </#list>
            return null;
        }
        @Override
        public Match matchBackgroundKeyword(GherkinLine line) {
    <#list matcher.backgrounds as background>
            if (line.startsWith("${background.keyword}")) {
                return new Match("${background.keyword}", ${background.length});
            }
    </#list>
            return null;
        }
        @Override
        public Match matchRuleKeyword(GherkinLine line) {
    <#list matcher.rules as rule>
            if (line.startsWith("${rule.keyword}")) {
                return new Match("${rule.keyword}", ${rule.length});
            }
    </#list>
            return null;
        }
        @Override
        public Match matchScenarioKeyword(GherkinLine line) {
    <#list matcher.scenarios as scenario>
            if (line.startsWith("${scenario.keyword}")) {
                return new Match("${scenario.keyword}", ${scenario.length});
            }
    </#list>
            return null;
        }
        @Override
        public Match matchExampleKeyword(GherkinLine line) {
    <#list matcher.examples as example>
            if (line.startsWith("${example.keyword}")) {
                return new Match("${example.keyword}", ${example.length});
            }
    </#list>
            return null;
        }
        @Override
        public StepMatch matchStepKeyword(GherkinLine line) {
    <#list matcher.steps as step>
            if (line.startsWith("${step.keyword}")) {
                return new StepMatch("${step.keyword}", ${step.length}, ${step.keywordType});
            }
    </#list>
            return null;
        }
    }
</#list>
}
