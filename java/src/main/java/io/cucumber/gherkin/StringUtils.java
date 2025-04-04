package io.cucumber.gherkin;


import java.util.AbstractMap.SimpleEntry;
import java.util.Map.Entry;

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

    static Entry<String, Integer> trimAndIndentKeepNewLines(String input) {
        return trimAndIndent(input, WHITESPACE_CHARS_EXTENDED_KEEP_NEW_LINES);
    }

    static Entry<String, Integer> trimAndIndent(String input) {
        return trimAndIndent(input, WHITESPACE_CHARS_EXTENDED);
    }

    private static Entry<String, Integer> trimAndIndent(String input, char[] whitespaceChars) {
        if (input.isEmpty()) {
            return new SimpleEntry<>("", 0);
        }

        int start = 0;
        int length = input.length();

        while (start < length && contains(whitespaceChars, input.charAt(start))) {
            start++;
        }

        int end = length - 1;
        while (end > start && contains(whitespaceChars, input.charAt(end))) {
            end--;
        }

        String trimmed = input.substring(start, end + 1);
        int indent = input.codePointCount(0, start);
        return new SimpleEntry<>(trimmed, indent);
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

    private static boolean contains(char[] characters, char c) {
        for (Character candidate : characters) {
            if (candidate == c) {
                return true;
            }
        }
        return false;
    }

}
