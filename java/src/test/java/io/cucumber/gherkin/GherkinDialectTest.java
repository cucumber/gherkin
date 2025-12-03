package io.cucumber.gherkin;

import io.cucumber.messages.types.StepKeywordType;
import org.junit.jupiter.api.Test;

import java.util.List;
import java.util.NoSuchElementException;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

class GherkinDialectTest {

    final GherkinDialect dialect = GherkinDialects.getDialect(Constants.DEFAULT_LANGUAGE)
            .orElseThrow(() -> new IllegalStateException("No default dialect"));
    
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

    @Test
    void keywords_are_sorted_from_longest_to_shortest() {
        // Given a Gherkin dialect for French with a lot of keywords
        GherkinDialect dialect = GherkinDialects.getDialect("fr")
                .orElseThrow(() -> new IllegalStateException("No fr dialect"));

        // When I get the keywords
        List<String> keywords = dialect.getStepKeywords();

        // Then the keywords are sorted from longest to shortest
        String[] sortedKeywords = keywords.toArray(new String[0]);
        for (int i = 0; i < sortedKeywords.length - 1; i++) {
            assertTrue(sortedKeywords[i].length() >= sortedKeywords[i + 1].length(),
                    "Expected " + sortedKeywords[i] + " to be longer than or equal to " + sortedKeywords[i + 1]);
        }
    }
}
