using Gherkin.Ast;

namespace Gherkin;

public class Token
{
    public Token(GherkinLine line, Location location)
    {
        Line = line;
        Location = location;
    }
    public Token(Location location)
    {
        Location = location;
        IsEOF = true;
    }

    public bool IsEOF { get; }
    public GherkinLine Line { get; set; }
    public TokenType MatchedType { get; set; }
    public string MatchedKeyword { get; set; }
    public string MatchedText { get; set; }
    public int MatchedIndent { get; set; }
    public GherkinDialect MatchedGherkinDialect { get; set; }
    public Location Location { get; set; }

    public void Detach()
    {
    }

    public string GetTokenValue()
    {
        return IsEOF ? "EOF" : Line.GetLineText(-1);
    }

    public override string ToString()
    {
        return string.Format("{0}: {1}/{2}", MatchedType, MatchedKeyword, MatchedText);
    }
}