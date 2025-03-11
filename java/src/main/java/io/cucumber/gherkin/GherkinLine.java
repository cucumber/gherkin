package io.cucumber.gherkin;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.PrimitiveIterator;
import java.util.regex.Pattern;

import static io.cucumber.gherkin.GherkinLanguageConstants.TAG_PREFIX;
import static io.cucumber.gherkin.StringUtils.rtrim;

class GherkinLine implements IGherkinLine, Indentable {
    // TODO: set this to 0 when/if we change to 0-indexed columns
    private static final int OFFSET = 1;
    private static final Pattern PATTERN_ONLY_SPACES = Pattern.compile("^\\S+$");
    private final String lineText;
    private final int line;
    private final boolean emptyTrimmedLineText;
    private String trimmedLineText;
    private int indent;

    public GherkinLine(String lineText, int line) {
        this.lineText = lineText;
        this.line = line;
        StringUtils.trimAndIndent(lineText, this);
        emptyTrimmedLineText = trimmedLineText.isEmpty();
    }

    @Override
    public int indent() {
        return indent;
    }

    @Override
    public void detach() {

    }

    @Override
    public String getLineText(int indentToRemove) {
        if (indentToRemove < 0 || indentToRemove > indent())
            return trimmedLineText;
        return lineText.substring(indentToRemove);
    }

    @Override
    public boolean isEmpty() {
        return emptyTrimmedLineText;
    }

    @Override
    public boolean startsWith(String prefix) {
        return trimmedLineText.startsWith(prefix);
    }

    @Override
    public String getRestTrimmed(int length) {
        return trimmedLineText.substring(length).trim();
    }

    @Override
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
                throw new ParserException("A tag may not contain whitespace", new Location(line, column));
            }
            tags.add(new GherkinLineSpan(column, TAG_PREFIX + token));
            indexInUncommentedLine += element.length() + 1;
        }
        return tags;
    }

    @Override
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
                        GherkinLineSpan gherkinLineSpan = new GherkinLineSpan(cellStart + OFFSET);
                        StringUtils.trimAndIndentKeepNewLines(cellBuilder.toString(), gherkinLineSpan);
                        lineSpans.add(gherkinLineSpan);
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

    @Override
    public boolean startsWithTitleKeyword(String text) {
        int textLength = text.length();
        return trimmedLineText.length() > textLength &&
                trimmedLineText.startsWith(text) &&
                trimmedLineText.startsWith(GherkinLanguageConstants.TITLE_KEYWORD_SEPARATOR, textLength);
    }

    @Override
    public void indent(int indent, String trimmedText) {
        this.indent = indent;
        this.trimmedLineText = trimmedText;
    }

}
