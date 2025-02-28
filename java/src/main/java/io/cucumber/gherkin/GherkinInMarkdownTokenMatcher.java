package io.cucumber.gherkin;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class GherkinInMarkdownTokenMatcher {
    private enum KeywordPrefix {
        BULLET("^(\\s*[*+-]\\s*)"),
        HEADER("^(\\s*(#{1,6})\\s)");

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
    private GherkinDialect dialect;

    public GherkinInMarkdownTokenMatcher(String defaultDialectName) {
        this.defaultDialectName = defaultDialectName;
        this.dialectName = defaultDialectName;
        GherkinDialectProvider dialectProvider = new GherkinDialectProvider(defaultDialectName);
        this.dialect = dialectProvider.getDialect(defaultDialectName)
                .orElseThrow(() -> new ParserException("No such dialect: " + defaultDialectName));
    }

    public boolean matchFeatureLine(Token token) {
        String pattern = KeywordPrefix.HEADER.getPattern() + "(" +
                String.join("|", dialect.getFeatureKeywords()) + "):(.*)";
        Pattern headerPattern = Pattern.compile(pattern);
        Matcher matcher = headerPattern.matcher(token.line.getLineText(-1));
        return matcher.find();
    }
}