using Gherkin.Ast;
using System.Diagnostics.CodeAnalysis;
using System.Text.Json;

namespace Gherkin;

public interface IGherkinDialectProvider
{
    GherkinDialect DefaultDialect { get; }
    GherkinDialect GetDialect(string language, Location location);
}

public class GherkinDialectProvider : IGherkinDialectProvider
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

    protected virtual bool TryGetDialect(string language, Location? location, [NotNullWhen(true)] out GherkinDialect? dialect)
    {
        var gherkinLanguageSettings = LoadLanguageSettings();
        return TryGetDialect(language, gherkinLanguageSettings, location, out dialect);
    }

    public virtual GherkinDialect GetDialect(string language, Location? location)
    {
        if (!TryGetDialect(language, location, out var dialect))
            throw new NoSuchLanguageException(language, location);
        return dialect;
    }

    protected virtual Dictionary<string, GherkinLanguageSetting> LoadLanguageSettings()
    {
        const string languageFileName = "gherkin-languages.json";

        var assembly = typeof(GherkinDialectProvider).Assembly;
        var resourceStream = assembly.GetManifestResourceStream("Gherkin." + languageFileName);

        if (resourceStream == null)
            throw new InvalidOperationException("Gherkin language resource not found: " + languageFileName);
        var languagesFileContent = new StreamReader(resourceStream).ReadToEnd();

        return ParseJsonContent(languagesFileContent);
    }

    protected virtual Dictionary<string, GherkinLanguageSetting> ParseJsonContent(string languagesFileContent)
    {
        var gherkinLanguageSettings = JsonSerializer.Deserialize<Dictionary<string, GherkinLanguageSetting>>(
            languagesFileContent,
            new JsonSerializerOptions(JsonSerializerDefaults.Web));

        return gherkinLanguageSettings ?? throw new Exception($"Unable to parse languages from {languagesFileContent}");
    }

    protected virtual bool TryGetDialect(
        string language,
        Dictionary<string, GherkinLanguageSetting> gherkinLanguageSettings,
        Location? location,
        [NotNullWhen(true)] out GherkinDialect? dialect)
    {
        if (!gherkinLanguageSettings.TryGetValue(language, out var languageSettings))
        {
            dialect = null;
            return false;
        }

        dialect = CreateGherkinDialect(language, languageSettings);
        return true;
    }

    protected GherkinDialect CreateGherkinDialect(string language, GherkinLanguageSetting languageSettings)
    {
        return new GherkinDialect(
            language,
            ParseTitleKeywords(languageSettings.Feature),
            ParseTitleKeywords(languageSettings.Rule),
            ParseTitleKeywords(languageSettings.Background),
            ParseTitleKeywords(languageSettings.Scenario),
            ParseTitleKeywords(languageSettings.ScenarioOutline),
            ParseTitleKeywords(languageSettings.Examples),
            ParseStepKeywords(languageSettings.Given),
            ParseStepKeywords(languageSettings.When),
            ParseStepKeywords(languageSettings.Then),
            ParseStepKeywords(languageSettings.And),
            ParseStepKeywords(languageSettings.But)
        );
    }

    private string[] ParseStepKeywords(string[] stepKeywords)
    {
        return stepKeywords;
    }

    private string[] ParseTitleKeywords(string[] keywords)
    {
        return keywords;
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

public class GherkinLanguageSetting
{
    public required string Name { get; set; }
    public required string Native { get; set; }
    public required string[] Feature { get; set; }
    public required string[] Rule { get; set; }
    public required string[] Background { get; set; }
    public required string[] Scenario { get; set; }
    public required string[] ScenarioOutline { get; set; }
    public required string[] Examples { get; set; }
    public required string[] Given { get; set; }
    public required string[] When { get; set; }
    public required string[] Then { get; set; }
    public required string[] And { get; set; }
    public required string[] But { get; set; }
}
