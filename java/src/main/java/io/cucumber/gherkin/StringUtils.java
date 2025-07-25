package io.cucumber.gherkin;


import java.util.AbstractMap.SimpleEntry;
import java.util.Map.Entry;
import java.util.function.Predicate;

import static io.cucumber.gherkin.GherkinLanguageConstants.COMMENT_PREFIX_CHAR;

final class StringUtils {

    static boolean isWhiteSpace(char c) {
        return isCharacterTypeSpace(c) || isDirectionalitySpace(c);
    }

    private static boolean isCharacterTypeSpace(char c) {
        return (((
                (1 << Character.SPACE_SEPARATOR)
//                        | (1 << Character.LINE_SEPARATOR)
//                        | (1 << Character.PARAGRAPH_SEPARATOR)
        ) >> Character.getType(c)) & 1) != 0;
    }

    private static boolean isDirectionalitySpace(char c) {
        return (
                (((1 << Character.DIRECTIONALITY_WHITESPACE)  
                | (1 << Character.DIRECTIONALITY_PARAGRAPH_SEPARATOR) 
                | (1 << Character.DIRECTIONALITY_SEGMENT_SEPARATOR) 
        ) >> Character.getDirectionality(c)) & 1) != 0;
    }

    private static final Predicate<Character> WHITESPACE_CHARS_EXTENDED = StringUtils::isWhiteSpace;
    private static final Predicate<Character> WHITESPACE_CHARS_EXTENDED_KEEP_NEW_LINE = c -> c != '\n' && isWhiteSpace(c);

    static String rtrim(String s) {
        if (s.isEmpty()) {
            return s;
        }

        int length = s.length();

        int end = length - 1;
        while (end >= 0) {
            if (!isWhiteSpace(s.charAt(end))) break;
            end--;
        }

        return s.substring(0, end + 1);
    }

    static Entry<String, Integer> trimAndIndentKeepNewLines(String input) {
        return trimAndIndent(input, WHITESPACE_CHARS_EXTENDED_KEEP_NEW_LINE);
    }

    static Entry<String, Integer> trimAndIndent(String input) {
        return trimAndIndent(input, WHITESPACE_CHARS_EXTENDED);
    }

    private static Entry<String, Integer> trimAndIndent(String input, Predicate<Character> isSpace) {
        if (input.isEmpty()) {
            return new SimpleEntry<>("", 0);
        }

        int start = findFirstIndexNotIn(input, input.length(), isSpace);
        int end = findLastIndexNotIn(input, start, isSpace);

        String trimmed = input.substring(start, end);
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
                && !(Character.isSpaceChar(input.charAt(start)) 
                && input.charAt(start + 1) == COMMENT_PREFIX_CHAR)
        ) {
            start++;
        }
        return input.substring(0, start < length - 1 ? start : start + 1);
    }

    static boolean containsWhiteSpace(String input) {
        return findFirstIndexIn(input, WHITESPACE_CHARS_EXTENDED) != -1;
    }

    private static int findFirstIndexNotIn(String input, int endIndex, Predicate<Character> isSpace) {
        int start = 0;
        while (start < endIndex && isSpace.test(input.charAt(start))) {
            start++;
        }
        return start;
    }
    
    private static int findLastIndexNotIn(String input, int beginIndex, Predicate<Character> isSpace) {
        int end = input.length();
        while (end > beginIndex && isSpace.test(input.charAt(end - 1))) {
            end--;
        }
        return end;
    }

    private static int findFirstIndexIn(String input, Predicate<Character> isSpace) {
        int length = input.length();
        for (int i = 0; i < length; i++) {
            if (isSpace.test(input.charAt(i))) {
                return i;
            }
        }
        return -1;
    }

}
