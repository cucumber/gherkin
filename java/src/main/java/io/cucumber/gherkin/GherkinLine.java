package io.cucumber.gherkin;

import java.util.ArrayList;
import java.util.List;
import java.util.PrimitiveIterator;

import static io.cucumber.gherkin.GherkinLanguageConstants.TITLE_KEYWORD_SEPARATOR;
import static io.cucumber.gherkin.Locations.COLUMN_OFFSET;
import static io.cucumber.gherkin.StringUtils.trimAndIndent;
import static io.cucumber.gherkin.StringUtils.trimAndIndentKeepNewLines;
import static java.util.Objects.requireNonNull;

class GherkinLine {

    /**
     * The line text, including all leading and trailing whitespace characters.
     */
    private final String rawText;
    private final boolean empty;
    
    /**
     * The line text with any whitespace characters trimmed.
     */
    private final String text;
    
    /**
     * The offset in code-points of the first non-whitespace character in this
     * line.
     */
    private final int indent;
    private final int textLength;

    GherkinLine(String rawText) {
        this.rawText = requireNonNull(rawText);
        StringUtils.IndentedText trimmedIndent = trimAndIndent(rawText);
        this.text = trimmedIndent.getText();
        this.indent = trimmedIndent.getIndent();
        this.textLength = text.length();
        this.empty = text.isEmpty();
    }

    int getIndent() {
        return indent;
    }

    String getText() {
        return text;
    }

    String getRawText() {
        return rawText;
    }

    String getRawTextSubstring(int beginIndex) {
        return rawText.substring(beginIndex);
    }

    boolean isEmpty() {
        return empty;
    }

    boolean startsWith(String prefix) {
        return text.startsWith(prefix);
    }

    public boolean startsWith(char prefix) {
        return !empty && text.charAt(0) == prefix;
    }

    String substringTrimmed(int beginIndex) {
        // trim the beginning of the line (the end of line has already been trimmed in the constructor)
        return StringUtils.substringAndTrim(text, beginIndex);
    }

    List<GherkinLineSpan> parseTableCells() {
        List<GherkinLineSpan> lineSpans = new ArrayList<>();
        StringBuilder cellBuilder = new StringBuilder();
        boolean beforeFirst = true;
        int col = 0;
        int cellStart = 0;
        boolean escape = false;
        PrimitiveIterator.OfInt iterator = text.codePoints().iterator();
        while (iterator.hasNext()) {
            int c = iterator.next();
            if (escape) {
                switch (c) {
                    case 'n':
                        cellBuilder.append('\n');
                        break;
                    case '\\':
                        cellBuilder.append('\\');
                        break;
                    case '|':
                        cellBuilder.append('|');
                        break;
                    default:
                        // Invalid escape. We'll just ignore it.
                        cellBuilder.append("\\");
                        cellBuilder.appendCodePoint(c);
                        break;
                }
                escape = false;
            } else {
                if (c == '\\') {
                    escape = true;
                } else if (c == '|') {
                    if (beforeFirst) {
                        // Skip the first empty span
                        beforeFirst = false;
                    } else {
                        StringUtils.IndentedText trimmedCellIndent = trimAndIndentKeepNewLines(cellBuilder.toString());
                        int column = indent + cellStart + trimmedCellIndent.getIndent() + COLUMN_OFFSET;
                        lineSpans.add(new GherkinLineSpan(column, trimmedCellIndent.getText()));
                    }
                    cellBuilder.setLength(0);// reuse instance rather than creating a new one is faster
                    cellStart = col + 1;
                } else {
                    cellBuilder.appendCodePoint(c);
                }
            }
            col++;
        }
        return lineSpans;
    }

    boolean startsWithTitleKeyword(String keyword) {
        int keywordLength = keyword.length();
        return textLength > keywordLength &&
               text.charAt(keywordLength) == TITLE_KEYWORD_SEPARATOR &&
               text.startsWith(keyword);
    }

}
