package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import java.util.Collection;
import java.util.Optional;
import java.util.Set;

import static org.assertj.core.api.Assertions.assertThat;

class GherkinDialectsTest {

    @Test
    void provides_emoji_dialect() {
        Optional<GherkinDialect> dialect = GherkinDialects.getDialect("em");
        assertThat(dialect).isPresent().get()
                .extracting(GherkinDialect::getLanguage)
                .isEqualTo("em");
    }

    @Test
    void provides_language_list() {
        Set<String> languages = GherkinDialects.getLanguages();
        assertThat(languages).contains("en");
    }

    @Test
    void provides_dialect_list() {
        Collection<GherkinDialect> dialects = GherkinDialects.getDialects();
        assertThat(dialects).extracting(GherkinDialect::getLanguage).contains("en");
    }

    @Test
    void provides_native_name() {
        // used by cucumber-jvm in code generation
        Optional<GherkinDialect> dialect = GherkinDialects.getDialect("no");
        assertThat(dialect).isPresent().get()
                .extracting(GherkinDialect::getNativeName)
                .isEqualTo("norsk");
    }
}
