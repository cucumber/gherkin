namespace Gherkin.Ast;

public class DocString(Location location, string contentType, string content, string delimiter = null) : StepArgument, IHasLocation
{
    public Location Location { get; } = location;
    public string ContentType { get; } = contentType;
    public string Content { get; } = content;
    public string Delimiter { get; } = delimiter;
}