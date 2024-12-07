using Gherkin.Ast;

namespace Gherkin;

public class GherkinLine : IGherkinLine
{
    private static char[] inlineWhitespaceChars = [' ', '\t', '\u00A0'];

    private readonly string lineText;
    private readonly string trimmedLineText;
    public int LineNumber { get; }

    public GherkinLine(string line, int lineNumber)
    {
        LineNumber = lineNumber;

        lineText = line;
        trimmedLineText = lineText.TrimStart();
    }

    public void Detach()
    {
        //nop
    }

    public int Indent
    {
        get { return lineText.Length - trimmedLineText.Length; }
    }

    public bool IsEmpty()
    {
        return trimmedLineText.Length == 0;
    }

    public bool StartsWith(string text)
    {
        return trimmedLineText.StartsWith(text, StringComparison.Ordinal);
    }

    public bool StartsWithTitleKeyword(string text)
    {
        return StringUtils.StartsWith(trimmedLineText, text) &&
            StartsWithFrom(trimmedLineText, text.Length, GherkinLanguageConstants.TITLE_KEYWORD_SEPARATOR);
    }

    private static bool StartsWithFrom(string text, int textIndex, string value)
    {
        return string.CompareOrdinal(text, textIndex, value, 0, value.Length) == 0;
    }

    public string GetLineText(int indentToRemove)
    {
        if (indentToRemove < 0 || indentToRemove > Indent)
            return trimmedLineText;

        return lineText.Substring(indentToRemove);
    }

    public string GetRestTrimmed(int length)
    {
        return trimmedLineText.Substring(length).Trim();
    }

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
