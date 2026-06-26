package io.cucumber.gherkin;

import java.util.ArrayList;
import java.util.List;

class TokenFormatterBuilder implements Parser.Builder<List<String>> {
    private final TokenFormatter formatter = new TokenFormatter();
    private final List<String> tokens = new ArrayList<>();

    @Override
    public void build(Token token) {
        tokens.add(formatter.formatToken(token));
    }

    @Override
    public void startRule(Parser.RuleType ruleType) {
    }

    @Override
    public void endRule(Parser.RuleType ruleType) {
    }

    @Override
    public List<String> getResult() {
        return tokens;
    }

    @Override
    public void reset(String uri) {
    }
}
