namespace Gherkin.Ast;

public readonly struct Location(int line = 0, int column = 0)
{
    public int Line { get; } = line;
    public int Column { get; } = column;
}