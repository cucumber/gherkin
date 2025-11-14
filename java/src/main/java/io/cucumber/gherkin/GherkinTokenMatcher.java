package io.cucumber.gherkin;

import io.cucumber.gherkin.Parser.TokenMatcher;
import io.cucumber.messages.types.Location;
import io.cucumber.messages.types.StepKeywordType;
import org.jspecify.annotations.Nullable;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static io.cucumber.gherkin.Constants.COMMENT_PREFIX_CHAR;
import static io.cucumber.gherkin.Constants.DEFAULT_LANGUAGE;
import static io.cucumber.gherkin.Constants.DOCSTRING_ALTERNATIVE_SEPARATOR;
import static io.cucumber.gherkin.Constants.DOCSTRING_SEPARATOR;
import static io.cucumber.gherkin.Constants.TABLE_CELL_SEPARATOR;
import static io.cucumber.gherkin.Constants.TAG_PREFIX_CHAR;
import static io.cucumber.gherkin.Locations.COLUMN_OFFSET;
import static io.cucumber.gherkin.Locations.atColumn;
import static io.cucumber.gherkin.Parser.TokenType;

final class GherkinTokenMatcher implements TokenMatcher {

    private static final Pattern LANGUAGE_PATTERN = Pattern.compile("^#\\s*language\\s*:\\s*([a-zA-Z\\-_]+)\\s*$");
    private final String defaultLanguage;
    // Expect at most two languages, the default language and one other
    private final Map<String, KeywordMatcher> activeKeywordMatchers = new HashMap<>(2);
    private @Nullable String currentLanguage;
    private KeywordMatcher currentKeywordMatcher;
    private @Nullable String activeDocStringSeparator = null;
    private int indentToRemove = 0;

    GherkinTokenMatcher(String defaultLanguage) {
        this.defaultLanguage = defaultLanguage;
        this.currentKeywordMatcher = requireKeywordMatcher(defaultLanguage, new Location(0, 0));
        reset();
    }

    GherkinTokenMatcher() {
        this(DEFAULT_LANGUAGE);
    }

    @Override
    public void reset() {
        // TODO performance: reset() is called once in the constructor and once for each file (Parser.parse()). 
        // It could be called only once, but there is no measurable impact with the profiler
        activeDocStringSeparator = null;
        indentToRemove = 0;
        setLanguageMatched(defaultLanguage, null);
    }

    private void setLanguageMatched(String language, @Nullable Location location) {
        if (language.equals(currentLanguage)) {
            return;
        }
        KeywordMatcher keywordMatcher = requireKeywordMatcher(language, location);
        currentLanguage = language;
        currentKeywordMatcher = keywordMatcher;
    }

    private KeywordMatcher requireKeywordMatcher(String language, @Nullable Location location) {
        KeywordMatcher keywordMatcher = activeKeywordMatchers.computeIfAbsent(language, KeywordMatchers::of);
        if (keywordMatcher == null) {
            throw new ParserException.NoSuchLanguageException(language, location);
        }
        return keywordMatcher;
    }

    private void setTokenMatched(Token token, TokenType matchedType, @Nullable String text, @Nullable String keyword, int indent, @Nullable StepKeywordType keywordType, @Nullable List<LineSpan> items) {
        token.matchedType = matchedType;
        token.matchedKeyword = keyword;
        token.keywordType = keywordType;
        token.matchedText = text;
        token.matchedItems = items;
        token.matchedLanguage = currentLanguage;
        token.matchedIndent = indent;
        token.location = atColumn(token.location, token.matchedIndent + COLUMN_OFFSET);
    }

    @Override
    public boolean match_EOF(Token token) {
        if (!token.isEOF()) {
            return false;
        }
        setTokenMatched(token, TokenType.EOF, null, null, 0, null, null);
        return true;
    }

    @Override
    public boolean match_Other(Token token) {
        String text = removeDocStringIndent(token);
        setTokenMatched(token, TokenType.Other, unescapeDocString(text), null, 0, null, null);
        return true;
    }

    @Override
    public boolean match_Empty(Token token) {
        if (!token.getRequiredLine().isEmpty()) {
            return false;
        }
        setTokenMatched(token, TokenType.Empty, null, null, 0, null, null);
        return true;
    }

    @Override
    public boolean match_Comment(Token token) {
        Line line = token.getRequiredLine();
        if (!line.startsWith(COMMENT_PREFIX_CHAR)) {
            return false;
        }
        String text = line.getRawText();
        setTokenMatched(token, TokenType.Comment, text, null, 0, null, null);
        return true;
    }

    @Override
    public boolean match_Language(Token token) {
        Line line = token.getRequiredLine();
        if (!line.startsWith(COMMENT_PREFIX_CHAR)) {
            return false;
        }
        Matcher matcher = LANGUAGE_PATTERN.matcher(line.getText());
        if (!matcher.matches()) {
            return false;
        }
        String language = matcher.group(1);
        setTokenMatched(token, TokenType.Language, language, null, line.getIndent(), null, null);
        setLanguageMatched(language, token.location);
        return true;
    }

