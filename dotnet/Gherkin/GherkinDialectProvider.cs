using Gherkin.Ast;
using System.Text.Json;
using System.Text.Json.Serialization;

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

    protected virtual bool TryGetDialect(string language, Location location, out GherkinDialect dialect)
    {
        var gherkinLanguageSettings = LoadLanguageSettings();
        return TryGetDialect(language, gherkinLanguageSettings, location, out dialect);
    }

    public virtual GherkinDialect GetDialect(string language, Location location)
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
        return JsonSerializer.Deserialize<Dictionary<string, GherkinLanguageSetting>>(languagesFileContent, new JsonSerializerOptions(JsonSerializerDefaults.Web) { TypeInfoResolver = SourceGenerationContext.Default });
    }

    protected virtual bool TryGetDialect(string language, Dictionary<string, GherkinLanguageSetting> gherkinLanguageSettings, Location location, out GherkinDialect dialect)
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

[JsonSourceGenerationOptions]
[JsonSerializable(typeof(Dictionary<string, GherkinLanguageSetting>))]
internal partial class SourceGenerationContext : JsonSerializerContext
{
}

public class GherkinLanguageSetting
{
    public string Name { get; set; }
    public string Native { get; set; }
    public string[] Feature { get; set; }
    public string[] Rule { get; set; }
    public string[] Background { get; set; }
    public string[] Scenario { get; set; }
    public string[] ScenarioOutline { get; set; }
    public string[] Examples { get; set; }
    public string[] Given { get; set; }
    public string[] When { get; set; }
    public string[] Then { get; set; }
    public string[] And { get; set; }
    public string[] But { get; set; }
}
