namespace Gherkin.Ast;

public readonly struct TableCell(Location location, string value) : IHasLocation
{
    public Location Location { get; } = location;
    public string Value { get; } = value;
}