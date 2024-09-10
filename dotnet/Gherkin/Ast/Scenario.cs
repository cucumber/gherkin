namespace Gherkin.Ast;

public class Scenario(Tag[] tags, Location location, string keyword, string name, string description, Step[] steps, Examples[] examples)
    : StepsContainer(location, keyword, name, description, steps), IHasTags
{
    public IEnumerable<Tag> Tags { get; } = tags;
    public IEnumerable<Examples> Examples { get; } = examples;
}