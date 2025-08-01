package io.cucumber.gherkin;

import java.util.Objects;

import static io.cucumber.messages.types.StepKeywordType.ACTION;
import static io.cucumber.messages.types.StepKeywordType.CONJUNCTION;
import static io.cucumber.messages.types.StepKeywordType.CONTEXT;
import static io.cucumber.messages.types.StepKeywordType.OUTCOME;
import static io.cucumber.messages.types.StepKeywordType.UNKNOWN;

import static io.cucumber.gherkin.Constants.TITLE_KEYWORD_SEPARATOR_LENGTH;

/**
* Generated by GenerateKeywordMatchers.
*/
final class KeywordMatchers {

    static KeywordMatcher of(String language) {
        Objects.requireNonNull(language);
        switch (language){
<#list matchers as name, matcher>
            case "${name}":
                return new ${matcher.className}();
</#list>
            default:
                return null;
        }
    }
<#list matchers as name, matcher>
    private static final class ${matcher.className} implements KeywordMatcher {
        @Override
        public Match matchFeatureKeyword(Line line) {
    <#list matcher.features as feature>
            if (line.startsWithTitleKeyword("${feature.keyword}")) {
                return new Match("${feature.keyword}", ${feature.length} + TITLE_KEYWORD_SEPARATOR_LENGTH);
            }
    </#list>
            return null;
        }
        @Override
        public Match matchBackgroundKeyword(Line line) {
    <#list matcher.backgrounds as background>
            if (line.startsWithTitleKeyword("${background.keyword}")) {
                return new Match("${background.keyword}", ${background.length} + TITLE_KEYWORD_SEPARATOR_LENGTH);
            }
    </#list>
            return null;
        }
        @Override
        public Match matchRuleKeyword(Line line) {
    <#list matcher.rules as rule>
            if (line.startsWithTitleKeyword("${rule.keyword}")) {
                return new Match("${rule.keyword}", ${rule.length} + TITLE_KEYWORD_SEPARATOR_LENGTH);
            }
    </#list>
            return null;
        }
        @Override
        public Match matchScenarioKeyword(Line line) {
    <#list matcher.scenarios as scenario>
            if (line.startsWithTitleKeyword("${scenario.keyword}")) {
                return new Match("${scenario.keyword}", ${scenario.length}  + TITLE_KEYWORD_SEPARATOR_LENGTH);
            }
    </#list>
            return null;
        }
        @Override
        public Match matchExampleKeyword(Line line) {
    <#list matcher.examples as example>
            if (line.startsWithTitleKeyword("${example.keyword}")) {
                return new Match("${example.keyword}", ${example.length}  + TITLE_KEYWORD_SEPARATOR_LENGTH);
            }
    </#list>
            return null;
        }
        @Override
        public StepMatch matchStepKeyword(Line line) {
    <#list matcher.steps as step>
            if (line.startsWith("${step.keyword}")) {
                return new StepMatch("${step.keyword}", ${step.length}, ${step.keywordType} );
            }
    </#list>
            return null;
        }
    }
</#list>
}
