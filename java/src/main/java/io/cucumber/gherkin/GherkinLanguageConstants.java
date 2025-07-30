package io.cucumber.gherkin;

interface GherkinLanguageConstants {
    char TAG_PREFIX_CHAR = '@';
    char COMMENT_PREFIX_CHAR = '#';
    char TITLE_KEYWORD_SEPARATOR = ':';
    /**
     * Size of TITLE_KEYWORD_SEPARATOR = 1 char.
     */
    int TITLE_KEYWORD_SEPARATOR_LENGTH = 1;
    char TABLE_CELL_SEPARATOR = '|';
    String DOCSTRING_SEPARATOR = "\"\"\"";
    String DOCSTRING_ALTERNATIVE_SEPARATOR = "```";
    String DEFAULT_LANGUAGE = "en";
}
