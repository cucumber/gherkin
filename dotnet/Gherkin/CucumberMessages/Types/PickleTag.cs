using System.Diagnostics.CodeAnalysis;
using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class PickleTag
{
    [DataMember(Name = "name")]
    public required string Name { get; set; }

    [DataMember(Name = "astNodeId")]
    public required string AstNodeId { get; set; }

    public PickleTag()
    {
    }

    [SetsRequiredMembers]
    public PickleTag(string name, string astNodeId)
    {
        AstNodeId = astNodeId;
        Name = name;
    }
}
