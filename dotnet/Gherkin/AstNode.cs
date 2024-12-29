using System.Collections;
using System.Diagnostics;

namespace Gherkin;

[DebuggerDisplay($"{{{nameof(GetDebuggerDisplay)}(),nq}}")]
public class AstNode(RuleType ruleType)
{
    private readonly List<(RuleType RuleType, object Item)> subItems = new(4);

    public RuleType RuleType { get; } = ruleType;

    public Token GetToken(TokenType tokenType)
    {
        return GetSingle<Token>((RuleType)tokenType);
    }

    public Enumerable<Token> GetTokens(TokenType tokenType)
    {
        return GetItems<Token>((RuleType)tokenType);
    }

    public T GetSingle<T>(RuleType ruleType)
    {
        bool foundOne = false;
        T ret = default;
        foreach ((var itemType, var item) in subItems)
        {
            if (itemType != ruleType)
                continue;
            if (item is not T tItem)
                continue;
            if (foundOne)
                throw new InvalidOperationException();
            ret = tItem;
            foundOne = true;
        }
        return ret;
    }

    public readonly struct Enumerable<T> : IEnumerable<T>
    {
        readonly List<(RuleType RuleType, object Item)> subItems;
        readonly RuleType ruleType;

        internal Enumerable(List<(RuleType RuleType, object Item)> subItems, RuleType ruleType)
        {
            this.subItems = subItems;
            this.ruleType = ruleType;
        }

        public Enumerator<T> GetEnumerator() => new Enumerator<T>(subItems.GetEnumerator(), ruleType);

        IEnumerator<T> IEnumerable<T>.GetEnumerator() => GetEnumerator();
        IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
    }

    public struct Enumerator<T> : IEnumerator<T>
    {
        private List<(RuleType RuleType, object Item)>.Enumerator enumerator;
        readonly RuleType ruleType;

        internal Enumerator(List<(RuleType RuleType, object Item)>.Enumerator enumerator, RuleType ruleType)
        {
            this.enumerator = enumerator;
            this.ruleType = ruleType;
        }

        public T Current { readonly get; private set; }
        readonly object IEnumerator.Current => Current;

        public readonly void Dispose()
        {
            // nothing to do
        }

        public bool MoveNext()
        {
            while (enumerator.MoveNext())
            {
                (var itemType, var item) = enumerator.Current;
                if (itemType != ruleType)
                    continue;
                if (item is not T tItem)
                    continue;
                Current = tItem;
                return true;
            }
            Current = default;
            return false;
        }

        public void Reset() => throw new NotImplementedException();
    }

    public Enumerable<T> GetItems<T>(RuleType ruleType) => new Enumerable<T>(subItems, ruleType);

    public void Add<T>(RuleType ruleType, T obj)
    {
        subItems.Add((ruleType, obj));
    }

    string GetDebuggerDisplay() => $"RuleType: {RuleType} with item count: {(subItems.Count == 0 ? "<none>" : string.Join(", ", subItems.GroupBy(x => x.RuleType).Select(x => $"{x.Key}:{x.Count()}")))}";
}
