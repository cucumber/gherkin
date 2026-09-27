package io.cucumber.gherkin;

interface ThrowingBiConsumer<T, U> {

    void accept(T t, U u) throws ParserException;

}
