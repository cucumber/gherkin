namespace Gherkin.Ast;

public class TableCell(Location location, string value) : IHasLocation
{
    public Location Location { get; } = location;
    public string Value { get; } = value;
}