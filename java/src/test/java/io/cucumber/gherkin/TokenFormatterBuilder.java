package io.cucumber.gherkin;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

class TokenFormatterBuilder implements Parser.Builder<String> {
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
    public String getResult() {
        return tokens.stream().collect(Collectors.joining("\n", "","\n"));
    }

    @Override
    public void reset(String uri) {
    }
}
