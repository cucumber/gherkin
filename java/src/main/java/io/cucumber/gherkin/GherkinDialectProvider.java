package io.cucumber.gherkin;

import java.util.Optional;
import java.util.Set;

import static java.util.Objects.requireNonNull;

public final class GherkinDialectProvider {

    private final String defaultDialectName;
    private GherkinDialect defaultDialect;

    public GherkinDialectProvider(String defaultDialectName) {
        this.defaultDialectName = requireNonNull(defaultDialectName);
    }

    public GherkinDialectProvider() {
        this("en");
    }

    public GherkinDialect getDefaultDialect() {
        if (defaultDialect == null) {
            Optional<GherkinDialect> optionalGherkinDialect = getDialect(defaultDialectName);
            if (optionalGherkinDialect.isPresent()) {
                defaultDialect = optionalGherkinDialect.get();
            } else {
                throw new ParserException.NoSuchLanguageException(defaultDialectName, null);
            }
        }
        return defaultDialect;
    }

    public Optional<GherkinDialect> getDialect(String language) {
        requireNonNull(language);
        return Optional.ofNullable(GherkinDialects.DIALECTS.get(language));
    }

    public Set<String> getLanguages() {
        return GherkinDialects.DIALECTS.keySet();
    }
}
