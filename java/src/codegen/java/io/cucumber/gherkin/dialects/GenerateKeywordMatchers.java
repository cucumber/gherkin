package io.cucumber.gherkin.dialects;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;
import freemarker.template.TemplateExceptionHandler;
import io.cucumber.messages.types.StepKeywordType;

import java.io.IOException;
import java.io.Reader;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.stream.Collectors;

import static io.cucumber.messages.types.StepKeywordType.ACTION;
import static io.cucumber.messages.types.StepKeywordType.CONJUNCTION;
import static io.cucumber.messages.types.StepKeywordType.CONTEXT;
import static io.cucumber.messages.types.StepKeywordType.OUTCOME;
import static io.cucumber.messages.types.StepKeywordType.UNKNOWN;
import static java.nio.file.Files.newBufferedReader;
import static java.nio.file.Files.newBufferedWriter;
import static java.nio.file.StandardOpenOption.CREATE;
import static java.nio.file.StandardOpenOption.TRUNCATE_EXISTING;
import static java.util.Comparator.naturalOrder;
import static java.util.Map.Entry.comparingByKey;
import static java.util.Objects.requireNonNull;

/*
 * This class generates the KeywordMatchers class using the FreeMarker
 * template engine and provided templates.
 */
class GenerateKeywordMatchers {

    private static final Comparator<String> LONGEST_TO_SHORTEST_COMPARATOR =
            (s1, s2) -> Integer.compare(s2.length(), s1.length());

    static void generate(String baseDirectory, String packagePath) throws Exception {
        Path path = Paths.get(baseDirectory, packagePath, "KeywordMatchers.java");

        Template dialectsSource = readTemplate();

        Map<String, Map<String, Object>> binding = new LinkedHashMap<>();
        Map<String, Object> dialects = readGherkinLanguages();
        Map<String, Object> matcherModels = createMatcherModels(dialects);
        binding.put("matchers", matcherModels);

        try {
            Files.createDirectories(path.getParent());
            dialectsSource.process(binding, newBufferedWriter(path, CREATE, TRUNCATE_EXISTING));
        } catch (IOException | TemplateException e) {
            throw new RuntimeException(e);
        }
    }

