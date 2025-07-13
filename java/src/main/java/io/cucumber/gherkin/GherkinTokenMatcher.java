package io.cucumber.gherkin;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import io.cucumber.gherkin.Parser.TokenMatcher;
import io.cucumber.messages.types.StepKeywordType;

import static io.cucumber.gherkin.GherkinLanguageConstants.COMMENT_PREFIX_CHAR;
import static io.cucumber.gherkin.GherkinLanguageConstants.DOCSTRING_ALTERNATIVE_SEPARATOR;
import static io.cucumber.gherkin.GherkinLanguageConstants.DOCSTRING_SEPARATOR;
import static io.cucumber.gherkin.GherkinLanguageConstants.TABLE_CELL_SEPARATOR;
import static io.cucumber.gherkin.GherkinLanguageConstants.TAG_PREFIX_CHAR;
import static io.cucumber.gherkin.GherkinLanguageConstants.TITLE_KEYWORD_SEPARATOR_LENGTH;
import static io.cucumber.gherkin.Locations.COLUMN_OFFSET;
import static io.cucumber.gherkin.Locations.atColumn;
import static io.cucumber.gherkin.Parser.TokenType;

class GherkinTokenMatcher implements TokenMatcher {

    private static final Pattern LANGUAGE_PATTERN = Pattern.compile("^#\\s*language\\s*:\\s*([a-zA-Z\\-_]+)\\s*$");
    private final GherkinDialectProvider dialectProvider;
    private GherkinDialect currentDialect;
    private String activeDocStringSeparator = null;
    private int indentToRemove = 0;
    private StepLineElem stepLineElem1;
    private StepLineElem stepLineElem2;
    private StepLineElem stepLineElem3;
    private StepLineElem stepLineElem4;
    private StepLineElem stepLineElem0;
    private StepLineElem stepLineElem5;
    private List<StepLineElem> remainingStepLineElems;

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
        prepareStepLineLoopUnrolling();
    }

    private void setTokenMatched(Token token, TokenType matchedType, String text, String keyword, int indent, StepKeywordType keywordType, List<GherkinLineSpan> items) {
        token.matchedType = matchedType;
        token.matchedKeyword = keyword;
        token.keywordType = keywordType;
        token.matchedText = text;
        token.matchedItems = items;
        token.matchedGherkinDialect = currentDialect;
        token.matchedIndent = indent;
        token.location = atColumn(token.location, token.matchedIndent + COLUMN_OFFSET);
    }

    @Override
    public boolean match_EOF(Token token) {
        if (token.isEOF()) {
            setTokenMatched(token, TokenType.EOF, null, null, 0, null, null);
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
            setTokenMatched(token, TokenType.Empty, null, null, token.line.getIndent(), null, null);
            return true;
        }
        return false;
    }

    @Override
    public boolean match_Comment(Token token) {
        if (token.line.startsWith(COMMENT_PREFIX_CHAR)) {
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
            setTokenMatched(token, TokenType.Language, language, null, token.line.getIndent(), null, null);

            currentDialect = dialectProvider.getDialect(language)
                    .orElseThrow(() -> new ParserException.NoSuchLanguageException(language, token.location));
            return true;
        }
        return false;
    }

    @Override
    public boolean match_TagLine(Token token) {
        if (token.line.startsWith(TAG_PREFIX_CHAR)) {
            setTokenMatched(token, TokenType.TagLine, null, null, token.line.getIndent(), null, token.line.parseTags());
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
                String title = token.line.substringTrimmed(keyword.length() + TITLE_KEYWORD_SEPARATOR_LENGTH);
                setTokenMatched(token, tokenType, title, keyword, token.line.getIndent(), null, null);
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

            setTokenMatched(token, TokenType.DocStringSeparator, mediaType, separator, token.line.getIndent(), null, null);
            return true;
        }
        return false;
    }

    private void prepareStepLineLoopUnrolling() {
        // Loop unrolling the step line keyword matching
        // is 2x faster than using a loop.
        // There are at least 6 keywords (Given, When, Then,
        // And, But, *) in the English dialect, but some dialects
        // may have more keywords. Thus, we unroll the first 6
        // keywords, and process the other dynamically.
        List<String> keywords = currentDialect.getStepKeywords();
        stepLineElem0 = new StepLineElem(keywords.get(0), currentDialect.getStepKeywordType(keywords.get(0)));
        stepLineElem1 = new StepLineElem(keywords.get(1), currentDialect.getStepKeywordType(keywords.get(1)));
        stepLineElem2 = new StepLineElem(keywords.get(2), currentDialect.getStepKeywordType(keywords.get(2)));
        stepLineElem3 = new StepLineElem(keywords.get(3), currentDialect.getStepKeywordType(keywords.get(3)));
        stepLineElem4 = new StepLineElem(keywords.get(4), currentDialect.getStepKeywordType(keywords.get(4)));
        stepLineElem5 = new StepLineElem(keywords.get(5), currentDialect.getStepKeywordType(keywords.get(5)));
        int keywordCount = keywords.size();
        if (keywordCount > 6) {
            remainingStepLineElems = new ArrayList<>(keywordCount - 6);
            for (int i = 6; i < keywordCount; i++) {
                remainingStepLineElems.add(new StepLineElem(keywords.get(i), currentDialect.getStepKeywordType(keywords.get(i))));
            }
        } else {
            remainingStepLineElems = Collections.emptyList();
        }

    }

    @Override
    public boolean match_StepLine(Token token) {
        if (token.line.startsWith(stepLineElem0.keyword)) {
            matchStepKeyword(token, stepLineElem0);
            return true;
        }
        if (token.line.startsWith(stepLineElem1.keyword)) {
            matchStepKeyword(token, stepLineElem1);
            return true;
        }
        if (token.line.startsWith(stepLineElem2.keyword)) {
            matchStepKeyword(token, stepLineElem2);
            return true;
        }
        if (token.line.startsWith(stepLineElem3.keyword)) {
            matchStepKeyword(token, stepLineElem3);
            return true;
        }
        if (token.line.startsWith(stepLineElem4.keyword)) {
            matchStepKeyword(token, stepLineElem4);
            return true;
        }
        if (token.line.startsWith(stepLineElem5.keyword)) {
            matchStepKeyword(token, stepLineElem5);
            return true;
        }
        for (StepLineElem stepLineElem : remainingStepLineElems) {
            if (token.line.startsWith(stepLineElem.keyword)) {
                matchStepKeyword(token, stepLineElem);
                return true;
            }
        }
        return false;
    }

    private void matchStepKeyword(Token token, StepLineElem stepLineElem) {
        String stepText = token.line.substringTrimmed(stepLineElem.keywordLength);
        StepKeywordType keywordType = stepLineElem.keywordType;
        setTokenMatched(token, TokenType.StepLine, stepText, stepLineElem.keyword, token.line.getIndent(), keywordType, null);
    }

    @Override
    public boolean match_TableRow(Token token) {
        if (token.line.startsWith(TABLE_CELL_SEPARATOR)) {
            setTokenMatched(token, TokenType.TableRow, null, null, token.line.getIndent(), null, token.line.parseTableCells());
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

    public static class StepLineElem {
        public final int keywordLength;
        public final String keyword;
        public final StepKeywordType keywordType;

        public StepLineElem(String keyword, StepKeywordType keywordType) {
            this.keywordLength = keyword.length();
            this.keyword = keyword;
            this.keywordType = keywordType;
        }
    }
}
