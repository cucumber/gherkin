package io.cucumber.gherkin;

import io.cucumber.messages.IdGenerator;
import io.cucumber.messages.types.Background;
import io.cucumber.messages.types.Comment;
import io.cucumber.messages.types.DataTable;
import io.cucumber.messages.types.DocString;
import io.cucumber.messages.types.Examples;
import io.cucumber.messages.types.Feature;
import io.cucumber.messages.types.FeatureChild;
import io.cucumber.messages.types.GherkinDocument;
import io.cucumber.messages.types.Rule;
import io.cucumber.messages.types.RuleChild;
import io.cucumber.messages.types.Scenario;
import io.cucumber.messages.types.Step;
import io.cucumber.messages.types.TableCell;
import io.cucumber.messages.types.TableRow;
import io.cucumber.messages.types.Tag;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Deque;
import java.util.List;

import static io.cucumber.gherkin.GherkinParser.FEATURE_FILE_AVERAGE_LINE_LENGTH;
import static io.cucumber.gherkin.Locations.atColumn;
import static io.cucumber.gherkin.Parser.Builder;
import static io.cucumber.gherkin.Parser.RuleType;
import static io.cucumber.gherkin.Parser.TokenType;

final class GherkinDocumentBuilder implements Builder<GherkinDocument> {
    private final List<Comment> comments = new ArrayList<>();
    private final IdGenerator idGenerator;
    private String uri;

    private Deque<AstNode> stack;

    GherkinDocumentBuilder(IdGenerator idGenerator, String uri) {
        this.idGenerator = idGenerator;
        reset(uri);
    }

    @Override
    public void reset(String uri) {
        this.uri = uri;
        stack = new ArrayDeque<>();
        stack.push(new AstNode(RuleType.None));
    }

    private AstNode currentNode() {
        return stack.peek();
    }

    @Override
    public void build(Token token) {
        if (token.matchedType == TokenType.Comment) {
            Comment comment = new Comment(token.location, token.matchedText);
            comments.add(comment);
        } else {
            currentNode().add(token.matchedType.ruleType, token);
        }
    }

    @Override
    public void startRule(RuleType ruleType) {
        stack.push(new AstNode(ruleType));
    }

    @Override
    public void endRule(RuleType ruleType) {
        AstNode node = stack.pop();
        Object transformedNode = getTransformedNode(node);
        currentNode().add(node.ruleType, transformedNode);
    }

    private Object getTransformedNode(AstNode node) {
        switch (node.ruleType) {
            case Step: {
                Token stepLine = node.getToken(TokenType.StepLine);
                return new Step(
                        stepLine.location,
                        stepLine.matchedKeyword,
                        stepLine.keywordType,
                        stepLine.matchedText,
                        node.getSingle(RuleType.DocString),
                        node.getSingle(RuleType.DataTable),
                        idGenerator.newId()
                );
            }
            case DocString: {
                Token separatorToken = node.getTokens(TokenType.DocStringSeparator).get(0);
                String mediaType = separatorToken.matchedText.isEmpty() ? null : separatorToken.matchedText;
                List<Token> lineTokens = node.getTokens(TokenType.Other);
                String content = joinMatchedText(lineTokens, lineTokens.size());
                return new DocString(
                        separatorToken.location,
                        mediaType,
                        content,
                        separatorToken.matchedKeyword
                );
            }
            case DataTable: {
                List<TableRow> rows = getTableRows(node);
                return new DataTable(rows.get(0).getLocation(), rows);
            }
            case Background: {
                Token backgroundLine = node.getToken(TokenType.BackgroundLine);
                return new Background(
                        backgroundLine.location,
                        backgroundLine.matchedKeyword,
                        backgroundLine.matchedText,
                        getDescription(node),
                        getSteps(node),
                        idGenerator.newId()
                );
            }
            case ScenarioDefinition: {
                AstNode scenarioNode = node.getRequiredSingle(RuleType.Scenario);
                Token scenarioLine = scenarioNode.getToken(TokenType.ScenarioLine);

                return new Scenario(
                        scenarioLine.location,
                        getTags(node),
                        scenarioLine.matchedKeyword,
                        scenarioLine.matchedText,
                        getDescription(scenarioNode),
                        getSteps(scenarioNode),
                        scenarioNode.getItems(RuleType.ExamplesDefinition),
                        idGenerator.newId()
                );
            }
            case ExamplesDefinition: {
                AstNode examplesNode = node.getRequiredSingle(RuleType.Examples);
                Token examplesLine = examplesNode.getToken(TokenType.ExamplesLine);
                // rows is null when a Scenario Outline has no Examples table
                List<TableRow> rows = examplesNode.getSingle(RuleType.ExamplesTable);
                TableRow tableHeader;
                List<TableRow> tableBody;
                if (rows != null && !rows.isEmpty()) {
                    tableHeader = rows.get(0);
                    tableBody = rows.subList(1, rows.size());
                } else {
                    tableHeader = null;
                    tableBody = Collections.emptyList();
                }

                return new Examples(
                        examplesLine.location,
                        getTags(node),
                        examplesLine.matchedKeyword,
                        examplesLine.matchedText,
                        getDescription(examplesNode),
                        tableHeader,
                        tableBody,
                        idGenerator.newId()
                );
            }
            case ExamplesTable: {
                return getTableRows(node);
            }
            case Description: {
                List<Token> lineTokens = node.getTokens(TokenType.Other);
                // Trim trailing empty lines
                int toIndex = lineTokens.size();
                while (toIndex > 0 && lineTokens.get(toIndex - 1).line.isEmpty()) {
                    toIndex--;
                }
                return joinMatchedText(lineTokens, toIndex);
            }
            case Feature: {
                AstNode header = node.getRequiredSingle(RuleType.FeatureHeader);
                List<Tag> tags = getTags(header);
                Token featureLine = header.getToken(TokenType.FeatureLine);

                List<FeatureChild> children = new ArrayList<>();
                // Background is an optional element of a Feature, so can be null
                Background background = node.getSingle(RuleType.Background);
                if (background != null) {
                    children.add(new FeatureChild(null, background, null));
                }
                for (Scenario scenario : node.<Scenario>getItems(RuleType.ScenarioDefinition)) {
                    children.add(new FeatureChild(null, null, scenario));
                }
                for (Rule rule : node.<Rule>getItems(RuleType.Rule)) {
                    children.add(new FeatureChild(rule, null, null));
                }

                return new Feature(
                        featureLine.location,
                        tags,
                        featureLine.matchedLanguage,
                        featureLine.matchedKeyword,
                        featureLine.matchedText,
                        getDescription(header),
                        children
                );
            }
            case Rule: {
                AstNode header = node.getRequiredSingle(RuleType.RuleHeader);
                Token ruleLine = header.getToken(TokenType.RuleLine);

                List<RuleChild> children = new ArrayList<>();
                List<Tag> tags = getTags(header);

                // Background is an optional element of a Feature, so can be null
                Background background = node.getSingle(RuleType.Background);
                if (background != null) {
                    children.add(new RuleChild(background, null));
                }
                List<Scenario> scenarios = node.getItems(RuleType.ScenarioDefinition);
                for (Scenario scenario : scenarios) {
                    children.add(new RuleChild(null, scenario));
                }

                return new Rule(
                        ruleLine.location,
                        tags,
                        ruleLine.matchedKeyword,
                        ruleLine.matchedText,
                        getDescription(header),
                        children,
                        idGenerator.newId()
                );

            }
            case GherkinDocument: {
                Feature feature = node.getSingle(RuleType.Feature);
                // feature is null when the file is empty or contains only comments/whitespace, or no Cucumber feature
                return new GherkinDocument(uri, feature, comments);
            }

        }
        return node;
    }

