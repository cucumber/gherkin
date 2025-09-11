package io.cucumber.gherkin;


final class StringUtils {
    private static final IndentedText NO_INDENT_ENTRY = new IndentedText(0, "");

    /**
     * Array to indicate presence of whitespace characters.
     * WHITESPACE_CHARS[' ']==true if ' ' is a whitespace character.
     * There is no whitespace character with a value > 12288.
     * The memory footprint is 12289 x 1 byte = 12289 bytes. This is
     * relatively large, but about 30% faster than java.util.BitSet.
     */
    private static final boolean[] WHITESPACE_CHARS = new boolean[12289];
    static {
        // Initialisation des valeurs connues
        int[] numbers = {
                9, 10, 11, 12, 13, 28, 29, 30, 31, 32,
                133, 160, 5760, 8192, 8193, 8194, 8195,
                8196, 8197, 8198, 8199, 8200, 8201, 8202,
                8232, 8233, 8239, 8287, 12288
        };
        for (int number : numbers) {
            WHITESPACE_CHARS[number] = true;
        }
    }

    /**
     * An extended definition of Whitespace minus new lines.
     * <p>
     * Character in Unicode general category {@code Zs} and directionality
     * categories {@code WS}, {@code B}, and {@code S} are considered whitespace
     * for this definition.
     *
     * @param c character to test
     * @return true iff the {@code c} is whitespace and not new line.
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
        return c < WHITESPACE_CHARS.length && WHITESPACE_CHARS[c];
    }

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

    static String substringAndLeftTrim(String input, int beginIndex, int endIndex) {
        int start = beginIndex;
        while (start < endIndex && isWhitespace(input.charAt(start))) {
            start++;
        }
        return input.substring(start);
    }

    static final class IndentedText {
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
