namespace Gherkin.Ast;

public class Feature(IEnumerable<Tag> tags, Location location, string language, string keyword, string name, string description, IEnumerable<IHasLocation> children)
    : IHasLocation, IHasDescription, IHasTags, IHasChildren
{
    public IEnumerable<Tag> Tags { get; } = tags;
    public Location Location { get; } = location;
    public string Language { get; } = language;
    public string Keyword { get; } = keyword;
    public string Name { get; } = name;
    public string Description { get; } = description;
    public IEnumerable<IHasLocation> Children { get; } = children;
}
