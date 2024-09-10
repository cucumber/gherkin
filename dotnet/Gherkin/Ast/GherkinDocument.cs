namespace Gherkin.Ast;

public class GherkinDocument(Feature feature, Comment[] comments)
{
    public Feature Feature { get; } = feature;
    public IEnumerable<Comment> Comments { get; } = comments;
}
