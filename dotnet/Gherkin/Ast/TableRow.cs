namespace Gherkin.Ast;

public class TableRow(Location location, TableCell[] cells) : IHasLocation
{
    public Location Location { get; } = location;
    public IEnumerable<TableCell> Cells { get; } = cells;
}