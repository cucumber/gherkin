package io.cucumber.gherkin.dialects;

public class Generate {

    public static void main(String[] args) throws Exception {
        if (args.length != 2) {
            throw new IllegalArgumentException("Usage: <baseDirectory> <packagePath>");
        }
        String baseDirectory = args[0];
        String packagePath = args[1];
        GenerateGherkinDialects.generate(baseDirectory, packagePath);
        GenerateKeywordMatchers.generate(baseDirectory, packagePath);
    }
}
