namespace Gherkin.Ast;

public class Rule(Tag[] tags, Location location, string keyword, string name, string description, IHasLocation[] children)
    : IHasLocation, IHasDescription, IHasChildren, IHasTags
{
    public Location Location { get; } = location;
    public string Keyword { get; } = keyword;
    public string Name { get; } = name;
    public string Description { get; } = description;
    public IEnumerable<Tag> Tags { get; } = tags;
    public IEnumerable<IHasLocation> Children { get; } = children;
}
