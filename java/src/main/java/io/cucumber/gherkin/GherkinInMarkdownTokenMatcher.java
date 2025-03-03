package io.cucumber.gherkin;

import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.List;
import java.util.stream.Collectors;
import io.cucumber.messages.types.StepKeywordType;
import java.util.ArrayList;

import static io.cucumber.gherkin.Parser.TokenType;
import static io.cucumber.gherkin.Parser.ITokenMatcher;

class GherkinInMarkdownTokenMatcher implements ITokenMatcher{
    private enum KeywordPrefix {
        BULLET("^(\\s*[*+-]\\s)"),
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
    private final Pattern TABLE_ROW_PATTERN = Pattern.compile("^\\|.*\\S.*\\|$");
    private static final Pattern LANGUAGE_PATTERN = Pattern.compile("^\\s*#\\s*language\\s*:\\s*([a-zA-Z\\-]+)\\s*$");
    private boolean activeDocStringSeparator = false;

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
                String.join("|", keywords) + "):(\\s+)(.*)";
        Pattern headerPattern = Pattern.compile(pattern);
        Matcher matcher = headerPattern.matcher(token.line.getLineText(-1));
        if (matcher.find()) {
            String keyword = matcher.group(2);
            String text = matcher.group(4).trim();
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
            //stream the step keywords and quote them then join them with |
            stepKeywords.stream().map(keyword -> Pattern.quote(keyword)).collect(Collectors.joining("|")) + 
            ")" + 
            "(.*)"
        ;
        
        Pattern stepPattern = Pattern.compile(pattern);
        Matcher matcher = stepPattern.matcher(token.line.getLineText(-1));

        if (matcher.find()) {
            String keyword = matcher.group(2);  // The step keyword
            String text = matcher.group(3).trim();  // The step text
            int indent = matcher.group(1).length();  // Length of bullet + whitespace

            if (!text.isEmpty()) {
                setTokenMatched(token, TokenType.StepLine, text, keyword, indent, null, null);
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean match_TableRow(Token token) {
        Matcher matcher = TABLE_ROW_PATTERN.matcher(token.line.getLineText(-1));
        if (matcher.find()) {
            setTokenMatched(token, TokenType.TableRow, null, null, null, null, token.line.getTableCells());
            return true;
        }
        return false;
    }

    @Override
    public boolean match_Empty(Token token) {
        if (token.line == null) return false;
        if (token.line.isEmpty()) {
            setTokenMatched(token, TokenType.Empty, null, null, null, null, null);
            return true;
        }
        return false;
    }

    @Override
    public boolean match_TagLine(Token token) {
        if (token.line == null) return false;
        
        String lineText = token.line.getLineText(-1);
        List<GherkinLineSpan> items = new ArrayList<>();
        
        // Pattern for backtick-wrapped tags
        Pattern tagPattern = Pattern.compile("`(@[^\\s`]+)`");
        Matcher matcher = tagPattern.matcher(lineText);
        
        boolean found = false;
        while (matcher.find()) {
            found = true;
            String tag = matcher.group(1);  // Group 1 is the actual tag without backticks
            int column = matcher.start(1) + 1;  // +1 for 1-based column indexing
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
        if (token.line == null) return false;
        return !activeDocStringSeparator  ?
                // open
                match_DocStringSeparator(token,  true)
                // close
                : match_DocStringSeparator(token,  false);
    }

    private boolean match_DocStringSeparator(Token token, boolean isOpen) {
        String separator = GherkinLanguageConstants.DOCSTRING_ALTERNATIVE_SEPARATOR;
        String lineText = token.line.getLineText(-1);
        if (lineText.trim().equals(separator)) {
            String mediaType = null;
            if (isOpen) {
                mediaType = token.line.getRestTrimmed(separator.length());
                activeDocStringSeparator = true;
                indentToRemove = token.line.indent();
            } else {
                activeDocStringSeparator = false;
                indentToRemove = 0;
            }

            setTokenMatched(token, TokenType.DocStringSeparator, mediaType, separator, null, null, null);
            return true;
        }
        return false;
    }

    @Override
    public boolean match_Comment(Token token) {
        if (token.line == null) return false;
        
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
        if (tableCells == null || tableCells.isEmpty()) return false;
        
        // Check if all cells match the GFM separator pattern: :?-+:?
        // Examples of valid separators: ---, :---, ---:, :---:
        Pattern separatorPattern = Pattern.compile("^:?-+:?$");
        
        return tableCells.stream()
            .map(cell -> cell.text)
            .allMatch(text -> separatorPattern.matcher(text.trim()).matches());
    }

    @Override
    public boolean match_Other(Token token) {
        if (token.line == null) return false;
        
        String text = token.line.getLineText(indentToRemove); // take the entire line, except removing DocString indents
        setTokenMatched(token, TokenType.Other, text, null, 0, null, null);
        return true;
    }

    @Override
    public boolean match_Language(Token token) {
        if (token.line == null) return false;
        
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
        activeDocStringSeparator = false;
        indentToRemove = 0;
        currentDialect = dialectProvider.getDefaultDialect();
    }
    
}