namespace Gherkin.Ast;

public class Tag(Location location, string name) : IHasLocation
{
    public Location Location { get; } = location;
    public string Name { get; } = name;
}