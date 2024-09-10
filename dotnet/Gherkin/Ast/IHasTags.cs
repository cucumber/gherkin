namespace Gherkin.Ast;

public interface IHasTags
{
    IEnumerable<Tag> Tags { get; }
}