package io.cucumber.gherkin;

class GherkinException extends RuntimeException {
    GherkinException(String message, Throwable cause) {
        super(message, cause);
    }
}
