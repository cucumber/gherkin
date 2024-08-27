namespace Gherkin.Ast;

public class Comment(Location location, string text) : IHasLocation
{
    public Location Location { get; } = location;
    public string Text { get; } = text;
}