using System.Diagnostics.CodeAnalysis;
using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class PickleTableRow
{
    [DataMember(Name = "cells")]
    public required IEnumerable<PickleTableCell> Cells { get; set; }

    public PickleTableRow()
    {
    }

    [SetsRequiredMembers]
    public PickleTableRow(IEnumerable<PickleTableCell> cells)
    {
        Cells = cells;
    }
}
