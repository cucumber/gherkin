package io.cucumber.gherkin.dialects;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;
import freemarker.template.TemplateExceptionHandler;

import java.io.IOException;
import java.io.Reader;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.LinkedHashMap;
import java.util.Locale;
import java.util.Map;
import java.util.TreeMap;

import static java.nio.file.Files.newBufferedReader;
import static java.nio.file.Files.newBufferedWriter;
import static java.nio.file.StandardOpenOption.CREATE;
import static java.nio.file.StandardOpenOption.TRUNCATE_EXISTING;
import static java.util.Comparator.naturalOrder;

/* 
 * This class generates the GherkinDialects class using the FreeMarker
 * template engine and provided templates.
 */
class GenerateGherkinDialects {

    static void generate(String baseDirectory, String packagePath) throws Exception {
        Path path = Paths.get(baseDirectory, packagePath,  "GherkinDialects.java");

        Template dialectsSource = readTemplate();

        Map<String, Map<String, Object>> binding = new LinkedHashMap<>();
        binding.put("dialects", readGherkinLanguages());

        try {
            Files.createDirectories(path.getParent());
            dialectsSource.process(binding, newBufferedWriter(path, CREATE, TRUNCATE_EXISTING));
        } catch (IOException | TemplateException e) {
            throw new RuntimeException(e);
        }
    }

    private static Template readTemplate() throws IOException {
        Configuration cfg = new Configuration(Configuration.VERSION_2_3_21);
        cfg.setClassForTemplateLoading(GenerateGherkinDialects.class, "templates");
        cfg.setDefaultEncoding("UTF-8");
        cfg.setLocale(Locale.US);
        cfg.setTemplateExceptionHandler(TemplateExceptionHandler.RETHROW_HANDLER);
        return cfg.getTemplate("gherkin-dialects.java.ftl");
    }

    private static Map<String, Object> readGherkinLanguages() throws IOException {
        ObjectMapper objectMapper = new ObjectMapper();
        TypeReference<Map<String, Object>> mapObjectType = new TypeReference<Map<String, Object>>() { };
        try (Reader reader = newBufferedReader(Paths.get("../gherkin-languages.json"))){
            Map<String, Object> sorted = new TreeMap<>(naturalOrder());
            sorted.putAll(objectMapper.readValue(reader, mapObjectType));
            return sorted;
        }
    }
}
