using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class Feature
{
    [DataMember(Name = "location")]
    public required Location Location { get; set; }

    [DataMember(Name = "tags")]
    public required IReadOnlyCollection<Tag> Tags { get; set; }

    [DataMember(Name = "language")]
    public required string Language { get; set; }

    [DataMember(Name = "keyword")]
    public required string Keyword { get; set; }

    [DataMember(Name = "name")]
    public required string Name { get; set; }

    [DataMember(Name = "description")]
    public required string Description { get; set; }

    [DataMember(Name = "children")]
    public required IReadOnlyCollection<FeatureChild> Children { get; set; }
}