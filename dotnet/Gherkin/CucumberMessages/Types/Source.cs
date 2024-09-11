using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class Source
{
    [DataMember(Name = "uri")]
    public required string Uri { get; set; }

    [DataMember(Name = "data")]
    public required string Data { get; set; }

    [DataMember(Name = "mediaType")]
    public required string MediaType { get; set; }
}