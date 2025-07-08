package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class GherkinDialectsTest {
    @Test
    void each_dialect_has_at_least_one_given_keyword_except_the_star() {
        for (GherkinDialect dialect : GherkinDialects.DIALECTS.values()) {
            assertTrue(dialect.getGivenKeywords().stream()
                    .anyMatch(keyword -> !keyword.equals("* ")),
                    "Dialect " + dialect.getName() + " has no given keywords");
        }
    }

}