    private static String joinMatchedText(List<Token> lineTokens, int toIndex) {
        StringBuilder content = new StringBuilder(FEATURE_FILE_AVERAGE_LINE_LENGTH * lineTokens.size());
        for (int i = 0; i < toIndex; i++) {
            Token lineToken = lineTokens.get(i);
            content.append(lineToken.matchedText).append('\n');
        }
        int contentLength = content.length();
        if (contentLength > 0) {
            content.setLength(contentLength - 1); // Remove the last \n
        }
        return content.toString();
    }

    @SuppressWarnings("ForLoopReplaceableByForEach") // classic 'for' loop is ~2x faster than 'for-each'
    private List<TableRow> getTableRows(AstNode node) {
        List<Token> tokens = node.getTokens(TokenType.TableRow);
        int tokenSize = tokens.size();
        List<TableRow> rows = new ArrayList<>(tokenSize);
        for (int i = 0; i < tokenSize; i++) {
            Token token = tokens.get(i);
            rows.add(new TableRow(token.location, getCells(token), idGenerator.newId()));
        }
        ensureCellCount(rows);
        return rows;
    }

    @SuppressWarnings("ForLoopReplaceableByForEach") // classic 'for' loop is ~2x faster than 'for-each'
    private void ensureCellCount(List<TableRow> rows) {
        if (rows.isEmpty())
            return;

        int firstRowCellsSize = rows.get(0).getCells().size();
        for (int i = 0, rowsSize = rows.size(); i < rowsSize; i++) {
            TableRow row = rows.get(i);
            if (row.getCells().size() != firstRowCellsSize) {
                throw new ParserException.AstBuilderException("inconsistent cell count within the table", row.getLocation());
            }
        }
    }

    @SuppressWarnings("ForLoopReplaceableByForEach") // classic 'for' loop is ~2x faster than 'for-each'
    private List<TableCell> getCells(Token token) {
        List<LineSpan> matchedItems = token.matchedItems;
        int itemSize = matchedItems.size();
        List<TableCell> cells = new ArrayList<>(itemSize);
        for (int i = 0; i < itemSize; i++) {
            LineSpan cellItem = matchedItems.get(i);
            TableCell tableCell = new TableCell(
                    atColumn(token.location, cellItem.column),
                    cellItem.text
            );
            cells.add(tableCell);
        }
        return cells;
    }

    private List<Step> getSteps(AstNode node) {
        return node.getItems(RuleType.Step);
    }

    private String getDescription(AstNode node) {
        return node.getSingle(RuleType.Description, "");
    }

    private List<Tag> getTags(AstNode node) {
        AstNode tagsNode = node.getSingle(RuleType.Tags);
        if (tagsNode == null) {// tags are optional
            return Collections.emptyList();
        }

        List<Token> tokens = tagsNode.getTokens(TokenType.TagLine);
        List<Tag> tags = new ArrayList<>();
        for (Token token : tokens) {
            for (LineSpan tagItem : token.matchedItems) {
                tags.add(new Tag(atColumn(token.location, tagItem.column), tagItem.text, idGenerator.newId()));
            }
        }
        return tags;
    }

    @Override
    public GherkinDocument getResult() {
        return currentNode().getSingle(RuleType.GherkinDocument);
    }

}
