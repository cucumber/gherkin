package io.cucumber.gherkin;

import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

import io.cucumber.messages.types.Location;

import static io.cucumber.gherkin.Locations.COLUMN_OFFSET;
import static io.cucumber.gherkin.Locations.atColumn;

class ParserException extends RuntimeException {
    final Location location;

    protected ParserException(String message) {
        super(message);
        location = null;
    }

    protected ParserException(String message, Location location) {
        super(createMessage(message, location));
        this.location = location;
    }

    private static String createMessage(String message, Location location) {
        if (location == null) {
            return String.format("(-1,0): %s", message);
        }
        Integer line = location.getLine();
        Integer column = location.getColumn().orElse(0);
        return String.format("(%s:%s): %s", line, column, message);
    }

    static class AstBuilderException extends ParserException {
        AstBuilderException(String message, Location location) {
            super(message, location);
        }
    }

    static class NoSuchLanguageException extends ParserException {
        NoSuchLanguageException(String language, Location location) {
            super("Language not supported: " + language, location);
        }
    }

    static class UnexpectedTokenException extends ParserException {
        String stateComment;

        final Token receivedToken;
        final List<String> expectedTokenTypes;

        UnexpectedTokenException(Token receivedToken, List<String> expectedTokenTypes, String stateComment) {
            super(getMessage(receivedToken, expectedTokenTypes), getLocation(receivedToken));
            this.receivedToken = receivedToken;
            this.expectedTokenTypes = expectedTokenTypes;
            this.stateComment = stateComment;
        }

        private static String getMessage(Token receivedToken, List<String> expectedTokenTypes) {
            return String.format("expected: %s, got '%s'",
                    String.join(", ", expectedTokenTypes),
                    receivedToken.getTokenValue()
            );
        }

        private static Location getLocation(Token receivedToken) {
            if (receivedToken.location.getColumn().isPresent()) {
                return receivedToken.location;
            }
            int column = COLUMN_OFFSET + receivedToken.line.getIndent();
            return atColumn(receivedToken.location, column);
        }
    }

    static class UnexpectedEOFException extends ParserException {
        final String stateComment;
        final List<String> expectedTokenTypes;

        UnexpectedEOFException(Token receivedToken, List<String> expectedTokenTypes, String stateComment) {
            super(getMessage(expectedTokenTypes), receivedToken.location);
            this.expectedTokenTypes = expectedTokenTypes;
            this.stateComment = stateComment;
        }

        private static String getMessage(List<String> expectedTokenTypes) {
            return String.format("unexpected end of file, expected: %s",
                    String.join(", ", expectedTokenTypes));
        }
    }

    static class CompositeParserException extends ParserException {
        final List<ParserException> errors;

        CompositeParserException(List<ParserException> errors) {
            super(getMessage(errors));
            this.errors = Collections.unmodifiableList(errors);
        }

        private static String getMessage(List<ParserException> errors) {
            if (errors == null) throw new NullPointerException("errors");
            return "Parser errors:\n" + errors.stream()
                    .map(Throwable::getMessage)
                    .collect(Collectors.joining("\n"));
        }
    }
}
