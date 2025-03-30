package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;
import io.cucumber.messages.types.StepKeywordType;

import java.util.List;

import static java.util.Objects.requireNonNull;

class Token {
    public final GherkinLine line;
    public Parser.TokenType matchedType;
    public String matchedKeyword;
    public String matchedText;
    public List<GherkinLineSpan> matchedItems;
    public int matchedIndent;
    public GherkinDialect matchedGherkinDialect;
    public StepKeywordType keywordType;
    public Location location;

    private Token(GherkinLine line, Location location) {
        this.line = line;
        this.location = location;
    }

    static Token createEOF(Location location) {
        requireNonNull(location);
        return new Token(null, location);
    }

    static Token createGherkinLine(String line, Location location) {
        requireNonNull(line);
        requireNonNull(location);
        return new Token(new GherkinLine(line, location), location);
    }

    public boolean isEOF() {
        return line == null;
    }

    public String getTokenValue() {
        return isEOF() ? "EOF" : line.getLineText(-1);
    }

    @Override
    public String toString() {
        return String.format("%s: %s/%s", matchedType, matchedKeyword, matchedText);
    }
}
