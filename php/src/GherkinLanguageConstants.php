<?php

namespace Cucumber\Gherkin;

interface GherkinLanguageConstants
{
    public const string TAG_PREFIX = "@";
    public const string COMMENT_PREFIX = "#";
    public const string TITLE_KEYWORD_SEPARATOR = ":";
    public const string TABLE_CELL_SEPARATOR = "|";
    public const string DOCSTRING_SEPARATOR = "\"\"\"";
    public const string DOCSTRING_ALTERNATIVE_SEPARATOR = "```";
}
