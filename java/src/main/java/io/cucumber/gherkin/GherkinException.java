package io.cucumber.gherkin;

final class GherkinException extends RuntimeException {
    GherkinException(String message, Throwable cause) {
        super(message, cause);
    }
}
