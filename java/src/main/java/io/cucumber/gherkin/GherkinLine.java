package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;

import java.util.ArrayList;
import java.util.List;
import java.util.PrimitiveIterator;

import static io.cucumber.gherkin.GherkinLanguageConstants.TAG_PREFIX;
import static io.cucumber.gherkin.GherkinLanguageConstants.TITLE_KEYWORD_SEPARATOR;
import static io.cucumber.gherkin.Locations.COLUMN_OFFSET;
import static io.cucumber.gherkin.StringUtils.containsWhiteSpace;
import static io.cucumber.gherkin.StringUtils.rtrim;
import static io.cucumber.gherkin.StringUtils.trimAndIndent;
import static io.cucumber.gherkin.StringUtils.trimAndIndentKeepNewLines;
import static java.util.Collections.emptyList;
import static java.util.Objects.requireNonNull;

class GherkinLine {

    /**
     * The line text, including all leading and trailing whitespace characters.
     */
    private final String rawText;
    private final Location location;
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

    GherkinLine(String rawText, Location location) {
        this.rawText = requireNonNull(rawText);
        this.location = requireNonNull(location);
        StringUtils.TrimmedText trimmedIndent = trimAndIndent(rawText);
        this.text = trimmedIndent.getText();
        this.indent = trimmedIndent.getIndent();
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

    String substringTrimmed(int beginIndex) {
        return text.substring(beginIndex).trim();
    }

    List<GherkinLineSpan> parseTags() {
        // in most cases, the line contains no tag, so the code is optimized for this situation
        if (empty) {
            return emptyList();
        }
        String uncommentedLine = StringUtils.removeComments(text);
        int indexInUncommentedLine = 0;

        String[] elements = uncommentedLine.split(TAG_PREFIX);
        if (elements.length == 0) {
            return emptyList();
        }
        List<GherkinLineSpan> tags = new ArrayList<>(elements.length);
        for (String element : elements) {
            String token = rtrim(element);
            if (token.isEmpty()) {
                continue;
            }
            int symbolLength = uncommentedLine.codePointCount(0, indexInUncommentedLine);
            int column = indent + symbolLength + COLUMN_OFFSET;
            if (containsWhiteSpace(token)) {
                throw new ParserException("A tag may not contain whitespace", Locations.atColumn(location, column));
            }
            tags.add(new GherkinLineSpan(column, TAG_PREFIX + token));
            indexInUncommentedLine += element.length() + 1;
        }
        return tags;
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
                        StringUtils.TrimmedText trimmedCellIndent = trimAndIndentKeepNewLines(cellBuilder.toString());
                        int column = indent + cellStart + trimmedCellIndent.getIndent() + COLUMN_OFFSET;
                        lineSpans.add(new GherkinLineSpan(column, trimmedCellIndent.getText()));
                    }
                    cellBuilder = new StringBuilder();
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
        return text.length() > keywordLength &&
                text.startsWith(keyword) &&
                text.startsWith(TITLE_KEYWORD_SEPARATOR, keywordLength);
    }

}
