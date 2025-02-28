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

    public boolean matchFeatureLine(Token token) {
        String pattern = KeywordPrefix.HEADER.getPattern() + "(" +
                String.join("|", currentDialect.getFeatureKeywords()) + "):(\\s+)(.*)";
        Pattern headerPattern = Pattern.compile(pattern);
        Matcher matcher = headerPattern.matcher(token.line.getLineText(-1));
        if (matcher.find()) {
            String keyword = matcher.group(2);
            String text = matcher.group(4).trim();
            int indent = matcher.group(1).length();
            setTokenMatched(token, TokenType.FeatureLine, text, keyword, indent, null, null);
            return true;
        }
        return false;
    }

    private void setTokenMatched(Token token, TokenType matchedType, String text, String keyword, Integer indent, StepKeywordType keywordType, List<GherkinLineSpan> items) {
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