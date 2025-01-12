namespace Gherkin;

public class AstNode(RuleType ruleType)
{
    private readonly Dictionary<RuleType, object> subItems = new Dictionary<RuleType, object>();

    public RuleType RuleType { get; } = ruleType;

    public Token GetToken(TokenType tokenType)
    {
        return GetSingle<Token>((RuleType)tokenType);
    }

    public IEnumerable<Token> GetTokens(TokenType tokenType)
    {
        return GetItems<Token>((RuleType)tokenType);
    }

    public T GetSingle<T>(RuleType ruleType)
    {
        if (!subItems.TryGetValue(ruleType, out var items))
            return default;
        if (items is List<object> list)
        {
            T ret = default;
            bool foundOne = false;
            foreach (var item in list)
            {
                if (item is T tItem)
                {
                    if (foundOne)
                        throw new InvalidOperationException();
                    ret = tItem;
                    foundOne = true;
                }
            }
            if (foundOne)
                return ret;
            else
                throw new InvalidOperationException();
        }
        else if (items is T tItem)
        {
            return tItem;
        }
        return default;
    }

    public IEnumerable<T> GetItems<T>(RuleType ruleType)
    {
        if (!subItems.TryGetValue(ruleType, out var items))
            yield break;
        if (items is List<object> list)
        {
            foreach (var item in list)
            {
                if (item is T tItem)
                    yield return tItem;
            }
        }
        else if (items is T tItem)
        {
            yield return tItem;
        }
    }

    public void SetSingle<T>(RuleType ruleType, T value)
    {
        subItems[ruleType] = new object[] { value };
    }

    public void AddRange<T>(RuleType ruleType, IEnumerable<T> values)
    {
        foreach (var value in values)
        {
            Add(ruleType, value);
        }
    }

    public void Add<T>(RuleType ruleType, T obj)
    {
        if (!subItems.TryGetValue(ruleType, out var items))
        {
            subItems.Add(ruleType, obj);
        }
        else if (items is List<object> list)
        {
            list.Add(obj);
        }
        else
        {
            list = [items, obj];
            subItems[ruleType] = list;
        }
    }
}
