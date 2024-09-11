using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class Tag
{
    [DataMember(Name = "location")]
    public required Location Location { get; set; }

    [DataMember(Name = "name")]
    public required string Name { get; set; }

    [DataMember(Name = "id")]
    public required string Id { get; set; }
}