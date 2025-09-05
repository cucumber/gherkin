using Gherkin.Ast;
using System.Collections;

namespace Gherkin;

/// <summary>
/// Represents a line of a Gherkin file
/// </summary>
public readonly struct GherkinLine
{
    private static readonly char[] inlineWhitespaceChars = [' ', '\t', '\u00A0'];

    private readonly string lineText;
    private readonly int trimmedStartIndex;

    /// <summary>
    /// One-based line number
    /// </summary>
    public int LineNumber { get; }

    public GherkinLine(string line, int lineNumber)
    {
        LineNumber = lineNumber;

        lineText = line;
        int start;
        for (start = 0; start < lineText.Length; start++)
        {
            if (!char.IsWhiteSpace(lineText[start]))
                break;
        }
        trimmedStartIndex = start;
    }

    /// <summary>
    /// The number of whitespace characters in the beginning of the line.
    /// </summary>
    public int Indent
    {
        get { return trimmedStartIndex; }
    }

    /// <summary>
    /// Gets if the line is empty or contains whitespaces only.
    /// </summary>
    /// <returns>true, if empty or contains whitespaces only; otherwise, false.</returns>
    public bool IsEmpty()
    {
        return lineText.Length == trimmedStartIndex;
    }

    /// <summary>
    /// Determines whether the beginning of the line (wihtout whitespaces) matches a specified string.
    /// </summary>
    /// <param name="text">The string to compare. </param>
    /// <returns>true if text matches the beginning of this line; otherwise, false.</returns>
    public bool StartsWith(string text)
    {
        return string.CompareOrdinal(lineText, trimmedStartIndex, text, 0, text.Length) == 0;
    }

    /// <summary>
    /// Determines whether the beginning of the line (wihtout whitespaces) matches a specified title keyword (ie. a keyword followed by a ':' character).
    /// </summary>
    /// <param name="text">The keyword to compare.</param>
    /// <returns>true if keyword matches the beginning of this line and followed by a ':' character; otherwise, false.</returns>
    public bool StartsWithTitleKeyword(string text)
    {
        return StartsWith(text) &&
            StartsWithFrom(lineText, trimmedStartIndex + text.Length, GherkinLanguageConstants.TITLE_KEYWORD_SEPARATOR);
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
            return lineText.Substring(trimmedStartIndex);

        return lineText.Substring(indentToRemove);
    }

    /// <summary>
    /// Returns the remaining part of the line.
    /// </summary>
    /// <param name="length">Number of characters to skip from the beginning of the line, including indentation.</param>
    /// <returns></returns>
    public string GetRestTrimmed(int length)
    {
        return lineText.Substring(trimmedStartIndex + length).Trim();
    }

    public readonly struct TagsEnumerable : IEnumerable<GherkinLineSpan>
    {
        readonly int lineNumber;
        readonly string uncommentedLine;
        readonly int position;
        public TagsEnumerable(int lineNumber, string lineText, int trimmedStartIndex)
        {
            this.lineNumber = lineNumber;
            uncommentedLine = lineText;
            var commentIndex = lineText.IndexOf(GherkinLanguageConstants.COMMENT_PREFIX[0], trimmedStartIndex);
            while (commentIndex >= 0)
            {
                if (commentIndex == 0)
                {
                    position = -1;
                    return;
                }
                if (Array.IndexOf(inlineWhitespaceChars, lineText[commentIndex - 1]) != -1)
                {
                    uncommentedLine = uncommentedLine.Substring(0, commentIndex);
                    break;
                }
                commentIndex = lineText.IndexOf(GherkinLanguageConstants.COMMENT_PREFIX[0], commentIndex + 1);
            }
            position = uncommentedLine.IndexOf(GherkinLanguageConstants.TAG_PREFIX[0], trimmedStartIndex);
        }

        public TagsEnumerator GetEnumerator() => new TagsEnumerator(lineNumber, uncommentedLine, position);

        IEnumerator<GherkinLineSpan> IEnumerable<GherkinLineSpan>.GetEnumerator() => GetEnumerator();
        IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
    }

    public struct TagsEnumerator : IEnumerator<GherkinLineSpan>
    {
        readonly int lineNumber;
        readonly string uncommentedLine;
        int position;

        public TagsEnumerator(int lineNumber, string uncommentedLine, int position) : this()
        {
            this.lineNumber = lineNumber;
            this.uncommentedLine = uncommentedLine;
            this.position = position;
        }

        public GherkinLineSpan Current { readonly get; private set; }
        readonly object IEnumerator.Current => Current;

        public bool MoveNext()
        {
            while (position >= 0)
            {
                int nextPos = uncommentedLine.IndexOf(GherkinLanguageConstants.TAG_PREFIX[0], position + 1);
                int endPos;
                if (nextPos > 0)
                    endPos = nextPos - 1;
                else
                    endPos = uncommentedLine.Length - 1;

                while (endPos > position && Array.IndexOf(inlineWhitespaceChars, uncommentedLine[endPos]) != -1) // TrimEnd
                    endPos -= 1;

                int length = endPos - position + 1;
                if (length <= 1)
                {
                    position = nextPos;
                    continue;
                }

                var tagName = uncommentedLine.Substring(position, length);

                if (tagName.IndexOfAny(inlineWhitespaceChars) >= 0)
                    throw new InvalidTagException("A tag may not contain whitespace", new Location(lineNumber, position + 1));

                Current = new GherkinLineSpan(position + 1, tagName);
                position = nextPos;
                return true;
            }

            Current = default;
            return false;
        }

        readonly void IDisposable.Dispose()
        {
            // nothing to do
        }

        void IEnumerator.Reset() => throw new NotImplementedException();
    }

    /// <summary>
    /// Tries parsing the line as a tag list, and returns the tags wihtout the leading '@' characters.
    /// </summary>
    /// <returns>(position,text) pairs, position is 0-based index</returns>
    public TagsEnumerable GetTags() => new TagsEnumerable(LineNumber, lineText, trimmedStartIndex);

    public readonly struct TableCellsEnumerable(string lineText, int startPos) : IEnumerable<GherkinLineSpan>
    {
        public TableCellsEnumerator GetEnumerator() => new TableCellsEnumerator(lineText, startPos);

        IEnumerator<GherkinLineSpan> IEnumerable<GherkinLineSpan>.GetEnumerator() => GetEnumerator();
        IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
    }

    public struct TableCellsEnumerator : IEnumerator<GherkinLineSpan>
    {
        readonly string lineText;
        int startPos;
        int pos;
        bool isFirstRow;

        public TableCellsEnumerator(string lineText, int startPos)
        {
            this.lineText = lineText;
            this.startPos = startPos;
            this.pos = startPos;
            this.isFirstRow = true;
        }

        public GherkinLineSpan Current { readonly get; private set; }
        readonly object IEnumerator.Current => Current;

        void EnsureCellText(ref string cell, bool trim)
        {
            if (cell is not null)
            {
                if (trim)
                    cell = cell.TrimEnd(inlineWhitespaceChars);
                return;
            }

            while (startPos < pos && Array.IndexOf(inlineWhitespaceChars, lineText[startPos]) != -1)
                startPos++;

            int trimedPos = pos - 2;
            if (trim)
            {
                while (trimedPos >= startPos && Array.IndexOf(inlineWhitespaceChars, lineText[trimedPos]) != -1)
                    trimedPos--;
            }

            cell = lineText.Substring(startPos, trimedPos - startPos + 1);
        }

        public bool MoveNext()
        {
            string cell = null;

            while (pos < lineText.Length)
            {
                char c = lineText[pos];
                pos++;
                if (c == GherkinLanguageConstants.TABLE_CELL_SEPARATOR_CHAR)
                {
                    if (isFirstRow)
                    {
                        isFirstRow = false;
                        startPos = pos;
                    }
                    else
                    {
                        EnsureCellText(ref cell, true);

                        Current = new GherkinLineSpan(startPos + 1, cell);
                        startPos = pos;
                        return true;
                    }
                }
                else if (c == GherkinLanguageConstants.TABLE_CELL_ESCAPE_CHAR)
                {
                    EnsureCellText(ref cell, false);
                    if ((pos + 1) < lineText.Length)
                    {
                        c = lineText[pos];
                        pos++;
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

            return false;
        }

        readonly void IDisposable.Dispose()
        {
            // nothing to do
        }

        void IEnumerator.Reset() => throw new NotImplementedException();
    }

    /// <summary>
    /// Tries parsing the line as table row and returns the trimmed cell values.
    /// </summary>
    /// <returns>(position,text) pairs, position is 0-based index</returns>
    public TableCellsEnumerable GetTableCells() => new TableCellsEnumerable(lineText, trimmedStartIndex);
}
