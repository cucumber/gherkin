using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class ParseError
{
    [DataMember(Name = "source")]
    public required SourceReference Source { get; set; }

    [DataMember(Name = "message")]
    public required string Message { get; set; }
}