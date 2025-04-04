package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map.Entry;
import java.util.PrimitiveIterator;
import java.util.regex.Pattern;

import static io.cucumber.gherkin.GherkinLanguageConstants.TAG_PREFIX;
import static io.cucumber.gherkin.StringUtils.rtrim;
import static io.cucumber.gherkin.StringUtils.trimAndIndent;
import static io.cucumber.gherkin.StringUtils.trimAndIndentKeepNewLines;
import static java.util.Objects.requireNonNull;

class GherkinLine {
    // TODO: set this to 0 when/if we change to 0-indexed columns
    private static final int OFFSET = 1;
    private static final Pattern PATTERN_ONLY_SPACES = Pattern.compile("^\\S+$");

    private final String lineText;
    private final Location line;
    private final boolean emptyTrimmedLineText;
    private final String trimmedLineText;
    private final int indent;

    public GherkinLine(String lineText, Location line) {
        this.lineText = requireNonNull(lineText);
        this.line = requireNonNull(line);
        Entry<String, Integer> trimmedIndent = trimAndIndent(lineText);
        this.trimmedLineText = trimmedIndent.getKey();
        this.indent = trimmedIndent.getValue();
        this.emptyTrimmedLineText = trimmedLineText.isEmpty();
    }

    public int indent() {
        return indent;
    }

    public String getLineText(int indentToRemove) {
        if (indentToRemove < 0 || indentToRemove > indent())
            return trimmedLineText;
        return lineText.substring(indentToRemove);
    }

    public boolean isEmpty() {
        return emptyTrimmedLineText;
    }

    public boolean startsWith(String prefix) {
        return trimmedLineText.startsWith(prefix);
    }

    public String getRestTrimmed(int length) {
        return trimmedLineText.substring(length).trim();
    }

    public List<GherkinLineSpan> getTags() {
        // in most cases, the line contains no tag, so the code is optimized for this situation
        if (emptyTrimmedLineText) {
            return Collections.emptyList();
        }
        String uncommentedLine = StringUtils.removeComments(trimmedLineText);
        int indexInUncommentedLine = 0;

        String[] elements = uncommentedLine.split(TAG_PREFIX);
        if (elements.length == 0) {
            return Collections.emptyList();
        }
        List<GherkinLineSpan> tags = new ArrayList<>(elements.length);
        for (String element : elements) {
            String token = rtrim(element);
            if (token.isEmpty()) {
                continue;
            }
            int symbolLength = uncommentedLine.codePointCount(0, indexInUncommentedLine);
            int column = indent() + symbolLength + 1;
            if (!PATTERN_ONLY_SPACES.matcher(token).matches()) {
                throw new ParserException("A tag may not contain whitespace", Locations.atColumn(line, column));
            }
            tags.add(new GherkinLineSpan(column, TAG_PREFIX + token));
            indexInUncommentedLine += element.length() + 1;
        }
        return tags;
    }

    public List<GherkinLineSpan> getTableCells() {
        List<GherkinLineSpan> lineSpans = new ArrayList<>();
        StringBuilder cellBuilder = new StringBuilder();
        boolean beforeFirst = true;
        int col = 0;
        int cellStart = 0;
        boolean escape = false;
        PrimitiveIterator.OfInt iterator = lineText.codePoints().iterator();
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
                        Entry<String, Integer> trimmedIndent = trimAndIndentKeepNewLines(cellBuilder.toString());
                        int indent = OFFSET + cellStart + trimmedIndent.getValue();
                        lineSpans.add(new GherkinLineSpan(indent, trimmedIndent.getKey()));
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

    public boolean startsWithTitleKeyword(String text) {
        int textLength = text.length();
        return trimmedLineText.length() > textLength &&
                trimmedLineText.startsWith(text) &&
                trimmedLineText.startsWith(GherkinLanguageConstants.TITLE_KEYWORD_SEPARATOR, textLength);
    }

}
