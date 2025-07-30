package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.StringReader;

import static io.cucumber.gherkin.Token.createEOF;
import static io.cucumber.gherkin.Token.createGherkinLine;

/**
 * The scanner reads a gherkin doc (typically read from a .feature file) and
 * creates a token for each line. The tokens are passed to the parser, which
 * outputs an AST (Abstract Syntax Tree).</p>
 */
final class TokenScanner {

    private final BufferedReader reader;
    private int lineNumber;

    TokenScanner(String source) {
        // TODO performance: replace BufferedReader by Java 11 String.lines(source).iterator() : 25-50% faster
        this.reader = new BufferedReader(new StringReader(source));
    }

    Token read() {
        try {
            String rawText = reader.readLine();
            if (rawText == null) {
                // Don't optimistically increment the line number
                Location location = Locations.atLine(++lineNumber);
                return createEOF(location);
            }
            Location location = Locations.atLine(++lineNumber);
            return createGherkinLine(rawText, location);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
