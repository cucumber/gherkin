using System.Diagnostics.CodeAnalysis;
using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class PickleStep
{
    [DataMember(Name = "argument")]
    public PickleStepArgument? Argument { get; set; }

    [DataMember(Name = "astNodeIds")]
    public required IReadOnlyCollection<string> AstNodeIds { get; set; }

    [DataMember(Name = "id")]
    public required string Id { get; set; }

    [DataMember(Name = "text")]
    public required string Text { get; set; }

    [DataMember(Name = "type")]
    public StepKeywordType Type { get; set; }

    public PickleStep()
    {
    }

    [SetsRequiredMembers]
    public PickleStep(PickleStepArgument? argument, IEnumerable<string> astNodeIds, string id, string text, StepKeywordType type)
    {
        Id = id;
        Text = text;
        Argument = argument;
        AstNodeIds = astNodeIds.ToReadOnlyCollection();
        Type = type;
    }
}
