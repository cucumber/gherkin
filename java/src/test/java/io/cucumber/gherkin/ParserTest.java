package io.cucumber.gherkin;

import io.cucumber.messages.IdGenerator;
import io.cucumber.messages.types.GherkinDocument;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

class ParserTest {

    @Test
    void change_default_language() {
        TokenMatcher matcher = new TokenMatcher("no");
        IdGenerator idGenerator = new IncrementingIdGenerator();
        Parser<GherkinDocument> parser = new Parser<>(new GherkinDocumentBuilder(idGenerator, "test.feature"));

        GherkinDocument gherkinDocument = parser.parse("Egenskap: i18n support\n", matcher, "test.feature");
        assertEquals("no", gherkinDocument.getFeature().get().getLanguage());
    }
}
