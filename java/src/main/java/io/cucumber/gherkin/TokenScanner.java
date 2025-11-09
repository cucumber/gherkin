package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;
import org.jspecify.annotations.Nullable;

import java.util.Iterator;

import static io.cucumber.gherkin.Token.createEOF;
import static io.cucumber.gherkin.Token.createGherkinLine;

/**
 * The scanner reads a gherkin doc (typically read from a .feature file) and
 * creates a token for each line. The tokens are passed to the parser, which
 * outputs an AST (Abstract Syntax Tree).</p>
 */
final class TokenScanner {

    private final Iterator<String> reader;
    private int lineNumber;

    TokenScanner(String source) {
        this.reader = source.lines().iterator();
    }

    Token read() {
        if (reader.hasNext()) {
            String rawText = reader.next();
            Location location = Locations.atLine(++lineNumber);
            return createGherkinLine(rawText, location);
        }
        // Don't optimistically increment the line number
        Location location = Locations.atLine(++lineNumber);
        return createEOF(location);
    }
}
