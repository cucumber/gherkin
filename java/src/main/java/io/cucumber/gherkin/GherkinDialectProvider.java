package io.cucumber.gherkin;

import java.util.Optional;
import java.util.Set;

import static java.util.Objects.requireNonNull;

/**
 * @deprecated use {@link GherkinDialects} instead.
 */
@Deprecated
public final class GherkinDialectProvider {

    private final String defaultDialectName;

    public GherkinDialectProvider(String defaultDialectName) {
        this.defaultDialectName = requireNonNull(defaultDialectName);
    }

    public GherkinDialectProvider() {
        this(Constants.DEFAULT_LANGUAGE);
    }

    public GherkinDialect getDefaultDialect() {
        return GherkinDialects.getDialect(defaultDialectName)// TODO performance: do not instanciate an Optional
                .orElseThrow(() -> new ParserException.NoSuchLanguageException(defaultDialectName, null));
    }

    public Optional<GherkinDialect> getDialect(String language) {
        return GherkinDialects.getDialect(language);// TODO performance: do not instanciate an Optional
    }

    public Set<String> getLanguages() {
        return GherkinDialects.getLanguages();
    }
}
