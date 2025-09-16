package io.cucumber.gherkin;


final class StringUtils {

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
     * Characters in Unicode general category {@code Zs} and directionality
     * categories {@code WS}, {@code B}, and {@code S} are considered whitespace
     * for this definition.
     *
     * @param c character to test
     * @return true iff the {@code c} is whitespace.
     */
    static boolean isWhitespace(char c) {
        // This method is about twice faster than `isWhiteSpaceSlow(c)`.
        // It has been optimized based on the expected use-cases
        // (4 spaces and first letter of the keywords).
        // Within this test set, the character distribution is as follows:
        //  Category 1(0..31) : 0 occurrences
        //  Category 2(32..32) : 1036 occurrences
        //  Category 3(33..133) : 38 occurrences
        //  Category 4(134..160) : 0 occurrences
        //  Category 5(161..5760) : 177 occurrences
        //  Category 6(5761..12288) : 0 occurrences
        //  Category 7(12289..65535) : 44 occurrences
        // This sacrifies some readability for performance.

        // Fast path, common whitespace
        return (c == ' ' || c == '\t')
        // There are 29 whitespace characters, we really only expect spaces and
        // tabs. So here, for valid feature files, we want to efficiently
        // determine if a character is not one of those remaining 27 whitespaces.
        //
        // We also know that valid feature files support a limited number of
        // keywords, so we only have to optimize performance against detecting
        // the first letters of those keywords.
        //
        // The whitespaces and first keyword characters are clustered in several
        // semi-consecutive ranges. We can use this to quickly rule out a
        // characters potential for being a whitespace character.
        //
        // |                    | c --->                                                       |
        // | whitespace         | 10-32 |     | 133 || 160 |       | 5760-12288 |              |
        // | keyword characters |       || 39----------------4877 ||            || 12363-55357 |

            // Slow path here is okay because:
            // * Characters before space are not expected to be used
            // * No Gherkin keyword starts with these characters
            || ((c < ' ' || (c >= '\u1680' && c <= '\u3000')) && isWhiteSpaceSlow(c))

            // Test only whitespace characters in the range (32, 5760).
            || (c == '\u0085' || c == '\u00a0');
    }

    static boolean isWhiteSpaceSlow(char c) {
        return isCharacterTypeSpace(c) || isDirectionalitySpace(c);
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
