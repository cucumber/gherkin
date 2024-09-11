using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class DocString
{
    [DataMember(Name = "location")]
    public required Location Location { get; set; }

    [DataMember(Name = "mediaType")]
    public string? MediaType { get; set; }

    [DataMember(Name = "content")]
    public required string Content { get; set; }

    [DataMember(Name = "delimiter")]
    public required string Delimiter { get; set; }
}