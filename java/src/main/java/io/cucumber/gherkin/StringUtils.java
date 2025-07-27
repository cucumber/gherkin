package io.cucumber.gherkin;


class StringUtils {

    /**
     * An extended definition of Whitespace minus new lines.
     * <p>
     * Character in Unicode general category {@code Zs} and directionality
     * categories {@code WS}, {@code B}, and {@code S} are considered whitespace
     * for this definition.
     *
     * @param c character to test
     * @return true iff the {@code c} is whitespace and not new line..
     */
    private static boolean isWhitespaceExcludingNewLine(char c) {
        return c != '\n' && isWhitespace(c);
    }

    /**
     * An extended definition of Whitespace.
     * <p>
     * Character in Unicode general category {@code Zs} and directionality
     * categories {@code WS}, {@code B}, and {@code S} are considered whitespace
     * for this definition.
     *
     * @param c character to test
     * @return true iff the {@code c} is whitespace.
     */
    static boolean isWhitespace(char c) {
        // Fast path for the common case
        return c == ' ' || c == '\t' || isCharacterTypeSpace(c) || isDirectionalitySpace(c);
    }

    private static boolean isCharacterTypeSpace(char c) {
        return (((
                (1 << Character.SPACE_SEPARATOR)
                        // Not in the definition, but a subset of isDirectionalitySpace
                        | (1 << Character.LINE_SEPARATOR)
                        // Not in the definition, but a subset of isDirectionalitySpace
                        | (1 << Character.PARAGRAPH_SEPARATOR)
        ) >> Character.getType(c)) & 1) != 0;
    }

    private static boolean isDirectionalitySpace(char c) {
        return (
                (((1 << Character.DIRECTIONALITY_WHITESPACE)
                        | (1 << Character.DIRECTIONALITY_PARAGRAPH_SEPARATOR)
                        | (1 << Character.DIRECTIONALITY_SEGMENT_SEPARATOR)
                ) >> Character.getDirectionality(c)) & 1) != 0;
    }

    private static final IndentedText NO_INDENT_ENTRY = new IndentedText(0, "");

    static IndentedText trimAndIndentKeepNewLines(String input) {
        int length = input.length();
        if (length == 0) {
            return NO_INDENT_ENTRY;
        }

        int start = 0;
        while (start < length && isWhitespaceExcludingNewLine(input.charAt(start))) {
            start++;
        }
        int end = length;
        while (end > start && isWhitespaceExcludingNewLine(input.charAt(end - 1))) {
            end--;
        }
        String trimmed = input.substring(start, end);
        int indent = input.codePointCount(0, start);
        // the object instance is not truly created because
        // the code is inlined by the hotspot compiler
        // (as "-XX:+EliminateAllocations" is enabled by default).
        return new IndentedText(indent, trimmed);
    }

    static IndentedText trimAndIndent(String input) {
        int length = input.length();
        if (length == 0) {
            return NO_INDENT_ENTRY;
        }
        int start = 0;
        while (start < length && isWhitespace(input.charAt(start))) {
            start++;
        }
        int end = length;
        while (end > start && isWhitespace(input.charAt(end - 1))) {
            end--;
        }
        String trimmed = input.substring(start, end);
        int indent = input.codePointCount(0, start);
        // the object instance is not truly created because
        // the code is inlined by the hotspot compiler
        // (as "-XX:+EliminateAllocations" is enabled by default).
        return new IndentedText(indent, trimmed);
    }

    static boolean containsWhitespace(String input, int fromIndex, int toIndex) {
        for (int i = fromIndex; i < toIndex; i++) {
            if (isWhitespace(input.charAt(i))) {
                return true;
            }
        }
        return false;
    }

    static String substringAndTrim(String input, int beginIndex) {
        int length = input.length();
        int start = beginIndex;
        while (start < length && isWhitespace(input.charAt(start))) {
            start++;
        }
        return input.substring(start);
    }

    static class IndentedText {
        private final int indent;
        private final String text;

        IndentedText(int indent, String text) {
            this.text = text;
            this.indent = indent;
        }

        int getIndent() {
            return indent;
        }

        String getText() {
            return text;
        }

    }
}
