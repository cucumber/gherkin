package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;

import java.util.ArrayList;
import java.util.List;

import static io.cucumber.gherkin.Constants.COMMENT_PREFIX_CHAR;
import static io.cucumber.gherkin.Constants.TAG_PREFIX_CHAR;
import static io.cucumber.gherkin.Locations.COLUMN_OFFSET;
import static io.cucumber.gherkin.StringUtils.containsWhitespace;
import static io.cucumber.gherkin.StringUtils.isWhitespace;

final class TagLine {

    private TagLine() {

    }

    static List<LineSpan> parse(int indent, String text, Location location) {
        int textLength = text.length();
        // parseTags is guarded by token.line.startsWith(TAG_PREFIX_CHAR) 
        // so there is always at least one tag, and it sits at the start of the
        // text
        int indexStartCurrentTag = 0;
        int indexEndOfLine = 1;
        while (indexEndOfLine < textLength && !(text.charAt(indexEndOfLine) == COMMENT_PREFIX_CHAR && isWhitespace(text.charAt(indexEndOfLine - 1)))) {
            indexEndOfLine++;
        }

        List<LineSpan> tags = new ArrayList<>();
        int indexEndCurrentTag;
        int indexStartPreviousTag = 0;
        int totalCodePointCount = 0;
        while (indexStartCurrentTag < indexEndOfLine) {
            // look for the next tag
            int indexStartNextTag = indexStartCurrentTag + 1;
            while (indexStartNextTag < indexEndOfLine && text.charAt(indexStartNextTag) != TAG_PREFIX_CHAR) {
                indexStartNextTag++;
            }

            // look for the end of current tag (going back from begin of next tag)
            indexEndCurrentTag = indexStartNextTag - 1;
            while (indexEndCurrentTag > indexStartCurrentTag && isWhitespace(text.charAt(indexEndCurrentTag))) {
                indexEndCurrentTag--;
            }
            indexEndCurrentTag++;

            if (indexEndCurrentTag > indexStartCurrentTag + 1) {
                // non-empty tag found, check that the tag does not contain whitespace characters

                // totalCodePointCount is updated incrementally
                totalCodePointCount += text.codePointCount(indexStartPreviousTag, indexStartCurrentTag);
                indexStartPreviousTag = indexStartCurrentTag;
                int column = indent + totalCodePointCount + COLUMN_OFFSET;
                if (containsWhitespace(text, indexStartCurrentTag + 1, indexEndCurrentTag)) {
                    throw new ParserException("A tag may not contain whitespace", Locations.atColumn(location, column));
                }
                // build the line span
                String token = text.substring(indexStartCurrentTag, indexEndCurrentTag);
                tags.add(new LineSpan(column, token));
            }

            // setup for the next tag
            indexStartCurrentTag = indexStartNextTag;
        }
        return tags;
    }

}
