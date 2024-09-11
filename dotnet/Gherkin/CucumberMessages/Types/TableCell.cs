using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class TableCell
{
    [DataMember(Name = "location")]
    public required Location Location { get; set; }

    [DataMember(Name = "value")]
    public required string Value { get; set; }
}