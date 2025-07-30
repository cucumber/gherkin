package io.cucumber.gherkin;

import io.cucumber.messages.types.StepKeywordType;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.HashSet;
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
    private static final Comparator<String> LONGEST_TO_SHORTEST_COMPARATOR =
            (s1, s2) -> Integer.compare(s2.length(), s1.length());
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

        this.stepKeywords = distinctKeywords(givenKeywords, whenKeywords, thenKeywords, andKeywords, butKeywords);
        this.stepKeywordsTypes = aggregateKeywordTypes(givenKeywords, whenKeywords, thenKeywords, andKeywords, butKeywords);
    }

    @SafeVarargs
    private static List<String> distinctKeywords(List<String>... keywords) {
        // french is the largest dialect with 32 keywords, so we build the sorting hashset with this max size
        Set<String> uniqueKeywords = new HashSet<>(32);
        for (List<String> keyword : keywords) {
            uniqueKeywords.addAll(keyword);
        }
        List<String> sortedKeywords = new ArrayList<>(uniqueKeywords);
        sortedKeywords.sort(LONGEST_TO_SHORTEST_COMPARATOR);
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
     * @param keyword to get the keyword type for
     * @return the keywords type
     * @deprecated use {{@link #getStepKeywordTypesSet(String)}} instead.
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
