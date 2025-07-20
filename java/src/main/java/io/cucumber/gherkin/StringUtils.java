package io.cucumber.gherkin;


import static io.cucumber.gherkin.GherkinLanguageConstants.COMMENT_PREFIX_CHAR;

class StringUtils {

    /**
     * Matches regex pattern for whitespace.
     */
    private static final char[] WHITESPACE_CHARS = new char[]{' ', '\t', '\n', '\u000B', '\f', '\r'};

    /**
     * Matches regex pattern whitespace + NEL + NBSP.
     */
    private static final char[] WHITESPACE_CHARS_EXTENDED = new char[]{' ', '\t', '\n', '\u000B', '\f', '\r', '\u0085', '\u00A0'};
    
    /**
     * Matches regex pattern whitespace + NEL + NBSP - new line.
     */
    private static final char[] WHITESPACE_CHARS_EXTENDED_KEEP_NEW_LINES = new char[]{' ', '\t', '\u000B', '\f', '\r', '\u0085', '\u00A0'};
    public static final IndentedText NO_INDENT_ENTRY = new IndentedText(0, "");

    static String rtrim(String s) {
        if (s.isEmpty()) {
            return s;
        }

        int length = s.length();

        int end = length - 1;
        while (end >= 0 && contains(WHITESPACE_CHARS_EXTENDED, s.charAt(end))) {
            end--;
        }

        return s.substring(0, end + 1);
    }

    static IndentedText trimAndIndentKeepNewLines(String input) {
        return trimAndIndent(input, WHITESPACE_CHARS_EXTENDED_KEEP_NEW_LINES);
    }

    static IndentedText trimAndIndent(String input) {
        return trimAndIndent(input, WHITESPACE_CHARS_EXTENDED);
    }

    private static IndentedText trimAndIndent(String input, char[] whitespaceChars) {
        if (input.isEmpty()) {
            return NO_INDENT_ENTRY;
        }

        int start = findFirstIndexNotIn(input, input.length(), whitespaceChars);
        int end = findLastIndexNotIn(input, start, whitespaceChars);

        String trimmed = input.substring(start, end);
        int indent = input.codePointCount(0, start);
        // the object instance is not truly created because
        // the code is inlined by the hotspot compiler
        // (as "-XX:+EliminateAllocations" is enabled by default).
        return new IndentedText(indent, trimmed);
    }

    static String removeComments(String input) {
        if (input.isEmpty()) {
            return input;
        }
        int start = 0;
        int length = input.length();

        while (start < length - 1 
                && !(contains(WHITESPACE_CHARS, input.charAt(start)) 
                && input.charAt(start + 1) == COMMENT_PREFIX_CHAR)
        ) {
            start++;
        }
        return input.substring(0, start < length - 1 ? start : start + 1);
    }

    static boolean containsWhiteSpace(String input) {
        return findFirstIndexIn(input, WHITESPACE_CHARS) != -1;
    }

    private static int findFirstIndexNotIn(String input, int endIndex, char[] characters) {
        int start = 0;
        while (start < endIndex && contains(characters, input.charAt(start))) {
            start++;
        }
        return start;
    }
    
    private static int findLastIndexNotIn(String input, int beginIndex, char[] characters) {
        int end = input.length();
        while (end > beginIndex && contains(characters, input.charAt(end - 1))) {
            end--;
        }
        return end;
    }

    private static int findFirstIndexIn(String input, char[] characters) {
        int length = input.length();
        for (int i = 0; i < length; i++) {
            if (contains(characters, input.charAt(i))) {
                return i;
            }
        }
        return -1;
    }
    
    private static boolean contains(char[] characters, char c) {
        for (char candidate : characters) {
            if (candidate == c) {
                return true;
            }
        }
        return false;
    }

    public static class IndentedText {
        private final int indent;
        private final String text;

        public IndentedText(int indent, String text) {
            this.text = text;
            this.indent = indent;
        }

        public int getIndent() {
            return indent;
        }

        public String getText() {
            return text;
        }

    }
}