    @Override
    public boolean match_TagLine(Token token) {
        Line line = token.getRequiredLine();
        if (!line.startsWith(TAG_PREFIX_CHAR)) {
            return false;
        }
        List<LineSpan> tags = TagLine.parse(line.getIndent(), line.getText(), token.location);
        setTokenMatched(token, TokenType.TagLine, null, null, line.getIndent(), null, tags);
        return true;
    }

    @Override
    public boolean match_FeatureLine(Token token) {
        return matchTitleLine(token, TokenType.FeatureLine, currentKeywordMatcher::matchFeatureKeyword);
    }

    @Override
    public boolean match_RuleLine(Token token) {
        return matchTitleLine(token, TokenType.RuleLine, currentKeywordMatcher::matchRuleKeyword);
    }

    @Override
    public boolean match_BackgroundLine(Token token) {
        return matchTitleLine(token, TokenType.BackgroundLine, currentKeywordMatcher::matchBackgroundKeyword);
    }

    @Override
    public boolean match_ScenarioLine(Token token) {
        return matchTitleLine(token, TokenType.ScenarioLine, currentKeywordMatcher::matchScenarioKeyword);
    }

    @Override
    public boolean match_ExamplesLine(Token token) {
        return matchTitleLine(token, TokenType.ExamplesLine, currentKeywordMatcher::matchExampleKeyword);
    }

    private boolean matchTitleLine(Token token, TokenType tokenType, Function<Line, KeywordMatcher.@Nullable Match> matcher) {
        Line line = token.getRequiredLine();
        KeywordMatcher.Match match = matcher.apply(line);
        if (match == null) {
            return false;
        }
        String keyword = match.getKeyword();
        int keywordLength = match.getKeywordLength();
        String title = line.substringTrimmed(keywordLength);
        setTokenMatched(token, tokenType, title, keyword, line.getIndent(), null, null);
        return true;
    }

    @Override
    public boolean match_DocStringSeparator(Token token) {
        return activeDocStringSeparator == null
                // open
                ? match_DocStringSeparator(token, DOCSTRING_SEPARATOR, true) ||
                match_DocStringSeparator(token, DOCSTRING_ALTERNATIVE_SEPARATOR, true)
                // close
                : match_DocStringSeparator(token, activeDocStringSeparator, false);
    }

    private boolean match_DocStringSeparator(Token token, String separator, boolean isOpen) {
        Line line = token.getRequiredLine();
        if (!line.startsWith(separator)) {
            return false;
        }
        String mediaType = null;
        if (isOpen) {
            mediaType = line.substringTrimmed(separator.length());
            activeDocStringSeparator = separator;
            indentToRemove = line.getIndent();
        } else {
            activeDocStringSeparator = null;
            indentToRemove = 0;
        }

        setTokenMatched(token, TokenType.DocStringSeparator, mediaType, separator, line.getIndent(), null, null);
        return true;
    }

    @Override
    public boolean match_StepLine(Token token) {
        Line line = token.getRequiredLine();
        KeywordMatcher.StepMatch match = currentKeywordMatcher.matchStepKeyword(line);
        if (match == null) {
            return false;
        }
        String keyword = match.getKeyword();
        int keywordLength = match.getKeywordLength();
        StepKeywordType keywordType = match.getKeywordType();
        String stepText = line.substringTrimmed(keywordLength);
        setTokenMatched(token, TokenType.StepLine, stepText, keyword, line.getIndent(), keywordType, null);
        return true;
    }

    @Override
    public boolean match_TableRow(Token token) {
        Line line = token.getRequiredLine();
        if (!line.startsWith(TABLE_CELL_SEPARATOR)) {
            return false;
        }
        List<LineSpan> tableCells = TableRowLine.parse(line.getIndent(), line.getText());
        setTokenMatched(token, TokenType.TableRow, null, null, line.getIndent(), null, tableCells);
        return true;
    }

    private String removeDocStringIndent(Token token) {
        Line line = token.getRequiredLine();
        if (activeDocStringSeparator == null) {
            return line.getRawText();
        }
        if (indentToRemove > line.getIndent()) {
            // BUG: Removes trailing whitespace!
            return line.getText();
        }
        return line.getRawTextSubstring(indentToRemove);
    }

    private String unescapeDocString(String text) {
        if (DOCSTRING_SEPARATOR.equals(activeDocStringSeparator)) {
            return text.replace("\\\"\\\"\\\"", DOCSTRING_SEPARATOR);
        }

        if (DOCSTRING_ALTERNATIVE_SEPARATOR.equals(activeDocStringSeparator)) {
            return text.replace("\\`\\`\\`", DOCSTRING_ALTERNATIVE_SEPARATOR);
        }
        return text;
    }
}
