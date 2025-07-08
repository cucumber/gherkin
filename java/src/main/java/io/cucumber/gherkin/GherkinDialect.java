package io.cucumber.gherkin;

import io.cucumber.messages.types.StepKeywordType;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Set;

import static io.cucumber.messages.types.StepKeywordType.ACTION;
import static io.cucumber.messages.types.StepKeywordType.CONJUNCTION;
import static io.cucumber.messages.types.StepKeywordType.CONTEXT;
import static io.cucumber.messages.types.StepKeywordType.OUTCOME;
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
    private final Map<String, StepKeywordType> stepKeywordsType;

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

        // the step keywords are ordered by decreasing priority usage
        // (supposedly Given, Then, When, And, But, "* ") to test the
        // most probable keyword first in GherkinTokenMatcher.match_StepLine
        this.stepKeywords = distinctKeywords(givenKeywords, thenKeywords, whenKeywords, andKeywords, butKeywords);
        this.stepKeywordsTypes = aggregateKeywordTypes(givenKeywords, whenKeywords, thenKeywords, andKeywords, butKeywords);
        this.stepKeywordsType = defineSingleTypes();
    }

    private Map<String, StepKeywordType> defineSingleTypes() {
        Map<String, StepKeywordType> stepKeywordsType = new HashMap<>();
        for (Map.Entry<String, Set<StepKeywordType>> entry : stepKeywordsTypes.entrySet()) {
            Set<StepKeywordType> stepKeywordTypes = entry.getValue();
            StepKeywordType type = stepKeywordTypes.size() == 1 ? stepKeywordTypes.iterator().next() : StepKeywordType.UNKNOWN;
            stepKeywordsType.put(entry.getKey(), type);
        }
        return stepKeywordsType;
    }

    @SafeVarargs
    private static List<String> distinctKeywords(List<String>... keywords) {
        int totalSize = 0;
        for (List<String> keyword : keywords) {
            totalSize += keyword.size();
        }
        Set<String> uniqueKeywords = new LinkedHashSet<>(totalSize);
        for (List<String> keyword : keywords) {
            uniqueKeywords.addAll(keyword);
        }

        // the "* " keyword is rarely used, so having it at the
        // end would theoretically improve the performance, but
        // it's so tiny that the profiler doesn't see the difference.

        List<String> sortedKeywords = new ArrayList<>(uniqueKeywords);
        // Sort from longest to shortest
        Comparator<String> naturalOrder = Comparator.naturalOrder();
        Collections.sort(sortedKeywords, naturalOrder.reversed());
        return unmodifiableList(sortedKeywords);
    }
    
    private static Map<String, Set<StepKeywordType>> aggregateKeywordTypes(
            List<String> givenKeywords,
            List<String> whenKeywords,
            List<String> thenKeywords,
            List<String> andKeywords,
            List<String> butKeywords
    ) {
        Map<String, Set<StepKeywordType>> stepKeywordsTypes = new HashMap<>();
        addStepKeywordsTypes(stepKeywordsTypes, CONTEXT, givenKeywords);
        addStepKeywordsTypes(stepKeywordsTypes, ACTION, whenKeywords);
        addStepKeywordsTypes(stepKeywordsTypes, OUTCOME, thenKeywords);
        addStepKeywordsTypes(stepKeywordsTypes, CONJUNCTION, distinctKeywords(andKeywords, butKeywords));
        stepKeywordsTypes.replaceAll((keyword, stepKeywordTypes) -> unmodifiableSet(stepKeywordTypes));
        return stepKeywordsTypes;
    }

    private static void addStepKeywordsTypes(Map<String, Set<StepKeywordType>> accumulator, StepKeywordType type, List<String> keywords) {
        for (String keyword : keywords) {
            Set<StepKeywordType> stepKeywordTypes = accumulator.get(keyword);
            if (stepKeywordTypes == null) {
                // Most keywords only have a single type.
                accumulator.put(keyword, EnumSet.of(type));
            } else {
                stepKeywordTypes.add(type);
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
     * Returns the {@link StepKeywordType StepKeywordTypes} for a given keyword
     * 
     * @deprecated use {{@link #getStepKeywordTypesSet(String)}} instead.
     * @param keyword to get the keyword type for
     * @return the keywords type
     */
    @Deprecated
    public List<StepKeywordType> getStepKeywordTypes(String keyword) {
        Set<StepKeywordType> stepKeywordTypes = stepKeywordsTypes.get(keyword);
        if (stepKeywordTypes == null) {
            return null;
        }
        return new ArrayList<>(stepKeywordTypes);
    }

    /**
     * Returns the {@link StepKeywordType StepKeywordTypes} for a given keyword
     *
     * @param keyword to get the keyword type for
     * @return the keywords type
     */
    public Set<StepKeywordType> getStepKeywordTypesSet(String keyword) {
        requireNonNull(keyword);
        Set<StepKeywordType> stepKeywordTypes = stepKeywordsTypes.get(keyword);
        if (stepKeywordTypes == null) {
            throw new NoSuchElementException(String.format("'%s' is not part of this dialect", keyword));
        }
        return stepKeywordTypes;
    }

    public StepKeywordType getStepKeywordType(String keyword) {
        requireNonNull(keyword);
        StepKeywordType stepKeywordType = stepKeywordsType.get(keyword);
        if (stepKeywordType == null) {
            throw new NoSuchElementException(String.format("'%s' is not part of this dialect", keyword));
        }
        return stepKeywordType;
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
