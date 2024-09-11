using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class Comment
{
    [DataMember(Name = "location")]
    public required Location Location { get; set; }

    [DataMember(Name = "text")]
    public required string Text { get; set; }
}