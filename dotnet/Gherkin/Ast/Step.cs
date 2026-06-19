using Io.Cucumber.Messages.Types;

namespace Gherkin.Ast;

public class Step(Location location, string keyword, StepKeywordType keywordType, string text, DataTable dataTable, DocString docString) : IHasLocation
{
    public Location Location { get; } = location;
    public string Keyword { get; } = keyword;
    public StepKeywordType KeywordType { get; } = keywordType;

    public string Text { get; } = text;
    public DataTable DataTable { get; } = dataTable;
    public DocString DocString { get; } = docString;

    public Step(Location location, string keyword, StepKeywordType keywordType, string text, StepArgument argument)
        : this(location, keyword, keywordType, text, argument as DataTable, argument as DocString)
    {
    }
}
