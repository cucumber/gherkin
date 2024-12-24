namespace Gherkin.SourceGenerator;

class GherkinLanguageSetting
{
    public string? Name { get; set; }
    public string? Native { get; set; }
    public string?[]? Feature { get; set; }
    public string?[]? Rule { get; set; }
    public string?[]? Background { get; set; }
    public string?[]? Scenario { get; set; }
    public string?[]? ScenarioOutline { get; set; }
    public string?[]? Examples { get; set; }
    public string?[]? Given { get; set; }
    public string?[]? When { get; set; }
    public string?[]? Then { get; set; }
    public string?[]? And { get; set; }
    public string?[]? But { get; set; }
}
