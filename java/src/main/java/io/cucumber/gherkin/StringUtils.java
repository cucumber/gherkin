package io.cucumber.gherkin;


final class StringUtils {

    /**
     * An extended definition of Whitespace minus new lines.
     *
     * @param c character to test
     * @return true iff the {@code c} is whitespace and not new line.
     * @see #isWhitespace(char)
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
        // It has been optimized based on the expected use-case of
        // left-trimming lines in valid feature files. 
        //
        // * There are 29 whitespace characters. However, we only expect spaces
        //   or tabs to be used.
        // * Valid feature files start each line with sequences of one or more
        //   spaces followed by a keyword character.
        // 
        // | category           | 0     | 1    | 2                        | 3          | 4             |
        // |                    | c --->                                                               |
        // | whitespace         | 10-31 | 32   |     | 133 || 160 |       | 5760-12288 |               |
        // | keyword characters |              || 39----------------4877 ||            || 12363-55357 ||
        // | occurrences        | 0     | 1036 |          215             |             | 44           |
        //
        // Plotting this information for a hypothetical feature that uses every
        // keyword indented with 4 spaces we can see that there are only a few
        // ranges that have to be checked.
        // 
        // Category 0: Control symbols
        // Category 1: Spaces (and tabs)
        // Category 2: Latin block to Unified Canadian Aboriginal Syllabics block
        // Category 3: Ogham block to the space in CJK Symbols and Punctuation
        // Category 4: CJK Symbols and Punctuation block minus space and onwards

        // Fast path, common whitespace
        // Note: Single boolean expression is faster than if-else
        return (c == ' ' || c == '\t')
                // Slow path here is okay because:
                // * Characters before space are not expected to be used
                // * No Gherkin keyword starts with these characters
                || ((c < ' ' || (c >= '\u1680' && c <= '\u3000')) && isWhiteSpaceSlow(c))
                // Test only two remaining whitespace characters in the range (32, 5760).
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
