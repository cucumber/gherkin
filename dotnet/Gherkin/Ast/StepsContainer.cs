namespace Gherkin.Ast;

public abstract class StepsContainer(Location location, string keyword, string name, string description, Step[] steps)
    : IHasLocation, IHasDescription, IHasSteps
{
    public Location Location { get; } = location;
    public string Keyword { get; } = keyword;
    public string Name { get; } = name;
    public string Description { get; } = description;
    public IEnumerable<Step> Steps { get; } = steps;
}