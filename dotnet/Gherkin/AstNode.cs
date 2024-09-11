namespace Gherkin;

public class AstNode(RuleType ruleType)
{
    private readonly Dictionary<RuleType, IList<object>> subItems = new Dictionary<RuleType, IList<object>>();

    public RuleType RuleType { get; } = ruleType;

    public Token? GetToken(TokenType tokenType)
    {
        return GetSingle<Token>((RuleType)tokenType);
    }

    public IEnumerable<Token> GetTokens(TokenType tokenType)
    {
        return GetItems<Token>((RuleType)tokenType);
    }

    public T? GetSingle<T>(RuleType ruleType) where T : notnull
    {
        return GetItems<T>(ruleType).SingleOrDefault();
    }

    public IEnumerable<T> GetItems<T>(RuleType ruleType)
    {
        if (!subItems.TryGetValue(ruleType, out var items))
        {
            return Enumerable.Empty<T>();
        }
        return items.Cast<T>();
    }

    public void SetSingle<T>(RuleType ruleType, T value) where T : notnull
    {
        subItems[ruleType] = [value];
    }

    public void AddRange<T>(RuleType ruleType, IEnumerable<T> values) where T : notnull
    {
        foreach (var value in values)
        {
            Add(ruleType, value);
        }
    }

    public void Add<T>(RuleType ruleType, T obj) where T : notnull
    {
        if (!subItems.TryGetValue(ruleType, out var items))
        {
            items = new List<object>();
            subItems.Add(ruleType, items);
        }
        items.Add(obj);
    }
}
