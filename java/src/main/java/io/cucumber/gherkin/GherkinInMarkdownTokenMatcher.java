package io.cucumber.gherkin;

import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.List;
import java.util.stream.Collectors;
import io.cucumber.messages.types.StepKeywordType;
import java.util.ArrayList;

import static io.cucumber.gherkin.Parser.TokenType;
import static io.cucumber.gherkin.Parser.ITokenMatcher;
import static io.cucumber.gherkin.StringUtils.ltrim;

class GherkinInMarkdownTokenMatcher implements ITokenMatcher {
    private enum KeywordPrefix {
        BULLET("^(\\s*[*+-]\\s+)"),
        HEADER("^(#{1,6}\\s)");

        private final String pattern;

        KeywordPrefix(String pattern) {
            this.pattern = pattern;
        }

        public String getPattern() {
            return pattern;
        }
    }

    private final GherkinDialectProvider dialectProvider;
    private GherkinDialect currentDialect;
    private int indentToRemove = 0;
    private final Pattern TABLE_ROW_PATTERN = Pattern.compile("^\\s{2,5}\\|.*\\S.*\\|$");
    private static final Pattern LANGUAGE_PATTERN = Pattern.compile("^\\s*#\\s*language\\s*:\\s*([a-zA-Z\\-]+)\\s*$");
    private static final String DEFAULT_DOC_STRING_SEPARATOR = "^\\s*(```[`]*)\\s*";
    private String activeDocStringSeparator = DEFAULT_DOC_STRING_SEPARATOR;
    private boolean matchedFeatureLine = false;

    public GherkinInMarkdownTokenMatcher(GherkinDialectProvider dialectProvider) {
        this.dialectProvider = dialectProvider;
        reset();
    }

    public GherkinInMarkdownTokenMatcher() {
        this(new GherkinDialectProvider());
    }

    public GherkinInMarkdownTokenMatcher(String defaultDialectName) {
        this(new GherkinDialectProvider(defaultDialectName));
    }

    private GherkinDialect getCurrentDialect() {
        return currentDialect;
    }

    public boolean match_EOF(Token token) {
        if (token.isEOF()) {
            setTokenMatched(token, TokenType.EOF, null, null, null, null, null);
            return true;
        }
        return false;
    }

