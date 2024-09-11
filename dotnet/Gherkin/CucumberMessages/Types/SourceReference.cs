using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class SourceReference
{
    [DataMember(Name = "location")]
    public required Location Location { get; set; }

    [DataMember(Name = "uri")]
    public required string Uri { get; set; }

    //TODO: javaMethod, javaStackTraceElement
}