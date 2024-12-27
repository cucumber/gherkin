using Gherkin.Ast;

namespace Gherkin;

/// <summary>
/// Represents a line of a Gherkin file
/// </summary>
public readonly struct GherkinLine
{
    private static char[] inlineWhitespaceChars = [' ', '\t', '\u00A0'];

    private readonly string lineText;
    private readonly string trimmedLineText;

    /// <summary>
    /// One-based line number
    /// </summary>
    public int LineNumber { get; }

    public GherkinLine(string line, int lineNumber)
    {
        LineNumber = lineNumber;

        lineText = line;
        trimmedLineText = lineText.TrimStart();
    }

    /// <summary>
    /// The number of whitespace characters in the beginning of the line.
    /// </summary>
    public int Indent
    {
        get { return lineText.Length - trimmedLineText.Length; }
    }

    /// <summary>
    /// Gets if the line is empty or contains whitespaces only.
    /// </summary>
    /// <returns>true, if empty or contains whitespaces only; otherwise, false.</returns>
    public bool IsEmpty()
    {
        return trimmedLineText.Length == 0;
    }

    /// <summary>
    /// Determines whether the beginning of the line (wihtout whitespaces) matches a specified string.
    /// </summary>
    /// <param name="text">The string to compare. </param>
    /// <returns>true if text matches the beginning of this line; otherwise, false.</returns>
    public bool StartsWith(string text)
    {
        return trimmedLineText.StartsWith(text, StringComparison.Ordinal);
    }

    /// <summary>
    /// Determines whether the beginning of the line (wihtout whitespaces) matches a specified title keyword (ie. a keyword followed by a ':' character).
    /// </summary>
    /// <param name="text">The keyword to compare.</param>
    /// <returns>true if keyword matches the beginning of this line and followed by a ':' character; otherwise, false.</returns>
    public bool StartsWithTitleKeyword(string text)
    {
        return StringUtils.StartsWith(trimmedLineText, text) &&
            StartsWithFrom(trimmedLineText, text.Length, GherkinLanguageConstants.TITLE_KEYWORD_SEPARATOR);
    }

    private static bool StartsWithFrom(string text, int textIndex, string value)
    {
        return string.CompareOrdinal(text, textIndex, value, 0, value.Length) == 0;
    }

    /// <summary>
    /// Returns the line text
    /// </summary>
    /// <param name="indentToRemove">The maximum number of whitespace characters to remove. -1 removes all leading whitespaces.</param>
    /// <returns>The line text.</returns>
    public string GetLineText(int indentToRemove = 0)
    {
        if (indentToRemove < 0 || indentToRemove > Indent)
            return trimmedLineText;

        return lineText.Substring(indentToRemove);
    }

    /// <summary>
    /// Returns the remaining part of the line.
    /// </summary>
    /// <param name="length">Number of characters to skip from the beginning of the line, including indentation.</param>
    /// <returns></returns>
    public string GetRestTrimmed(int length)
    {
        return trimmedLineText.Substring(length).Trim();
    }

    /// <summary>
    /// Tries parsing the line as a tag list, and returns the tags wihtout the leading '@' characters.
    /// </summary>
    /// <returns>(position,text) pairs, position is 0-based index</returns>
    public IEnumerable<GherkinLineSpan> GetTags()
    {
        string uncommentedLine = trimmedLineText;
        var commentIndex = trimmedLineText.IndexOf(GherkinLanguageConstants.COMMENT_PREFIX[0]);
        while (commentIndex >= 0)
        {
            if (commentIndex == 0)
                yield break;
            if (Array.IndexOf(inlineWhitespaceChars, trimmedLineText[commentIndex - 1]) == 0)
            {
                uncommentedLine = uncommentedLine.Substring(0, commentIndex);
                break;
            }
            commentIndex = trimmedLineText.IndexOf(GherkinLanguageConstants.COMMENT_PREFIX[0], commentIndex + 1);
        }
        int position = Indent;
        foreach (string item in uncommentedLine.Split(GherkinLanguageConstants.TAG_PREFIX[0]))
        {
            if (item.Length > 0)
            {
                var tagName = GherkinLanguageConstants.TAG_PREFIX + item.TrimEnd(inlineWhitespaceChars);
                if (tagName.Length == 1)
                    continue;

                if (tagName.IndexOfAny(inlineWhitespaceChars) >= 0)
                    throw new InvalidTagException("A tag may not contain whitespace", new Location(LineNumber, position));

                yield return new GherkinLineSpan(position, tagName);
                position += item.Length;
            }
            position++; // separator
        }
    }

    /// <summary>
    /// Tries parsing the line as table row and returns the trimmed cell values.
    /// </summary>
    /// <returns>(position,text) pairs, position is 0-based index</returns>
    public IEnumerable<GherkinLineSpan> GetTableCells()
    {
        var rowEnum = trimmedLineText.GetEnumerator();
        bool isFirstRow = true;

        string cell = null;
        int pos = 0;
        int startPos = 0;

        static void EnsureCellText(ref string cell, string trimmedLineText, ref int startPos, int pos)
        {
            if (cell is not null)
                return;

            while (startPos < pos && Array.IndexOf(inlineWhitespaceChars, trimmedLineText[startPos]) != -1)
                startPos++;

            cell = trimmedLineText.Substring(startPos, pos - startPos - 1);
        }

        while (rowEnum.MoveNext())
        {
            pos++;
            char c = rowEnum.Current;
            if (c == GherkinLanguageConstants.TABLE_CELL_SEPARATOR_CHAR)
            {
                if (isFirstRow)
                    isFirstRow = false;
                else
                {
                    EnsureCellText(ref cell, trimmedLineText, ref startPos, pos);
                    var cellText = cell.TrimEnd(inlineWhitespaceChars);

                    yield return new GherkinLineSpan(Indent + startPos + 1, cellText);
                }
                cell = null;
                startPos = pos;
            }
            else if (c == GherkinLanguageConstants.TABLE_CELL_ESCAPE_CHAR)
            {
                EnsureCellText(ref cell, trimmedLineText, ref startPos, pos);
                if (rowEnum.MoveNext())
                {
                    pos++;
                    c = rowEnum.Current;
                    if (c == GherkinLanguageConstants.TABLE_CELL_NEWLINE_ESCAPE)
                    {
                        cell += "\n";
                    }
                    else
                    {
                        if (c != GherkinLanguageConstants.TABLE_CELL_SEPARATOR_CHAR && c != GherkinLanguageConstants.TABLE_CELL_ESCAPE_CHAR)
                        {
                            cell += GherkinLanguageConstants.TABLE_CELL_ESCAPE_CHAR;
                        }
                        cell += c;
                    }
                }
                else
                {
                    cell += GherkinLanguageConstants.TABLE_CELL_ESCAPE_CHAR;
                }
            }
            else
            {
                if (cell is not null)
                    cell += c;
            }
        }
    }
}
