package io.cucumber.gherkin;

import io.cucumber.messages.types.StepKeywordType;
import org.junit.jupiter.api.Test;

import java.util.NoSuchElementException;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.*;

class GherkinDialectTest {

    final GherkinDialect dialect = new GherkinDialectProvider().getDefaultDialect();
    
    @Test
    void getDistinctStepKeywordTypes_star_has_multiple_stepKeywordTypes() {
        // When I get the step keyword types
        Set<StepKeywordType> stepKeywordTypes = dialect.getStepKeywordTypesSet("* ");

        // Then multiple types are possible
        assertEquals(4, stepKeywordTypes.size());
    }
    
    @Test
    void getDistinctStepKeywordTypes_Given_has_multiple_stepKeywordTypes() {
        // When I get the step keyword types
        Set<StepKeywordType> stepKeywordTypes = dialect.getStepKeywordTypesSet("Given ");

        // Then multiple types are possible
        assertEquals(1, stepKeywordTypes.size());
    }
    
    @Test
    void getDistinctStepKeywordTypes_null_throws() {
        // When I get the step keyword types
        assertThrows(NullPointerException.class, () -> dialect.getStepKeywordTypesSet(null));
    }

    @Test
    void getDistinctStepKeywordTypes_unknown_throws() {
        // When I get the step keyword types
        assertThrows(NoSuchElementException.class, () -> dialect.getStepKeywordTypesSet("Unknown"));
    }

    @Test
    void getName_returns_the_name_of_the_dialect() {
        // When I get the name of the dialect
        String name = dialect.getName();

        // Then the name is "English"
        assertEquals("English", name);
    }
}
