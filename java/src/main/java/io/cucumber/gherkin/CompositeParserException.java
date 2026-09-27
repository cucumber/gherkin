package io.cucumber.gherkin;

import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

final class CompositeParserException extends Exception {
    final List<ParserError> errors;

    CompositeParserException(ParserError error) {
        this(Collections.singletonList(error));
    }

    CompositeParserException(List<ParserError> errors) {
        super(getMessage(errors));
        this.errors = List.copyOf(errors);
    }

    private static String getMessage(List<ParserError> errors) {
        if (errors.size() == 1) {
            return errors.get(0).getMessage();
        }
        return "Parser errors:\n" + errors.stream()
                .map(ParserError::getMessage)
                .collect(Collectors.joining("\n"));
    }
}
