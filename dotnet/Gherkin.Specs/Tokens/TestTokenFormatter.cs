namespace Gherkin.Specs.Tokens;

class TestTokenFormatter
{
    public string FormatToken(Token token)
    {
        if (token.IsEOF)
            return "EOF";

        string stepTypeText = string.Empty;
        string matchedItemsText = null;
        switch (token.MatchedType)
        {
            case TokenType.FeatureLine:
            case TokenType.ScenarioLine:
            case TokenType.ExamplesLine:
            case TokenType.DocStringSeparator:
            case TokenType.BackgroundLine:
            case TokenType.RuleLine:
                stepTypeText = "()";
                break;
            case TokenType.StepLine:
                var tokenType = token.MatchedGherkinDialect.GetStepKeywordType(token.MatchedKeyword);
                stepTypeText = $"({tokenType})";
                break;
            case TokenType.TagLine:
                matchedItemsText = string.Join(",", token.Line.GetTags().Select(i => i.Column + ":" + i.Text));
                break;
            case TokenType.TableRow:
                matchedItemsText = string.Join(",", token.Line.GetTableCells().Select(i => i.Column + ":" + i.Text));
                break;
        }

        return $"({token.Location.Line}:{token.Location.Column}){token.MatchedType}:{stepTypeText}{token.MatchedKeyword}/{token.MatchedText}/{matchedItemsText}";
    }
}
