using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class Rule
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

    [DataMember(Name = "children")]
    public required IReadOnlyCollection<RuleChild> Children { get; set; }

    [DataMember(Name = "id")]
    public required string Id { get; set; }
}