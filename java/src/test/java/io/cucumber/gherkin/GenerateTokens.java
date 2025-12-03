package io.cucumber.gherkin;

import org.jspecify.annotations.NullMarked;

import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.file.Paths;

import static java.nio.charset.StandardCharsets.UTF_8;
import static java.nio.file.Files.readString;

public final class GenerateTokens {

    private GenerateTokens() {
        // main class
    }

    public static void main(String[] args) throws IOException {
        TokenFormatterBuilder builder = new TokenFormatterBuilder();
        Parser<String> parser = new Parser<>(builder);
        GherkinTokenMatcher matcher = new GherkinTokenMatcher();
        OutputStream out = new NonClosableOutputStream(System.out);
        try (PrintWriter writer = new PrintWriter(new OutputStreamWriter(out, UTF_8))) {
            for (String fileName : args) {
                String bytes = readString(Paths.get(fileName), UTF_8);
                String result = parser.parse(bytes, matcher, fileName);
                writer.print(result);
            }
        }
    }

    @NullMarked
    private static class NonClosableOutputStream extends OutputStream {

        private final OutputStream delegate;

        NonClosableOutputStream(OutputStream delegate) {
            this.delegate = delegate;
        }

        @Override
        public void write(int b) throws IOException {
            delegate.write(b);
        }

        @Override
        public void write(byte[] b, int off, int len) throws IOException {
            delegate.write(b, off, len);
        }
    }
}
