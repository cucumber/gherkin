package io.cucumber.gherkin;

import io.cucumber.messages.types.StepKeywordType;
import org.junit.jupiter.api.Test;

import java.util.List;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.*;

class GherkinDialectTest {

    @Test
    void getDistinctStepKeywordTypes_star_has_multiple_stepKeywordTypes() {
        // Given the default Gherkin dialect (English)
        GherkinDialect dialect = new GherkinDialectProvider().getDefaultDialect();

        // When I get the step keyword types
        Set<StepKeywordType> stepKeywordTypes = dialect.getDistinctStepKeywordTypes("* ");

        // Then multiple types are possible
        assertEquals(4, stepKeywordTypes.size());
    }

    @Test
    void getName_returns_the_name_of_the_dialect() {
        // Given the default Gherkin dialect (English)
        GherkinDialect dialect = new GherkinDialectProvider().getDefaultDialect();

        // When I get the name of the dialect
        String name = dialect.getName();

        // Then the name is "English"
        assertEquals("English", name);
    }
}
