namespace Gherkin.Ast;

public class Scenario(IEnumerable<Tag> tags, Location location, string keyword, string name, string description, IEnumerable<Step> steps, IEnumerable<Examples> examples)
    : StepsContainer(location, keyword, name, description, steps), IHasTags
{
    public IEnumerable<Tag> Tags { get; } = tags;
    public IEnumerable<Examples> Examples { get; } = examples;
}