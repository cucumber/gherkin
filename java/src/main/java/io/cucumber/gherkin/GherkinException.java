package io.cucumber.gherkin;

public class GherkinException extends RuntimeException {
    public GherkinException(String message, Throwable cause) {
        super(message, cause);
    }
}
