using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class Scenario
{
    [DataMember(Name = "location")]
    public required Location Location { get; set; }

    [DataMember(Name = "tags")]
    public required IReadOnlyCollection<Tag> Tags { get; set; }

    [DataMember(Name = "keyword")]
    public required string Keyword { get; set; }

    [DataMember(Name = "name")]
    public required string Name { get; set; }

    [DataMember(Name = "description")]
    public required string Description { get; set; }

    [DataMember(Name = "steps")]
    public required IReadOnlyCollection<Step> Steps { get; set; }

    [DataMember(Name = "examples")]
    public required IReadOnlyCollection<Examples> Examples { get; set; }

    [DataMember(Name = "id")]
    public required string Id { get; set; }
}