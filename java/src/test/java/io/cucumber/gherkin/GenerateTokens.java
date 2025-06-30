package io.cucumber.gherkin;

import java.io.IOException;
import java.nio.file.Paths;

import static java.nio.charset.StandardCharsets.UTF_8;
import static java.nio.file.Files.readAllBytes;

public final class GenerateTokens {
    public static void main(String[] args) throws IOException {
        TokenFormatterBuilder builder = new TokenFormatterBuilder();
        Parser<String> parser = new Parser<>(builder);
        GherkinTokenMatcher matcher = new GherkinTokenMatcher();
        for (String fileName : args) {
            byte[] bytes = readAllBytes(Paths.get(fileName));
            String result = parser.parse(new String(bytes, UTF_8), matcher, fileName);
            Stdio.out.print(result);
            Stdio.out.flush(); // print doesn't autoflush
        }
    }
}
