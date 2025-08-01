package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

@Deprecated
class GherkinDialectProviderTest {
    
    @Test
    void provides_emoji_dialect() {
        GherkinDialect em = GherkinDialects.getDialect("em").orElseThrow(() -> new RuntimeException("Missing dialect: em"));
        String actual = em.getScenarioKeywords().get(0);
        assertEquals(1, actual.codePointCount(0, actual.length()));
    }

    @Test
    void provides_language_list() {
        Set<String> languages = GherkinDialects.getLanguages();
        assertTrue(languages.contains("en"));
    }

    @Test
    void provides_native_name_which_is_used_in_cucumber_jvm_code_generation() {
        GherkinDialect no = GherkinDialects.getDialect("no").orElseThrow(() -> new RuntimeException("Missing dialect: no"));
        assertEquals("norsk", no.getNativeName());
    }
}
