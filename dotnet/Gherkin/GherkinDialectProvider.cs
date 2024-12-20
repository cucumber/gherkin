using Gherkin.Ast;

namespace Gherkin;

public interface IGherkinDialectProvider
{
    GherkinDialect DefaultDialect { get; }
    GherkinDialect GetDialect(string language, Location location);
}

[LanguageDialectGenerated]
public partial class GherkinDialectProvider : IGherkinDialectProvider
{
    private readonly Lazy<GherkinDialect> defaultDialect;

    public GherkinDialect DefaultDialect
    {
        get { return defaultDialect.Value; }
    }

    public GherkinDialectProvider(string defaultLanguage = "en")
    {
        defaultDialect = new Lazy<GherkinDialect>(() => GetDialect(defaultLanguage, null));
    }

    protected virtual bool TryGetDialect(string language, Location location, out GherkinDialect dialect)
    {
        dialect = TryCreateGherkinDialect(language);
        return dialect is not null;
    }

    public virtual GherkinDialect GetDialect(string language, Location location)
    {
        if (!TryGetDialect(language, location, out var dialect))
            throw new NoSuchLanguageException(language, location);
        return dialect;
    }

    protected static GherkinDialect GetFactoryDefault()
    {
        return new GherkinDialect(
            "en",
            ["Feature"],
            ["Rule"],
            ["Background"],
            ["Scenario"],
            ["Scenario Outline", "Scenario Template"],
            ["Examples", "Scenarios"],
            ["* ", "Given "],
            ["* ", "When "],
            ["* ", "Then "],
            ["* ", "And "],
            ["* ", "But "]);
    }
}
