package io.cucumber.gherkin;

import static io.cucumber.gherkin.Constants.TITLE_KEYWORD_SEPARATOR;
import static io.cucumber.gherkin.StringUtils.trimAndIndent;
import static java.util.Objects.requireNonNull;

final class Line {

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

    Line(String rawText) {
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

    String getRawTextSubstring(int indentToRemove) {
        return rawText.substring(rawText.offsetByCodePoints(0, indentToRemove));
    }

    boolean isEmpty() {
        return empty;
    }

    boolean startsWith(String prefix) {
        return text.startsWith(prefix);
    }

    /**
     * The text is expected to be non-empty.
     * This is an optimized version of startsWith(prefix) that
     * avoids checking the prefix length for most negative matches.
     * @param firstChar the first character of the prefix
     * @param prefixAfterFirstChar the prefix after the first character.
     * @return true if the text starts with the given prefix, false otherwise.
     */
    boolean startsWith(char firstChar, String prefixAfterFirstChar) {
        return text.charAt(0) == firstChar && // fast check for the first character (avoids startsWith to compute the prefix length)
               text.startsWith(prefixAfterFirstChar, 1);
    }

    boolean startsWith(char prefix) {
        return !empty && text.charAt(0) == prefix;
    }

    String substringTrimmed(int beginIndex) {
        // trim the beginning of the line (the end of line has already been trimmed in the constructor)
        return StringUtils.substringAndLeftTrim(text, beginIndex, textLength);
    }

    boolean startsWithTitleKeyword(String keyword, int keywordLength) {
        return textLength > keywordLength &&
               text.charAt(keywordLength) == TITLE_KEYWORD_SEPARATOR &&
               text.startsWith(keyword);
    }

}
