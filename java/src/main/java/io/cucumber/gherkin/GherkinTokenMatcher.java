package io.cucumber.gherkin;

import java.util.List;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import io.cucumber.gherkin.Parser.TokenMatcher;
import io.cucumber.messages.types.StepKeywordType;

import static io.cucumber.gherkin.GherkinLanguageConstants.COMMENT_PREFIX;
import static io.cucumber.gherkin.GherkinLanguageConstants.DOCSTRING_ALTERNATIVE_SEPARATOR;
import static io.cucumber.gherkin.GherkinLanguageConstants.DOCSTRING_SEPARATOR;
import static io.cucumber.gherkin.GherkinLanguageConstants.TABLE_CELL_SEPARATOR;
import static io.cucumber.gherkin.GherkinLanguageConstants.TAG_PREFIX;
import static io.cucumber.gherkin.GherkinLanguageConstants.TITLE_KEYWORD_SEPARATOR;
import static io.cucumber.gherkin.Locations.COLUMN_OFFSET;
import static io.cucumber.gherkin.Locations.atColumn;
import static io.cucumber.gherkin.Parser.TokenType;

class GherkinTokenMatcher implements TokenMatcher {

    private static final Pattern LANGUAGE_PATTERN = Pattern.compile("^#\\s*language\\s*:\\s*([a-zA-Z\\-_]+)\\s*$");
    private final GherkinDialectProvider dialectProvider;
    private GherkinDialect currentDialect;
    private String activeDocStringSeparator = null;
    private int indentToRemove = 0;

    GherkinTokenMatcher(GherkinDialectProvider dialectProvider) {
        this.dialectProvider = dialectProvider;
        reset();
    }

    GherkinTokenMatcher() {
        this(new GherkinDialectProvider());
    }

    GherkinTokenMatcher(String defaultDialectName) {
        this(new GherkinDialectProvider(defaultDialectName));
    }

    @Override
    public void reset() {
        activeDocStringSeparator = null;
        indentToRemove = 0;
        currentDialect = dialectProvider.getDefaultDialect();
    }

    private GherkinDialect getCurrentDialect() {
        return currentDialect;
    }

    private void setTokenMatched(Token token, TokenType matchedType, String text, String keyword, Integer indent, StepKeywordType keywordType, List<GherkinLineSpan> items) {
        token.matchedType = matchedType;
        token.matchedKeyword = keyword;
        token.keywordType = keywordType;
        token.matchedText = text;
        token.matchedItems = items;
        token.matchedGherkinDialect = getCurrentDialect();
        token.matchedIndent = indent != null ? indent : (token.isEOF() ? 0 : token.line.getIndent());
        token.location = atColumn(token.location, token.matchedIndent + COLUMN_OFFSET);
    }

    @Override
    public boolean match_EOF(Token token) {
        if (token.isEOF()) {
            setTokenMatched(token, TokenType.EOF, null, null, null, null, null);
            return true;
        }
        return false;
    }

    @Override
    public boolean match_Other(Token token) {
        String text = removeDocStringIndent(token);
        setTokenMatched(token, TokenType.Other, unescapeDocString(text), null, 0, null, null);
        return true;
    }

    @Override
    public boolean match_Empty(Token token) {
        if (token.line.isEmpty()) {
            setTokenMatched(token, TokenType.Empty, null, null, null, null, null);
            return true;
        }
        return false;
    }

    @Override
    public boolean match_Comment(Token token) {
        if (token.line.startsWith(COMMENT_PREFIX)) {
            String text = token.line.getRawText();
            setTokenMatched(token, TokenType.Comment, text, null, 0, null, null);
            return true;
        }
        return false;
    }

    @Override
    public boolean match_Language(Token token) {
        Matcher matcher = LANGUAGE_PATTERN.matcher(token.line.getText());
        if (matcher.matches()) {
            String language = matcher.group(1);
            setTokenMatched(token, TokenType.Language, language, null, null, null, null);

            currentDialect = dialectProvider.getDialect(language)
                    .orElseThrow(() -> new ParserException.NoSuchLanguageException(language, token.location));
            return true;
        }
        return false;
    }

