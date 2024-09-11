using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class GherkinDocument
{
    [DataMember(Name = "uri")]
    public required string Uri { get; set; }

    [DataMember(Name = "feature")]
    public Feature? Feature { get; set; }

    [DataMember(Name = "comments")]
    public required IReadOnlyCollection<Comment> Comments { get; set; }
}