    private static Template readTemplate() throws IOException {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_21);
        cfg.setClassForTemplateLoading(GenerateKeywordMatchers.class, "templates");
        cfg.setDefaultEncoding("UTF-8");
        cfg.setLocale(Locale.US);
        cfg.setTemplateExceptionHandler(TemplateExceptionHandler.RETHROW_HANDLER);
        return cfg.getTemplate("keyword-matchers.java.ftl");
    }

    private static Map<String, Object> readGherkinLanguages() throws IOException {
        ObjectMapper objectMapper = new ObjectMapper();
        TypeReference<Map<String, Object>> mapObjectType = new TypeReference<>() {
        };
        try (Reader reader = newBufferedReader(Paths.get("../gherkin-languages.json"))) {
            Map<String, Object> sorted = new TreeMap<>(naturalOrder());
            sorted.putAll(objectMapper.readValue(reader, mapObjectType));
            return sorted;
        }
    }

    @SuppressWarnings("unchecked")
    private static Map<String, Object> createMatcherModels(Map<String, Object> dialects) {
        return dialects.entrySet()
                .stream()
                .sorted(comparingByKey())
                .collect(Collectors.toMap(
                        Map.Entry::getKey, entry -> matcherModel(
                                entry.getKey(),
                                (Map<String, Object>) entry.getValue()),
                        GenerateKeywordMatchers::requireUniqueKeys,
                        LinkedHashMap::new
                ));
    }

    private static boolean requireUniqueKeys(Object a, Object b) {
        throw new IllegalStateException("Duplicate keys " + a + " and " + b);
    }

    @SuppressWarnings("unchecked")
    private static Map<String, Object> matcherModel(String language, Map<String, Object> dialect) {
        String normalizedLanguage = getNormalizedLanguage(language);
        Map<String, Object> model = new HashMap<>();
        model.put("className", capitalize(normalizedLanguage));

        List<String> featureKeywords = distinctSortedKeywords(
                (List<String>) requireNonNull(dialect.get("feature"))
        );
        model.put("features", featureKeywords.stream().map(keyword -> {
            Map<String, Object> entry = new HashMap<>();
            entry.put("keyword", keyword);
            entry.put("length", keyword.length());
            return entry;
        }).collect(Collectors.toList()));

        List<String> backgroundKeywords = distinctSortedKeywords(
                (List<String>) requireNonNull(dialect.get("background"))
        );
        model.put("backgrounds", backgroundKeywords.stream().map(keyword -> {
            Map<String, Object> entry = new HashMap<>();
            entry.put("keyword", keyword);
            entry.put("length", keyword.length());
            return entry;
        }).collect(Collectors.toList()));

        List<String> ruleKeywords = distinctSortedKeywords(
                (List<String>) requireNonNull(dialect.get("rule"))
        );
        model.put("rules", ruleKeywords.stream().map(keyword -> {
            Map<String, Object> entry = new HashMap<>();
            entry.put("keyword", keyword);
            entry.put("length", keyword.length());
            return entry;
        }).collect(Collectors.toList()));

        List<String> scenarioKeywords = distinctSortedKeywords(
                (List<String>) requireNonNull(dialect.get("scenario")),
                (List<String>) requireNonNull(dialect.get("scenarioOutline"))
        );
        model.put("scenarios", scenarioKeywords.stream().map(keyword -> {
            Map<String, Object> entry = new HashMap<>();
            entry.put("keyword", keyword);
            entry.put("length", keyword.length());
            return entry;
        }).collect(Collectors.toList()));

        List<String> exampleKeywords = distinctSortedKeywords(
                (List<String>) requireNonNull(dialect.get("examples"))
        );
        model.put("examples", exampleKeywords.stream().map(keyword -> {
            Map<String, Object> entry = new HashMap<>();
            entry.put("keyword", keyword);
            entry.put("length", keyword.length());
            return entry;
        }).collect(Collectors.toList()));

        Map<String, StepKeywordType> aggregateKeywordTypes = aggregateKeywordTypes(
                (List<String>) requireNonNull(dialect.get("given")),
                (List<String>) requireNonNull(dialect.get("when")),
                (List<String>) requireNonNull(dialect.get("then")),
                (List<String>) requireNonNull(dialect.get("and")),
                (List<String>) requireNonNull(dialect.get("but"))
        );
        List<String> stepKeywords = distinctSortedKeywords(
                (List<String>) requireNonNull(dialect.get("given")),
                (List<String>) requireNonNull(dialect.get("when")),
                (List<String>) requireNonNull(dialect.get("then")),
                (List<String>) requireNonNull(dialect.get("and")),
                (List<String>) requireNonNull(dialect.get("but"))
        );
        model.put("steps", stepKeywords.stream().map(keyword -> {
            Map<String, Object> entry = new HashMap<>();
            entry.put("keyword", keyword);
            entry.put("length", keyword.length());
            entry.put("keywordType", requireNonNull(aggregateKeywordTypes.get(keyword)).name());
            return entry;
        }).collect(Collectors.toList()));

        return model;
    }

    private static String capitalize(String str) {
        return str.substring(0, 1).toUpperCase(Locale.US) + str.substring(1);
    }

    private static String getNormalizedLanguage(String language) {
        return language.replaceAll("[\\s-]", "_").toLowerCase(Locale.US);
    }

    @SafeVarargs
    private static List<String> distinctSortedKeywords(List<String>... keywords) {
        // french is the largest dialect with 32 keywords, so we build the sorting hashset with this max size
        Set<String> uniqueKeywords = new HashSet<>(32);
        for (List<String> keyword : keywords) {
            uniqueKeywords.addAll(keyword);
        }
        List<String> sortedKeywords = new ArrayList<>(uniqueKeywords);
        sortedKeywords.sort(LONGEST_TO_SHORTEST_COMPARATOR);
        return sortedKeywords;
    }

    private static Map<String, StepKeywordType> aggregateKeywordTypes(
            List<String> givenKeywords,
            List<String> whenKeywords,
            List<String> thenKeywords,
            List<String> andKeywords,
            List<String> butKeywords
    ) {
        Map<String, StepKeywordType> stepKeywordsTypes = new HashMap<>();
        mergeKeywordTypes(stepKeywordsTypes, CONTEXT, givenKeywords);
        mergeKeywordTypes(stepKeywordsTypes, ACTION, whenKeywords);
        mergeKeywordTypes(stepKeywordsTypes, OUTCOME, thenKeywords);
        mergeKeywordTypes(stepKeywordsTypes, CONJUNCTION, distinctSortedKeywords(andKeywords, butKeywords));
        return stepKeywordsTypes;
    }

    private static void mergeKeywordTypes(Map<String, StepKeywordType> accumulator, StepKeywordType type, List<String> keywords) {
        for (String keyword : keywords) {
            StepKeywordType existing = accumulator.get(keyword);
            if (existing == null) {
                accumulator.put(keyword, type);
            } else {
                // Type is unknown if there are multiple applicable types.
                accumulator.put(keyword, UNKNOWN);
            }
        }
    }
}
