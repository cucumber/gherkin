package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;

import static io.cucumber.gherkin.Token.createEOF;
import static io.cucumber.gherkin.Token.createGherkinLine;

/**
 * <p>
 * The scanner reads a gherkin doc (typically read from a .feature file) and creates a token
 * for each line. The tokens are passed to the parser, which outputs an AST (Abstract Syntax Tree).</p>
 * <p>
 * If the scanner sees a # language header, it will reconfigure itself dynamically to look for
 * Gherkin keywords for the associated language. The keywords are defined in gherkin-languages.json.</p>
 */
class TokenScanner implements Parser.ITokenScanner {

    private final BufferedReader reader;
    private int lineNumber;

    TokenScanner(Reader source) {
        this.reader = new BufferedReader(source);
    }

    @Override
    public Token read() {
        try {
            String line = reader.readLine();
            Location location = Locations.atLine(++lineNumber);
            if (line == null) {
                return createEOF(location);
            }
            return createGherkinLine(line, location);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
