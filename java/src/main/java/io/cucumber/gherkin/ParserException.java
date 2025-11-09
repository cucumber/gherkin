package io.cucumber.gherkin;

import java.util.Collections;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

import io.cucumber.messages.types.Location;
import org.jspecify.annotations.NonNull;
import org.jspecify.annotations.Nullable;

import static io.cucumber.gherkin.Locations.COLUMN_OFFSET;
import static io.cucumber.gherkin.Locations.atColumn;
import static java.util.Objects.requireNonNull;

class ParserException extends RuntimeException {
    final @Nullable Location location;

    protected ParserException(String message) {
        super(message);
        location = null;
    }

    protected ParserException(String message, @Nullable Location location) {
        super(createMessage(message, location));
        this.location = location;
    }

    private static String createMessage(String message, @Nullable Location location) {
        if (location == null) {
            return String.format("(-1,0): %s", message);
        }
        Long line = location.getLine();
        Long column = location.getColumn().orElse(0L);
        return String.format("(%s:%s): %s", line, column, message);
    }

    static final class AstBuilderException extends ParserException {
        AstBuilderException(String message, Location location) {
            super(message, location);
        }
    }

    static final class NoSuchLanguageException extends ParserException {
        NoSuchLanguageException(String language, @Nullable Location location) {
            super("Language not supported: " + language, location);
        }
    }

    static final class UnexpectedTokenException extends ParserException {
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
            int column = COLUMN_OFFSET + requireNonNull(receivedToken.line).getIndent();
            return atColumn(receivedToken.location, column);
        }
    }

    static final class UnexpectedEOFException extends ParserException {
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

    static final class CompositeParserException extends ParserException {
        final List<ParserException> errors;

        CompositeParserException(List<ParserException> errors) {
            super(getMessage(errors));
            this.errors = Collections.unmodifiableList(errors);
        }

        private static String getMessage(List<ParserException> errors) {
            return "Parser errors:\n" + errors.stream()
                    .map(Throwable::getMessage)
                    .collect(Collectors.joining("\n"));
        }
    }
}
