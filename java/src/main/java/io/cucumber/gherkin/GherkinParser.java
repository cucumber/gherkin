package io.cucumber.gherkin;

import io.cucumber.gherkin.ParserException.CompositeParserException;
import io.cucumber.messages.IdGenerator;
import io.cucumber.messages.types.Envelope;
import io.cucumber.messages.types.GherkinDocument;
import io.cucumber.messages.types.ParseError;
import io.cucumber.messages.types.Pickle;
import io.cucumber.messages.types.Source;
import io.cucumber.messages.types.SourceReference;

import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;
import java.util.stream.Stream;

import static io.cucumber.gherkin.EncodingParser.readWithEncodingFromSource;
import static io.cucumber.messages.types.SourceMediaType.TEXT_X_CUCUMBER_GHERKIN_PLAIN;
import static java.util.Objects.requireNonNull;
import static java.util.stream.Collectors.toList;

/**
 * Main entry point for the Gherkin library
 */
public final class GherkinParser {

    /**
     * Estimate of the average line length in a feature file.
     */
    static final int FEATURE_FILE_AVERAGE_LINE_LENGTH = 100;

    /**
     * Estimate of the average number of lines in a feature file.
     */
    static final int FEATURE_FILE_AVERAGE_LINE_COUNT = 2048;

    /**
     * Estimate of the average feature file size.
     */
    static final int FEATURE_FILE_AVERAGE_SIZE = FEATURE_FILE_AVERAGE_LINE_LENGTH * FEATURE_FILE_AVERAGE_LINE_COUNT;

    private final boolean includeSource;
    private final boolean includeGherkinDocument;
    private final boolean includePickles;
    private final IdGenerator idGenerator;
    private final PickleCompiler pickleCompiler;

    private GherkinParser(boolean includeSource, boolean includeGherkinDocument, boolean includePickles,
                          IdGenerator idGenerator) {
        this.includeSource = includeSource;
        this.includeGherkinDocument = includeGherkinDocument;
        this.includePickles = includePickles;
        this.idGenerator = requireNonNull(idGenerator);
        this.pickleCompiler = new PickleCompiler(idGenerator);
    }

    public static Builder builder() {
        return new Builder();
    }

    public Stream<Envelope> parse(Path source) throws IOException {
        requireNonNull(source);
        // .feature.md files are not supported
        return parse(source.toUri().toString(), Files.readAllBytes(source));
    }

    public Stream<Envelope> parse(String uri, InputStream source) throws IOException {
        requireNonNull(uri);
        requireNonNull(source);
        return parse(uri, source.readAllBytes());
    }

    public Stream<Envelope> parse(String uri, byte[] source) {
        requireNonNull(uri);
        requireNonNull(source);
        String withEncodingFromSource = readWithEncodingFromSource(source);
        return parse(Envelope.of(new Source(uri, withEncodingFromSource, TEXT_X_CUCUMBER_GHERKIN_PLAIN)));
    }

    public Stream<Envelope> parse(Envelope envelope) {
        requireNonNull(envelope);

        List<Envelope> messages = new ArrayList<>();

        if (includeSource) {
            messages.add(envelope);
        }


        // Lambda is faster than method reference because if avoids a call to
        // Objects.requiresNonNull(messages)
        //noinspection Convert2MethodRef
        envelope.getSource()
                .map(this::parse)
                .ifPresent(envelopes -> messages.addAll(envelopes));

        return messages.stream();
    }

    private List<Envelope> parse(Source source) {
        return parse(source.getUri(), source.getData());
    }

    @SuppressWarnings("ForLoopReplaceableByForEach")
    private List<Envelope> parse(String uri, String data) {
        List<Envelope> messages = new ArrayList<>();
        GherkinDocumentBuilder documentBuilder = new GherkinDocumentBuilder(idGenerator, uri);
        Parser<GherkinDocument> parser = new Parser<>(documentBuilder);

        try {
            GherkinDocument gherkinDocument = parser.parse(data, uri);
            if (includeGherkinDocument) {
                messages.add(Envelope.of(gherkinDocument));
            }
            if (includePickles) {
                List<Pickle> compile = pickleCompiler.compile(gherkinDocument, uri);
                // classic 'for' loop is ~2x faster than 'for-each'
                for (int i = 0, compileSize = compile.size(); i < compileSize; i++) {
                    Pickle pickle = compile.get(i);
                    messages.add(Envelope.of(pickle));
                }
            }
        } catch (CompositeParserException composite) {
            messages.addAll(composite.errors.stream()
                    .map(error -> createParseError(error, uri))
                    .collect(toList()));
        } catch (ParserException error) {
            messages.add(createParseError(error, uri));
        }
        return messages;
    }

    private Envelope createParseError(ParserException e, String uri) {
        return Envelope.of(new ParseError(
                new SourceReference(
                        uri,
                        null,
                        null,
                        e.location
                ),
                // ParserException always has a message
                requireNonNull(e.getMessage())
        ));
    }

    public static final class Builder {
        private boolean includeSource = true;
        private boolean includeGherkinDocument = true;
        private boolean includePickles = true;
        private IdGenerator idGenerator = () -> UUID.randomUUID().toString();

        private Builder() {

        }

        public Builder includeSource(boolean includeSource) {
            this.includeSource = includeSource;
            return this;
        }

        public Builder includeGherkinDocument(boolean includeGherkinDocument) {
            this.includeGherkinDocument = includeGherkinDocument;
            return this;
        }

        public Builder includePickles(boolean includePickles) {
            this.includePickles = includePickles;
            return this;
        }

        public Builder idGenerator(IdGenerator idGenerator) {
            this.idGenerator = requireNonNull(idGenerator);
            return this;
        }

        public GherkinParser build() {
            return new GherkinParser(includeSource, includeGherkinDocument, includePickles, idGenerator);
        }

    }
}
