namespace Gherkin.Ast;

public class Step(Location location, string keyword, StepKeywordType keywordType, string text, StepArgument argument) : IHasLocation
{
    public Location Location { get; } = location;
    public string Keyword { get; } = keyword;
    public StepKeywordType KeywordType { get; } = keywordType;

    public string Text { get; } = text;
    public StepArgument Argument { get; } = argument;
}