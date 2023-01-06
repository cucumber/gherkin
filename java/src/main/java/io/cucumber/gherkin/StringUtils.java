package io.cucumber.gherkin;

import java.util.regex.Pattern;

class StringUtils {

    private static final Pattern LTRIM = Pattern.compile("^[ \\t\\n\\x0B\\f\\r\\x85\\xA0]+");
    private static final Pattern LTRIM_KEEP_NEW_LINES = Pattern.compile("^[ \\t\\x0B\\f\\r\\x85\\xA0]+");
    private static final Pattern RTRIM_KEEP_NEW_LINES = Pattern.compile("[ \\t\\x0B\\f\\r\\x85\\xA0]+$");
    private static final Pattern RTRIM = Pattern.compile("[ \\t\\n\\x0B\\f\\r\\x85\\xA0]+$");
    private static final Pattern TRIM = Pattern.compile("^[ \\t\\n\\x0B\\f\\r\\x85\\xA0]+|[ \\t\\n\\x0B\\f\\r\\x85\\xA0]+$");

    static String ltrim(String s) {
        // https://stackoverflow.com/questions/1060570/why-is-non-breaking-space-not-a-whitespace-character-in-java
        return LTRIM.matcher(s).replaceAll("");
    }

    /**
     * Trims whitespace on the left-hand side up to the first 
     * non-whitespace character and exclude new lines from the 
     * usual definition of whitespace.
     */
    static String ltrimKeepNewLines(String s) {
        // https://stackoverflow.com/questions/1060570/why-is-non-breaking-space-not-a-whitespace-character-in-java
        return LTRIM_KEEP_NEW_LINES.matcher(s).replaceAll("");
    }

    /**
     * Trims whitespace on the right-hand side up to the first 
     * non-whitespace character and exclude new lines from the 
     * usual definition of whitespace.
     */
    static String rtrimKeepNewLines(String s) {
        // https://stackoverflow.com/questions/1060570/why-is-non-breaking-space-not-a-whitespace-character-in-java
        return RTRIM_KEEP_NEW_LINES.matcher(s).replaceAll("");
    }

    static String rtrim(String s) {
        return RTRIM.matcher(s).replaceAll("");
    }

    static String trim(String s) {
        return TRIM.matcher(s).replaceAll("");
    }

    static int symbolCount(String string) {
        // http://rosettacode.org/wiki/String_length#Java
        return string.codePointCount(0, string.length());
    }
}
