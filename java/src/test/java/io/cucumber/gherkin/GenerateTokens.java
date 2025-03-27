package io.cucumber.gherkin;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.nio.charset.StandardCharsets;

public final class GenerateTokens {
    public static void main(String[] args) throws FileNotFoundException {
        TokenFormatterBuilder builder = new TokenFormatterBuilder();
        TokenMatcher classicTokenMatcher = new TokenMatcher();
        GherkinInMarkdownTokenMatcher gherkinInMarkdownTokenMatcher = new GherkinInMarkdownTokenMatcher();
        Parser<String> parser = null;
        
        for (String fileName : args) {

            if(fileName.endsWith(".feature")) {
                parser = new Parser<>(builder, classicTokenMatcher);
            } else {
                parser = new Parser<>(builder, gherkinInMarkdownTokenMatcher);
            }
            Reader in = new InputStreamReader(new FileInputStream(fileName), StandardCharsets.UTF_8);
            String result = parser.parse(in, fileName);
            Stdio.out.print(result);
            Stdio.out.flush(); // print doesn't autoflush
        }
    }
}
