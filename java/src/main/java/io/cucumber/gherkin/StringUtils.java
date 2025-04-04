package io.cucumber.gherkin;


import java.util.AbstractMap.SimpleEntry;
import java.util.Map.Entry;

class StringUtils {

    private static final Character[] WHITESPACE_CHARS = new Character[]{' ', '\t', '\n', '\u000B', '\f', '\r', '\u0085', '\u00A0'};
    private static final Character[] WHITESPACE_CHARS_KEEP_NEW_LINES = new Character[]{' ', '\t', '\u000B', '\f', '\r', '\u0085', '\u00A0'};
    private static final Character[] WHITESPACE_CHARS_SIMPLE = new Character[]{' ', '\t', '\n', '\u000B', '\f', '\r'};

    static String rtrim(String s) {
        if (s.isEmpty()) {
            return s;
        }

        int length = s.length();

        int end = length - 1;
        while (end >= 0 && contains(WHITESPACE_CHARS, s.charAt(end))) {
            end--;
        }

        return s.substring(0, end + 1);
    }

    static Entry<String, Integer> trimAndIndentKeepNewLines(String input) {
        return trimAndIndent(input, WHITESPACE_CHARS_KEEP_NEW_LINES);
    }

    static Entry<String, Integer> trimAndIndent(String input) {
        return trimAndIndent(input, WHITESPACE_CHARS);
    }

    private static Entry<String, Integer> trimAndIndent(String input, Character[] whitespaceChars) {
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
        if (input == null || input.isEmpty()) {
            return input;
        }
        int start = 0;
        int length = input.length();

        while (start < length - 1 && !(contains(WHITESPACE_CHARS_SIMPLE, input.charAt(start)) &&
                input.charAt(start + 1) == '#')) {
            start++;
        }
        return input.substring(0, start < length - 1 ? start : start + 1);
    }

    private static boolean contains(Character[] whitespaceChars, char c) {
        for (Character whitespaceChar : whitespaceChars) {
            if (whitespaceChar == c) {
                return true;
            }
        }
        return false;
    }

}
