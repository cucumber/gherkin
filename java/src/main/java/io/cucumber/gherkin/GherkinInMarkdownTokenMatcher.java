package io.cucumber.gherkin;

import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.List;

import io.cucumber.messages.types.StepKeywordType;

import static io.cucumber.gherkin.Parser.TokenType;

public class GherkinInMarkdownTokenMatcher {
    private enum KeywordPrefix {
        BULLET("^(\\s*[*+-]\\s*)"),
        HEADER("^(#{1,6}\\s)");

        private final String pattern;

        KeywordPrefix(String pattern) {
            this.pattern = pattern;
        }

        public String getPattern() {
            return pattern;
        }
    }

    private final String defaultDialectName;
    private String dialectName;
    private GherkinDialect currentDialect;

    public GherkinInMarkdownTokenMatcher(String defaultDialectName) {
        this.defaultDialectName = defaultDialectName;
        this.dialectName = defaultDialectName;
        GherkinDialectProvider dialectProvider = new GherkinDialectProvider(defaultDialectName);
        this.currentDialect = dialectProvider.getDialect(defaultDialectName)
                .orElseThrow(() -> new ParserException("No such dialect: " + defaultDialectName));
    }

    private GherkinDialect getCurrentDialect() {
        return currentDialect;
    }

    public boolean match_FeatureLine(Token token) {
        return matchTitleLine(token, TokenType.FeatureLine, currentDialect.getFeatureKeywords());
    }

    public boolean match_RuleLine(Token token) {
        return matchTitleLine(token, TokenType.RuleLine, currentDialect.getRuleKeywords());
    }

    public boolean match_BackgroundLine(Token token) {
        return matchTitleLine(token, TokenType.BackgroundLine, currentDialect.getBackgroundKeywords());
    }

    public boolean match_ExamplesLine(Token token) {
        return matchTitleLine(token, TokenType.ExamplesLine, currentDialect.getExamplesKeywords());
    }

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

}