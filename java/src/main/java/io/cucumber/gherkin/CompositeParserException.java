package io.cucumber.gherkin;

import java.util.List;
import java.util.stream.Collectors;

final class CompositeParserException extends Exception {
    final List<ParserException> errors;

    CompositeParserException(List<ParserException> errors) {
        super(getMessage(errors));
        this.errors = List.copyOf(errors);
    }

    private static String getMessage(List<ParserException> errors) {
        if (errors.size() == 1) {
            return errors.get(0).getMessage();
        }
        return "Parser errors:\n" + errors.stream()
                .map(Throwable::getMessage)
                .collect(Collectors.joining("\n"));
    }
}