    @Override
    public boolean match_FeatureLine(Token token) {

        if (token.line == null || token.line.isEmpty())
            return false;

        // First try to match "# Feature: blah"
        boolean result = matchTitleLine(token, TokenType.FeatureLine, currentDialect.getFeatureKeywords());

        // If we didn't match "# Feature: blah", we still match this line as a
        // FeatureLine
        if (!result && !matchedFeatureLine) {
            setTokenMatched(token, TokenType.FeatureLine, ltrim(token.line.getLineText(0)),
                    currentDialect.getFeatureKeywords().get(0), null, null, null);
            result = true;
        }
        if (result) {
            // Remember that we've matched a feature line
            matchedFeatureLine = result;
        }

        return result;

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
    public boolean match_ExamplesLine(Token token) {
        return matchTitleLine(token, TokenType.ExamplesLine, currentDialect.getExamplesKeywords());
    }

    @Override
    public boolean match_ScenarioLine(Token token) {
        return matchTitleLine(token, TokenType.ScenarioLine, currentDialect.getScenarioKeywords()) ||
                matchTitleLine(token, TokenType.ScenarioLine, currentDialect.getScenarioOutlineKeywords());
    }

    private boolean matchTitleLine(Token token, TokenType tokenType, List<String> keywords) {
        String pattern = KeywordPrefix.HEADER.getPattern() + "(" +
                String.join("|", keywords) + "):(\\s)?(.*)";
        Pattern headerPattern = Pattern.compile(pattern);
        Matcher matcher = headerPattern.matcher(token.line.getLineText(-1));
        if (matcher.find()) {
            String keyword = matcher.group(2);
            String text = matcher.groupCount() == 4 ? matcher.group(4).trim() : "";
            int indent = matcher.group(1).length();
            setTokenMatched(token, tokenType, text, keyword, indent, null, null);
            return true;
        }
        return false;
    }

    @Override
    public boolean match_StepLine(Token token) {

        // Combine all step keywords
        List<String> stepKeywords = currentDialect.getStepKeywords();

        // Build pattern: bullet point followed by step keyword
        String pattern = KeywordPrefix.BULLET.getPattern() +
                "(" +
                // stream the step keywords and quote them then join them with |
                stepKeywords.stream().map(keyword -> Pattern.quote(keyword)).collect(Collectors.joining("|")) +
                ")" +
                "(.*)";

        Pattern stepPattern = Pattern.compile(pattern);
        Matcher matcher = stepPattern.matcher(token.line.getLineText(0));

        if (matcher.find()) {
            String keyword = matcher.group(2); // The step keyword
            List<StepKeywordType> keywordTypes = currentDialect.getStepKeywordTypes(keyword);
            StepKeywordType keywordType = (keywordTypes.size() > 1) ? StepKeywordType.UNKNOWN : keywordTypes.get(0);
            String text = matcher.group(3).trim(); // The step text
            int indent = matcher.group(1).length(); // Length of bullet + whitespace

            if (!text.isEmpty()) {
                setTokenMatched(token, TokenType.StepLine, text, keyword, indent, keywordType, null);
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean match_TableRow(Token token) {
        Matcher matcher = TABLE_ROW_PATTERN.matcher(token.line.getLineText(0));
        if (matcher.find()) {
            List<GherkinLineSpan> tableCells = token.line.getTableCells();
            if (isGfmTableSeparator(tableCells))
                return false;

            setTokenMatched(token, TokenType.TableRow, null, null, null, null, tableCells);
            return true;
        }
        return false;
    }

    @Override
    public boolean match_Empty(Token token) {
        if (token.line == null)
            return false;
        if (token.line.isEmpty() // ){
                ||
                (!match_TagLine(token) &&
                        !match_ScenarioLine(token) &&
                        !match_BackgroundLine(token) &&
                        !match_ExamplesLine(token) &&
                        !match_RuleLine(token) &&
                        !match_TableRow(token) &&
                        !match_Comment(token) &&
                        !match_Language(token) &&
                        !match_DocStringSeparator(token) &&
                        !match_EOF(token) &&
                        !match_StepLine(token)
                        && !match_FeatureLine(token))) {
            setTokenMatched(token, TokenType.Empty, null, null, 0, null, null);
            return true;
        }
        Matcher matcher = TABLE_ROW_PATTERN.matcher(token.line.getLineText(0));
        if (matcher.find()) {
            List<GherkinLineSpan> tableCells = token.line.getTableCells();
            if (isGfmTableSeparator(tableCells)) {
                setTokenMatched(token, TokenType.Empty, null, null, null, null, null);
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean match_TagLine(Token token) {
        if (token.line == null)
            return false;

        String lineText = token.line.getLineText(-1);
        List<GherkinLineSpan> items = new ArrayList<>();

        // Pattern for backtick-wrapped tags
        Pattern tagPattern = Pattern.compile("`(@[^\\s`]+)`");
        Matcher matcher = tagPattern.matcher(lineText);

        boolean found = false;
        while (matcher.find()) {
            found = true;
            String tag = matcher.group(1); // Group 1 is the actual tag without backticks
            int column = matcher.start(1) + 1; // +1 for 1-based column indexing
            items.add(new GherkinLineSpan(column, tag));
        }

        if (found) {
            setTokenMatched(token, TokenType.TagLine, null, null, null, null, items);
            return true;
        }

        return false;
    }

    private void setTokenMatched(Token token, TokenType matchedType, String text, String keyword, Integer indent,
            StepKeywordType keywordType, List<GherkinLineSpan> items) {
        token.matchedType = matchedType;
        token.matchedKeyword = keyword;
        token.matchedText = text;
        token.keywordType = keywordType;
        token.matchedIndent = indent != null ? indent : token.line == null ? 0 : token.line.indent();
        token.matchedItems = items;
        token.matchedGherkinDialect = getCurrentDialect();
        token.location = new Location(token.location.getLine(), token.matchedIndent + 1);
        ;
    }

    @Override
    public boolean match_DocStringSeparator(Token token) {
        if (token.line == null)
            return false;
        Pattern docStringSeparatorPattern = Pattern.compile(activeDocStringSeparator);
        String lineText = token.line.getLineText(0);
        Matcher docStringSeparatorPatternMatcher = docStringSeparatorPattern.matcher(lineText);

        if (docStringSeparatorPatternMatcher.matches()) {
            String newSeparator = docStringSeparatorPatternMatcher.group(1);
            String mediaType = null;
            if (activeDocStringSeparator.equals(DEFAULT_DOC_STRING_SEPARATOR)) {
                activeDocStringSeparator = "^\\s*(" + newSeparator + ")$";
                indentToRemove = token.line.indent();
                mediaType = token.line.getRestTrimmed(newSeparator.length());
            } else {
                activeDocStringSeparator = DEFAULT_DOC_STRING_SEPARATOR;
            }
            setTokenMatched(token, TokenType.DocStringSeparator, mediaType, newSeparator, null, null, null);
            return true;

        }
        return false;

    }

    @Override
    public boolean match_Comment(Token token) {
        if (token.line == null)
            return false;
        if (token.line.startsWith("|")) {
            List<GherkinLineSpan> tableCells = token.line.getTableCells();
            if (isGfmTableSeparator(tableCells)) {
                setTokenMatched(token, TokenType.Comment, token.line.getLineText(0), null, 0, null, null);
                return true;
            }
        }
        return false;
    }

    private boolean isGfmTableSeparator(List<GherkinLineSpan> tableCells) {
        if (tableCells == null || tableCells.isEmpty())
            return false;

        // Check if all cells match the GFM separator pattern: :?-+:?
        // Examples of valid separators: ---, :---, ---:, :---:
        Pattern separatorPattern = Pattern.compile("^\\s*:?-+:?\\s*$");

        return tableCells.stream()
                .map(cell -> cell.text)
                .allMatch(text -> separatorPattern.matcher(text.trim()).matches());
    }

    @Override
    public boolean match_Other(Token token) {
        if (token.line == null)
            return false;

        String text = token.line.getLineText(indentToRemove); // take the entire line, except removing DocString indents
        setTokenMatched(token, TokenType.Other, text, null, 0, null, null);
        return true;
    }

    @Override
    public boolean match_Language(Token token) {
        if (token.line == null)
            return false;

        Matcher matcher = LANGUAGE_PATTERN.matcher(token.line.getLineText(0));
        if (matcher.matches()) {
            String language = matcher.group(1);
            setTokenMatched(token, TokenType.Language, language, null, null, null, null);

            // Update dialect
            GherkinDialectProvider dialectProvider = new GherkinDialectProvider(language);
            currentDialect = dialectProvider.getDialect(language)
                    .orElseThrow(() -> new ParserException.NoSuchLanguageException(language, token.location));

            return true;
        }
        return false;
    }

    @Override
    public void reset() {
        activeDocStringSeparator = DEFAULT_DOC_STRING_SEPARATOR;
        indentToRemove = 0;
        currentDialect = dialectProvider.getDefaultDialect();
    }

}