namespace Gherkin.Ast;

public class Location(int line = 0, int column = 0)
{
    public int Line { get; } = line;
    public int Column { get; } = column;
}