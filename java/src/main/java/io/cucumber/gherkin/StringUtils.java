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
        // Fast path, common whitespace
        if (c == ' ' || c == '\t') {
            return true;
        }
        // There are 25 whitespace characters, we really only expect spaces and
        // tabs. So here, for valid feature files, we want to efficiently
        // determine if a character is not one of those remaining 23 whitespaces.
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
        if (c < ' ') {
            // Slow path here is okay because: 
            // * Characters before space are not expected to be used
            // * No Gherkin keyword starts with these characters
            return isWhiteSpaceSlow(c);
        }

        if (c >= '\u1680') {
            if (c <= '\u3000') {
                // Slow path here is okay because: 
                // * Whitespace characters in this range are not expected to be used
                // * No Gherkin keyword starts with any of these characters
                return isWhiteSpaceSlow(c);
            }
            return false;
        }

        // Test only whitespace characters in the range (32, 5760).
        return c == '\u0085' || c == '\u00a0';
    }

    static boolean isWhitespaceNoIf(char c) {
        return (c == ' ' || c == '\t') ||
                (c < ' ' && isWhiteSpaceSlow(c)) ||
                (c >= '\u1680' && c <= '\u3000' && isWhiteSpaceSlow(c)) ||
                (c == '\u0085' || c == '\u00a0');
    }

    static boolean isWhitespaceLt32OrRange5760To12288ThenSparseSpaces(char c) {
        /*
        Catégorie 1(0..31) : 0 occurrences
        Catégorie 2(32..32) : 2072 occurrences
        Catégorie 3(33..133) : 38 occurrences
        Catégorie 4(134..160) : 0 occurrences
        Catégorie 5(161..5760) : 177 occurrences
        Catégorie 6(5761..12288) : 0 occurrences
        Catégorie 7(12289..65535) : 44 occurrences
         */
        // Fast path, common whitespace
        if (c == ' ' || c == '\t') {
            return true;
        }
        // The range below contains both whitespace and characters.
        //
        // * The characters in this range do not start a valid keyword (at
        //   present).
        // * The spaces in this range are not expected to be used in actual
        //   feature files
        //
        // So the slow path is okay for both.
        if (c < 32 || (c >= 5760 && c <= 12288)) {
            return isCharacterTypeSpace(c) || isDirectionalitySpace(c);
        }
        // Test only spaces characters not covered by the range above
        return c == 133 || c == 160;
    }
    static boolean isWhitespaceLt32OrRange5760To12288ThenSparseSpacesNoIf(char c) {
        return (c == ' ' || c == '\t') // Cas commun
                || ((c < 32 || (c >= 5760 && c <= 12288))
                && (isCharacterTypeSpace(c) || isDirectionalitySpace(c))) // plage basse et haute
                || (c == 133 || c == 160);// caractères spécifiques
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
