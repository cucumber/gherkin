using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class TableRow
{
    [DataMember(Name = "location")]
    public required Location Location { get; set; }

    [DataMember(Name = "cells")]
    public required IReadOnlyCollection<TableCell> Cells { get; set; }

    [DataMember(Name = "id")]
    public required string Id { get; set; }
}