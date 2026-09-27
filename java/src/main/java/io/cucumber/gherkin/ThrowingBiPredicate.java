package io.cucumber.gherkin;

interface ThrowingBiPredicate<T, U> {

    boolean test(T t, U u) throws CompositeParserException;

}
