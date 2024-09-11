using System.Diagnostics.CodeAnalysis;
using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class Pickle
{
    [DataMember(Name = "id")]
    public required string Id { get; set; }

    [DataMember(Name = "uri")]
    public required string Uri { get; set; }

    [DataMember(Name = "name")]
    public required string Name { get; set; }

    [DataMember(Name = "language")]
    public required string Language { get; set; }

    [DataMember(Name = "steps")]
    public required IReadOnlyCollection<PickleStep> Steps { get; set; }

    [DataMember(Name = "tags")]
    public required IReadOnlyCollection<PickleTag> Tags { get; set; }

    [DataMember(Name = "astNodeIds")]
    public required IReadOnlyCollection<string> AstNodeIds { get; set; }

    public Pickle()
    {
    }

    [SetsRequiredMembers]
    public Pickle(string id, string uri, string name, string language, IEnumerable<PickleStep> steps, IEnumerable<PickleTag> tags, IEnumerable<string> astNodeIds)
    {
        Id = id;
        Uri = uri;
        Name = name;
        Language = language;
        Steps = steps.ToReadOnlyCollection();
        Tags = tags.ToReadOnlyCollection();
        AstNodeIds = astNodeIds.ToReadOnlyCollection();
    }
}
