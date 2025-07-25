package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;

import java.util.ArrayList;
import java.util.List;
import java.util.PrimitiveIterator;

import static io.cucumber.gherkin.GherkinLanguageConstants.TAG_PREFIX_CHAR;
import static io.cucumber.gherkin.GherkinLanguageConstants.TITLE_KEYWORD_SEPARATOR;
import static io.cucumber.gherkin.Locations.COLUMN_OFFSET;
import static io.cucumber.gherkin.StringUtils.containsWhiteSpaceExtended;
import static io.cucumber.gherkin.StringUtils.isWhiteSpaceExtended;
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
    private final int textLength;

    GherkinLine(String rawText, Location location) {
        this.rawText = requireNonNull(rawText);
        this.location = requireNonNull(location);
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
        while ((beginIndex < textLength) && (text.charAt(beginIndex) <= ' ')) {
            beginIndex++;
        }
        return text.substring(beginIndex);
    }

    List<GherkinLineSpan> parseTags() {
        // in most cases, the line contains no tag, so the code is optimized for this situation
        if (empty) {
            return emptyList();
        }

        // look for the first tag
        int indexStartCurrentTag = text.indexOf(TAG_PREFIX_CHAR);
        int indexComment = StringUtils.findIndexOfTagComment(text);
        if (indexStartCurrentTag < 0 || (indexComment >= 0 && indexStartCurrentTag > indexComment)) {
            // no tag found (or all tags are commented out)
            return emptyList();
        }

        List<GherkinLineSpan> tags = new ArrayList<>();
        int indexEndOfLine = indexComment >= 0 ? indexComment : text.length();
        int indexEndCurrentTag;
        while (indexStartCurrentTag < indexEndOfLine) {
            // look for the next tag
            int indexStartNextTag = indexStartCurrentTag + 1;
            while (indexStartNextTag < indexEndOfLine && text.charAt(indexStartNextTag) != TAG_PREFIX_CHAR) {
                indexStartNextTag++;
            }

            // look for the end of current tag (going back from begin of next tag)
            indexEndCurrentTag = indexStartNextTag - 1;
            while (indexEndCurrentTag > indexStartCurrentTag && isWhiteSpaceExtended(text.charAt(indexEndCurrentTag))) {
                indexEndCurrentTag--;
            }
            indexEndCurrentTag++;

            if (indexEndCurrentTag > indexStartCurrentTag + 1) {
                // non-empty tag found
                // check that the tag does not contain whitespace characters
                int symbolLength = text.codePointCount(0, indexStartCurrentTag);
                int column = indent + symbolLength + COLUMN_OFFSET;
                if(containsWhiteSpaceExtended(text, indexStartCurrentTag + 1, indexEndCurrentTag)){
                    throw new ParserException("A tag may not contain whitespace", Locations.atColumn(location, column));
                }
                // build the line span
                String token = text.substring(indexStartCurrentTag, indexEndCurrentTag);
                tags.add(new GherkinLineSpan(column, token));
            }

            // setup for the next tag
            indexStartCurrentTag = indexStartNextTag;
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
        return textLength > keyword.length() &&
               text.charAt(keyword.length()) == TITLE_KEYWORD_SEPARATOR &&
               text.startsWith(keyword);
    }

}
