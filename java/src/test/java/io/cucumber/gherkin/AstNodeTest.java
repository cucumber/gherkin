package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertThrows;

class AstNodeTest {

    @Test
    void getSingle_returns_default_value_when_no_subitem() {
        // Given a node
        AstNode astNode = new AstNode(Parser.RuleType.Step);
        String defaultValue = "defaultValue";

        // When no subItem is present

        // Then
        assertEquals(defaultValue, astNode.getSingle(Parser.RuleType.Step, defaultValue));
    }

    @Test
    void getSingle_returns_default_value_when_null_subitem() {
        // Given a node
        AstNode astNode = new AstNode(Parser.RuleType.Step);
        String defaultValue = "defaultValue";

        // When no subItem is present

        // Then
        assertEquals(defaultValue, astNode.getSingle(Parser.RuleType.Scenario, defaultValue));
    }

    @Test
    void getSingle_returns_first_item() {
        // Given a node
        AstNode astNode = new AstNode(Parser.RuleType.Step);

        // When more than one item is present
        String item1 = "item1";
        astNode.add(Parser.RuleType.Step, item1);
        astNode.add(Parser.RuleType.Step, "item2");

        // Then
        assertEquals(item1, astNode.getSingle(Parser.RuleType.Step, "defaultValue"));
    }

    @Test
    void getRequiredSingle_throws_exception_when_no_items() {
        // Given a node
        AstNode astNode = new AstNode(Parser.RuleType.Step);

        // When no subItem is present

        // Then
        assertThrows(NullPointerException.class, () -> astNode.getRequiredSingle(Parser.RuleType.Scenario));
    }

    @Test
    void getSingle_return_null_when_no_items() {
        // Given a node
        AstNode astNode = new AstNode(Parser.RuleType.Step);

        // When no subItem is present

        // Then
        assertNull(astNode.getSingle(Parser.RuleType.Scenario));
    }
}
