package io.cucumber.gherkin;

import java.util.List;

import io.cucumber.messages.types.Location;
import org.jspecify.annotations.Nullable;

import static io.cucumber.gherkin.Locations.COLUMN_OFFSET;
import static io.cucumber.gherkin.Locations.atColumn;
import static java.util.Objects.requireNonNull;

class ParserError {
    private final String message;
    private final @Nullable Location location;

    ParserError(String message, @Nullable Location location) {
        this.message = createMessage(message, location);
        this.location = location;
    }

    String getMessage() {
        return message;
    }

    @Nullable Location getLocation() {
        return location;
    }

    private static String createMessage(String message, @Nullable Location location) {
        if (location == null) {
            return "(-1,0): %s".formatted(message);
        }
        Integer line = location.getLine();
        Integer column = location.getColumn().orElse(0);
        return "(%s:%s): %s".formatted(line, column, message);
    }

    static final class TagMayNotContainWhitespace extends ParserError {
        TagMayNotContainWhitespace(@Nullable Location location) {
            super("A tag may not contain whitespace", location);
        }
    }

    static final class InConsistentCellCount extends ParserError {
        InConsistentCellCount(@Nullable Location location) {
            super("inconsistent cell count within the table", location);
        }
    }

    static final class NoSuchLanguage extends ParserError {
        NoSuchLanguage(String language, @Nullable Location location) {
            super("Language not supported: " + language, location);
        }
    }

    static final class UnexpectedToken extends ParserError {

        final Token receivedToken;
        final List<String> expectedTokenTypes;
        final String stateComment;

        UnexpectedToken(Token receivedToken, List<String> expectedTokenTypes, String stateComment) {
            super(getMessage(receivedToken, expectedTokenTypes), getLocation(receivedToken));
            this.receivedToken = receivedToken;
            this.expectedTokenTypes = expectedTokenTypes;
            this.stateComment = stateComment;
        }

        private static String getMessage(Token receivedToken, List<String> expectedTokenTypes) {
            return "expected: %s, got '%s'".formatted(
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

    static final class UnexpectedEOF extends ParserError {
        final String stateComment;
        final List<String> expectedTokenTypes;

        UnexpectedEOF(Token receivedToken, List<String> expectedTokenTypes, String stateComment) {
            super(getMessage(expectedTokenTypes), receivedToken.location);
            this.expectedTokenTypes = expectedTokenTypes;
            this.stateComment = stateComment;
        }

        private static String getMessage(List<String> expectedTokenTypes) {
            return "unexpected end of file, expected: %s".formatted(
                    String.join(", ", expectedTokenTypes));
        }
    }

}
