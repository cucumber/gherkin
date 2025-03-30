package io.cucumber.gherkin;

import java.util.ArrayList;
import java.util.Collections;
import java.util.EnumMap;
import java.util.List;
import java.util.Map;

import static io.cucumber.gherkin.Parser.RuleType;
import static io.cucumber.gherkin.Parser.TokenType;
import static java.util.Objects.requireNonNull;

class AstNode {
    // subItems is relatively sparse, so pre-initializing all values with empty
    // lists is not efficient
    private final Map<RuleType, List<Object>> subItems = new EnumMap<>(RuleType.class);
    final RuleType ruleType;

    AstNode(RuleType ruleType) {
        this.ruleType = ruleType;
    }

    void add(RuleType ruleType, Object obj) {
        List<Object> items = subItems.get(ruleType);
        if (items == null) { // faster than Map.computeIfAbsent
            items = new ArrayList<>();
            subItems.put(ruleType, items);
        }
        items.add(obj);
    }

    @SuppressWarnings("unchecked")
    <T> T getSingle(RuleType ruleType, T defaultResult) {
        // if not null, then at least one item is present because
        // the list was created in add(), so no need to check isEmpty()
        List<T> items = (List<T>) subItems.get(ruleType);
        return items == null ? defaultResult : items.get(0);
    }

    @SuppressWarnings("unchecked")
    <T> List<T> getItems(RuleType ruleType) {
        List<T> items = (List<T>) subItems.get(ruleType);
        if (items == null) {
            return Collections.emptyList();
        }
        return items;
    }

    Token getToken(TokenType tokenType) {
        return requireNonNull(getSingle(tokenType.ruleType, null));
    }

    List<Token> getTokens(TokenType tokenType) {
        return getItems(tokenType.ruleType);
    }
}
