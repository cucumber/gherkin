namespace Gherkin.Ast;

public class DataTable : StepArgument, IHasRows, IHasLocation
{
    public Location Location { get; private set; }
    public IEnumerable<TableRow> Rows { get; private set; }

    public DataTable(List<TableRow> rows)
    {
        if (rows == null) throw new ArgumentNullException("rows");
        if (rows.Count == 0) throw new ArgumentException("DataTable must have at least one row", "rows");

        Location = rows[0].Location;
        Rows = rows;
    }
}