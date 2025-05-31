package io.cucumber.gherkin;

interface GherkinLanguageConstants {
    char TAG_PREFIX_CHAR = '@';
    String TAG_PREFIX = "" + TAG_PREFIX_CHAR;
    char COMMENT_PREFIX_CHAR = '#';
    String COMMENT_PREFIX = "" + COMMENT_PREFIX_CHAR;
    char TITLE_KEYWORD_SEPARATOR = ':';
    char TABLE_CELL_SEPARATOR = '|';
    String DOCSTRING_SEPARATOR = "\"\"\"";
    String DOCSTRING_ALTERNATIVE_SEPARATOR = "```";
}
