package io.cucumber.gherkin;

import java.util.ArrayList;
import java.util.Collections;
import java.util.EnumMap;
import java.util.List;
import java.util.Map;

import static io.cucumber.gherkin.Parser.RuleType;
import static io.cucumber.gherkin.Parser.TokenType;

class AstNode {
    // subItems is relatively sparse, so preinitializing all values with empty lists is not efficient
    private final Map<RuleType, List<Object>> subItems = new EnumMap<>(RuleType.class);
    public final RuleType ruleType;

    public AstNode(RuleType ruleType) {
        this.ruleType = ruleType;
    }

    public void add(RuleType ruleType, Object obj) {
        List<Object> items = subItems.get(ruleType);
        if (items == null) { // faster than Map.computeIfAbsent
            items = new ArrayList<>();
            subItems.put(ruleType, items);
        }
        items.add(obj);
    }

    public <T> T getSingle(RuleType ruleType, T defaultResult) {
        // if not null, then at least one item is present because
        // the list was created in add(), so no need to check isEmpty()
        List<T> items = (List<T>) subItems.get(ruleType);
        return items == null ? defaultResult : items.get(0);
    }

    public <T> List<T> getItems(RuleType ruleType) {
        List<T> items = (List<T>) subItems.get(ruleType);
        if (items == null) {
            return Collections.emptyList();
        }
        return items;
    }

    public Token getToken(TokenType tokenType) {
        return getSingle(tokenType.ruleType, new Token(null, null));
    }

    public List<Token> getTokens(TokenType tokenType) {
        return getItems(tokenType.ruleType);
    }
}
