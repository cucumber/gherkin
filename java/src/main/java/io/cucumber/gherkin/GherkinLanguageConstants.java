package io.cucumber.gherkin;

interface GherkinLanguageConstants {
    char TAG_PREFIX_CHAR = '@';
    String TAG_PREFIX = "" + TAG_PREFIX_CHAR;
    char COMMENT_PREFIX_CHAR = '#';
    String COMMENT_PREFIX = "" + COMMENT_PREFIX_CHAR;
    String TITLE_KEYWORD_SEPARATOR = ":";
    String TABLE_CELL_SEPARATOR = "|";
    String DOCSTRING_SEPARATOR = "\"\"\"";
    String DOCSTRING_ALTERNATIVE_SEPARATOR = "```";
}
