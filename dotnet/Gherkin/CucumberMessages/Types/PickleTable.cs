using System.Diagnostics.CodeAnalysis;
using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class PickleTable
{
    [DataMember(Name = "rows")]
    public required IEnumerable<PickleTableRow> Rows { get; set; }

    public PickleTable()
    {
    }

    [SetsRequiredMembers]
    public PickleTable(IEnumerable<PickleTableRow> rows)
    {
        Rows = rows;
    }
}
