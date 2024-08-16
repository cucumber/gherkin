namespace Gherkin;

public struct GherkinLineSpan(int column, string text)
{
    /// <summary>
    /// One-based line position
    /// </summary>
    public int Column { get; } = column;

    /// <summary>
    /// Text part of the line
    /// </summary>
    public string Text { get; } = text;
}
