using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class DataTable
{
    [DataMember(Name = "location")]
    public required Location Location { get; set; }

    [DataMember(Name = "rows")]
    public required IReadOnlyCollection<TableRow> Rows { get; set; }
}