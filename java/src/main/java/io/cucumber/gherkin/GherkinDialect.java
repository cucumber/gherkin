package io.cucumber.gherkin;

import io.cucumber.messages.types.StepKeywordType;

import java.util.ArrayList;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import static java.util.Collections.unmodifiableList;
import static java.util.Collections.unmodifiableSet;
import static java.util.Objects.requireNonNull;

public final class GherkinDialect {
    private final String language;
    private final String name;
    private final String nativeName;
    private final List<String> featureKeywords;
    private final List<String> ruleKeywords;
    private final List<String> scenarioKeywords;
    private final List<String> scenarioOutlineKeywords;
    private final List<String> backgroundKeywords;
    private final List<String> examplesKeywords;
    private final List<String> givenKeywords;
    private final List<String> whenKeywords;
    private final List<String> thenKeywords;
    private final List<String> andKeywords;
    private final List<String> butKeywords;
    private final List<String> stepKeywords;
    private final Map<String, Set<StepKeywordType>> stepKeywordsTypes;

    GherkinDialect(
            String language,
            String name,
            String nativeName,
            List<String> featureKeywords,
            List<String> ruleKeywords,
            List<String> scenarioKeywords,
            List<String> scenarioOutlineKeywords,
            List<String> backgroundKeywords,
            List<String> examplesKeywords,
            List<String> givenKeywords,
            List<String> whenKeywords,
            List<String> thenKeywords,
            List<String> andKeywords,
            List<String> butKeywords
    ) {
        this.language = requireNonNull(language);
        this.name = requireNonNull(name);
        this.nativeName = requireNonNull(nativeName);
        this.featureKeywords = requireNonNull(featureKeywords);
        this.ruleKeywords = requireNonNull(ruleKeywords);
        this.scenarioKeywords = requireNonNull(scenarioKeywords);
        this.scenarioOutlineKeywords = requireNonNull(scenarioOutlineKeywords);
        this.backgroundKeywords = requireNonNull(backgroundKeywords);
        this.examplesKeywords = requireNonNull(examplesKeywords);
        this.givenKeywords = requireNonNull(givenKeywords);
        this.whenKeywords = requireNonNull(whenKeywords);
        this.thenKeywords = requireNonNull(thenKeywords);
        this.andKeywords = requireNonNull(andKeywords);
        this.butKeywords = requireNonNull(butKeywords);
        
        this.stepKeywords = uniqueKeywords(givenKeywords, whenKeywords, thenKeywords, andKeywords, butKeywords);
        this.stepKeywordsTypes = aggregateKeywordTypes(givenKeywords, whenKeywords, thenKeywords, andKeywords, butKeywords);
    }

    @SafeVarargs
    private static List<String> uniqueKeywords(List<String>... keywords) {
        int totalSize = 0;
        for (List<String> keyword : keywords) {
            totalSize += keyword.size();
        }
        LinkedHashSet<String> uniqueKeywords = new LinkedHashSet<>(totalSize);
        for (List<String> keyword : keywords) {
            uniqueKeywords.addAll(keyword);
        }
        return unmodifiableList(new ArrayList<>(uniqueKeywords));
    }
    
    private static Map<String, Set<StepKeywordType>> aggregateKeywordTypes(
            List<String> givenKeywords,
            List<String> whenKeywords,
            List<String> thenKeywords,
            List<String> andKeywords,
            List<String> butKeywords
    ) {
        Map<String, Set<StepKeywordType>> stepKeywordsTypes = new HashMap<>();
        addStepKeywordsTypes(stepKeywordsTypes, givenKeywords, StepKeywordType.CONTEXT);
        addStepKeywordsTypes(stepKeywordsTypes, whenKeywords, StepKeywordType.ACTION);
        addStepKeywordsTypes(stepKeywordsTypes, thenKeywords, StepKeywordType.OUTCOME);
        addStepKeywordsTypes(stepKeywordsTypes, uniqueKeywords(andKeywords, butKeywords), StepKeywordType.CONJUNCTION);
        stepKeywordsTypes.replaceAll((keyword, stepKeywordTypes) -> unmodifiableSet(stepKeywordTypes));
        return stepKeywordsTypes;
    }

    private static void addStepKeywordsTypes(Map<String, Set<StepKeywordType>> accumulator, List<String> keywords, StepKeywordType type) {
        for (String keyword : keywords) {
            if (!accumulator.containsKey(keyword)) {
                // Most keywords only have a single type.
                accumulator.put(keyword, EnumSet.of(type));
            } else {
                accumulator.get(keyword).add(type);
            }
        }
    }

    public List<String> getFeatureKeywords() {
        return featureKeywords;
    }

    public String getName() {
        return name;
    }

    public String getNativeName() {
        return nativeName;
    }

    public List<String> getRuleKeywords() {
        return ruleKeywords;
    }

    public List<String> getScenarioKeywords() {
        return scenarioKeywords;
    }

    public List<String> getScenarioOutlineKeywords() {
        return scenarioOutlineKeywords;
    }

    public List<String> getStepKeywords() {
        return stepKeywords;
    }

    /**
     * Returns the {@link StepKeywordType} for a given keyword
     * 
     * @deprecated use {{@link #getDistinctStepKeywordTypes(String)}} instead.
     * @param keyword to get the keyword type for
     * @return the keywords type
     */
    @Deprecated
    public List<StepKeywordType> getStepKeywordTypes(String keyword) {
        return new ArrayList<>(stepKeywordsTypes.get(keyword));
    }

    public Set<StepKeywordType> getDistinctStepKeywordTypes(String keyword) {
        return stepKeywordsTypes.get(keyword);
    }

    public List<String> getBackgroundKeywords() {
        return backgroundKeywords;
    }

    public List<String> getExamplesKeywords() {
        return examplesKeywords;
    }

    public List<String> getGivenKeywords() {
        return givenKeywords;
    }

    public List<String> getWhenKeywords() {
        return whenKeywords;
    }

    public List<String> getThenKeywords() {
        return thenKeywords;
    }

    public List<String> getAndKeywords() {
        return andKeywords;
    }

    public List<String> getButKeywords() {
        return butKeywords;
    }

    public String getLanguage() {
        return language;
    }
}
