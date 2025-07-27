package io.cucumber.gherkin;

import static io.cucumber.gherkin.GherkinLanguageConstants.TITLE_KEYWORD_SEPARATOR;
import static io.cucumber.gherkin.StringUtils.trimAndIndent;
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

    String getRawTextSubstring(int indentToRemove) {
        return rawText.substring(rawText.offsetByCodePoints(0, indentToRemove));
    }

    boolean isEmpty() {
        return empty;
    }

    boolean startsWith(String prefix) {
        return text.startsWith(prefix);
    }

    boolean startsWith(char prefix) {
        return !empty && text.charAt(0) == prefix;
    }

    String substringTrimmed(int beginIndex) {
        // trim the beginning of the line (the end of line has already been trimmed in the constructor)
        return StringUtils.substringAndTrim(text, beginIndex);
    }

    boolean startsWithTitleKeyword(String keyword) {
        int keywordLength = keyword.length();
        return textLength > keywordLength &&
               text.charAt(keywordLength) == TITLE_KEYWORD_SEPARATOR &&
               text.startsWith(keyword);
    }

}
