using System.Diagnostics.CodeAnalysis;
using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class PickleTableCell
{
    [DataMember(Name = "value")]
    public required string Value { get; set; }

    public PickleTableCell()
    {
    }

    [SetsRequiredMembers]
    public PickleTableCell(string value)
    {
        Value = value;
    }
}