    @Override
    public boolean match_TagLine(Token token) {
        if (token.line.startsWith(TAG_PREFIX)) {
            setTokenMatched(token, TokenType.TagLine, null, null, null, null, token.line.parseTags());
            return true;
        }
        return false;
    }

    @Override
    public boolean match_FeatureLine(Token token) {
        return matchTitleLine(token, TokenType.FeatureLine, currentDialect.getFeatureKeywords());
    }

    @Override
    public boolean match_RuleLine(Token token) {
        return matchTitleLine(token, TokenType.RuleLine, currentDialect.getRuleKeywords());
    }

    @Override
    public boolean match_BackgroundLine(Token token) {
        return matchTitleLine(token, TokenType.BackgroundLine, currentDialect.getBackgroundKeywords());
    }

    @Override
    public boolean match_ScenarioLine(Token token) {
        return matchTitleLine(token, TokenType.ScenarioLine, currentDialect.getScenarioKeywords()) ||
                matchTitleLine(token, TokenType.ScenarioLine, currentDialect.getScenarioOutlineKeywords());
    }

    @Override
    public boolean match_ExamplesLine(Token token) {
        return matchTitleLine(token, TokenType.ExamplesLine, currentDialect.getExamplesKeywords());
    }

    private boolean matchTitleLine(Token token, TokenType tokenType, List<String> keywords) {
        for (String keyword : keywords) {
            if (token.line.startsWithTitleKeyword(keyword)) {
                String title = token.line.substringTrimmed(keyword.length() + TITLE_KEYWORD_SEPARATOR.length());
                setTokenMatched(token, tokenType, title, keyword, null, null, null);
                return true;
            }
        }
        return false;
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
        if (token.line.startsWith(separator)) {
            String mediaType = null;
            if (isOpen) {
                mediaType = token.line.substringTrimmed(separator.length());
                activeDocStringSeparator = separator;
                indentToRemove = token.line.getIndent();
            } else {
                activeDocStringSeparator = null;
                indentToRemove = 0;
            }

            setTokenMatched(token, TokenType.DocStringSeparator, mediaType, separator, null, null, null);
            return true;
        }
        return false;
    }

    @Override
    public boolean match_StepLine(Token token) {
        List<String> keywords = currentDialect.getStepKeywords();
        for (String keyword : keywords) {
            if (token.line.startsWith(keyword)) {
                String stepText = token.line.substringTrimmed(keyword.length());
                StepKeywordType keywordType = getKeywordType(keyword);
                setTokenMatched(token, TokenType.StepLine, stepText, keyword, null, keywordType, null);
                return true;
            }
        }
        return false;
    }

    private StepKeywordType getKeywordType(String stepKeyword) {
        Set<StepKeywordType> keywordTypes = currentDialect.getStepKeywordTypesSet(stepKeyword);
        if (keywordTypes.size() == 1) {
            return keywordTypes.iterator().next();
        }
        return StepKeywordType.UNKNOWN;
    }

    @Override
    public boolean match_TableRow(Token token) {
        if (token.line.startsWith(TABLE_CELL_SEPARATOR)) {
            setTokenMatched(token, TokenType.TableRow, null, null, null, null, token.line.parseTableCells());
            return true;
        }
        return false;
    }

    private String removeDocStringIndent(Token token) {
        if (activeDocStringSeparator == null) {
            return token.line.getRawText();
        }
        if (indentToRemove > token.line.getIndent()) {
            // BUG: Removes trailing whitespace!
            return token.line.getText();
        }
        // Note: Indent to remove is in codePoints while getRawTextSubstring counts chars.
        // This is okay because in this context all codepoints are one byte wide. 
        return token.line.getRawTextSubstring(indentToRemove);
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
