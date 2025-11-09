package io.cucumber.gherkin;

import io.cucumber.messages.types.Envelope;
import io.cucumber.messages.MessageToNdjsonWriter;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

import static io.cucumber.gherkin.Jackson.OBJECT_MAPPER;
import static java.util.Arrays.asList;

public class Main {

    public static void main(String[] argv) throws IOException {
        List<String> args = new ArrayList<>(asList(argv));
        List<String> paths = new ArrayList<>();

        GherkinParser.Builder builder = GherkinParser.builder();

        while (!args.isEmpty()) {
            String arg = args.remove(0).trim();

            switch (arg) {
                case "--no-source" -> builder.includeSource(false);
                case "--no-ast" -> builder.includeGherkinDocument(false);
                case "--no-pickles" -> builder.includePickles(false);
                case "--predictable-ids" -> builder.idGenerator(new IncrementingIdGenerator());
                default -> paths.add(arg);
            }
        }

        GherkinParser parser = builder.build();

        try (MessageToNdjsonWriter writer = new MessageToNdjsonWriter(nonClosableSystemOut(), OBJECT_MAPPER::writeValue)) {
            for (String path : paths) {
                try (InputStream fis  = Files.newInputStream(Paths.get(path))) {
                    // Don't use parser.parse(Path). The test suite uses relative paths.
                    parser.parse(path, fis)
                            .forEach(envelope -> printMessage(writer, envelope));
                }
            }
        }
    }

    private static OutputStream nonClosableSystemOut() {
        return new OutputStream() {
            @Override
            public void write(int b) {
                System.out.write(b);
            }
        };
    }

    private static void printMessage(MessageToNdjsonWriter writer, Envelope envelope) {
        try {
            writer.write(envelope);
        } catch (IOException e) {
            throw new RuntimeException("Couldn't print messages", e);
        }
    }

}
