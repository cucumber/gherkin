package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;
import io.cucumber.messages.types.StepKeywordType;
import org.jspecify.annotations.Nullable;

import java.util.List;

import static java.util.Objects.requireNonNull;

final class Token {
    final @Nullable Line line;
    final boolean eof;
    Parser.@Nullable TokenType matchedType;
    @Nullable String matchedKeyword;
    @Nullable String matchedText;
    @Nullable List<LineSpan> matchedItems;
    int matchedIndent;
    @Nullable String matchedLanguage;
    @Nullable StepKeywordType keywordType;
    Location location;

    private Token(@Nullable Line line, Location location) {
        this.line = line;
        this.location = location;
        this.eof = line == null;
    }

    static Token createEOF(Location location) {
        requireNonNull(location);
        return new Token(null, location);
    }

    static Token createGherkinLine(String text, Location location) {
        requireNonNull(text);
        requireNonNull(location);
        return new Token(new Line(text), location);
    }

    boolean isEOF() {
        return eof;
    }

    String getTokenValue() {
        return line == null ? "EOF" : line.getText();
    }

    @Override
    public String toString() {
        return "%s: %s/%s".formatted(matchedType, matchedKeyword, matchedText);
    }

    String getRequiredMatchedKeyword() {
        return requireNonNull(matchedKeyword);
    }

    String getRequiredMatchedText() {
        return requireNonNull(matchedText);
    }

    String getRequiredMatchedLanguage() {
        return requireNonNull(matchedLanguage);
    }

    Parser.TokenType getRequiredMatchedType() {
        return requireNonNull(matchedType);
    }

    Line getRequiredLine() {
        return requireNonNull(line);
    }
}
