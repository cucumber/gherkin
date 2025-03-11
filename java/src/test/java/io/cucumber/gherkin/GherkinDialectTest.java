package io.cucumber.gherkin;

import io.cucumber.messages.types.StepKeywordType;
import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class GherkinDialectTest {

    @Test
    void getStepKeywordTypes_star_has_multiple_stepKeywordTypes() {
        // Given the default Gherkin dialect (English)
        GherkinDialect dialect = new GherkinDialectProvider().getDefaultDialect();

        // When I get the step keyword types
        List<StepKeywordType> stepKeywordTypes = dialect.getStepKeywordTypes("* ");

        // Then multiple types are possible
        assertEquals(4, stepKeywordTypes.size());
    }
}
