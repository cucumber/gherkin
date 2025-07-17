namespace Gherkin;

public class GherkinDialect(
    string language,
    string[] featureKeywords,
    string[] ruleKeywords,
    string[] backgroundKeywords,
    string[] scenarioKeywords,
    string[] scenarioOutlineKeywords,
    string[] examplesKeywords,
    string[] givenStepKeywords,
    string[] whenStepKeywords,
    string[] thenStepKeywords,
    string[] andStepKeywords,
    string[] butStepKeywords)
{
    public const string AsteriskKeyword = "* ";
    public string Language { get; } = language;

    public string[] FeatureKeywords { get; } = featureKeywords;
    public string[] RuleKeywords { get; } = ruleKeywords;
    public string[] BackgroundKeywords { get; } = backgroundKeywords;
    public string[] ScenarioKeywords { get; } = scenarioKeywords;
    public string[] ScenarioOutlineKeywords { get; } = scenarioOutlineKeywords;
    public string[] ExamplesKeywords { get; } = examplesKeywords;
    public string[] GivenStepKeywords { get; } = givenStepKeywords;
    public string[] WhenStepKeywords { get; } = whenStepKeywords;
    public string[] ThenStepKeywords { get; } = thenStepKeywords;
    public string[] AndStepKeywords { get; } = andStepKeywords;
    public string[] ButStepKeywords { get; } = butStepKeywords;

    public string[] StepKeywords { get; } = givenStepKeywords
        .Concat(whenStepKeywords)
        .Concat(thenStepKeywords)
        .Concat(andStepKeywords)
        .Concat(butStepKeywords)
        .Distinct()
        .OrderByDescending(x => x.Length) // To avoid conflicts when some keywords are prefixes of others, try the longest keywords first.
        .ToArray();

    public IDictionary<string, StepKeywordType> StepKeywordTypes { get; } = 
                givenStepKeywords.Select(kw => new { Keyword = kw, Type = StepKeywordType.Context })
        .Concat(whenStepKeywords.Select(kw => new { Keyword = kw, Type = StepKeywordType.Action }))
        .Concat(thenStepKeywords.Select(kw => new { Keyword = kw, Type = StepKeywordType.Outcome }))
        .Concat(andStepKeywords.Select(kw => new { Keyword = kw, Type = StepKeywordType.Conjunction }))
        .Concat(butStepKeywords.Select(kw => new { Keyword = kw, Type = StepKeywordType.Conjunction }))
        .GroupBy(item => item.Keyword, item => item.Type)
        .ToDictionary(item => item.Key, items => items.Count() == 1 ? items.First() : StepKeywordType.Unknown);

    public StepKeywordType? GetStepKeywordType(string keyword)
        => StepKeywordTypes.TryGetValue(keyword, out var tokenType) ? tokenType : null;
}
