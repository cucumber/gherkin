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
import static java.util.Objects.requireNonNull;

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

    private AstNode requiredCurrentNode() {
        return requireNonNull(stack.peek());
    }

    @Override
    public void build(Token token) {
        if (token.matchedType == TokenType.Comment) {
            Comment comment = new Comment(token.location, token.getRequiredMatchedText());
            comments.add(comment);
        } else {
            requiredCurrentNode().add(token.getRequiredMatchedType().ruleType, token);
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
        requiredCurrentNode().add(node.ruleType, transformedNode);
    }

    private Object getTransformedNode(AstNode node) {
        return switch (node.ruleType) {
            case Step -> {
                Token stepLine = node.getToken(TokenType.StepLine);
                yield new Step(
                        stepLine.location,
                        stepLine.getRequiredMatchedKeyword(),
                        stepLine.keywordType,
                        stepLine.getRequiredMatchedText(),
                        node.getSingle(RuleType.DocString),
                        node.getSingle(RuleType.DataTable),
                        idGenerator.newId()
                );
            }
            case DocString -> {
                Token separatorToken = node.getTokens(TokenType.DocStringSeparator).get(0);
                String matchedText = separatorToken.getRequiredMatchedText();
                String mediaType = matchedText.isEmpty() ? null : matchedText;
                List<Token> lineTokens = node.getTokens(TokenType.Other);
                String content = joinMatchedText(lineTokens, lineTokens.size());
                yield new DocString(
                        separatorToken.location,
                        mediaType,
                        content,
                        separatorToken.getRequiredMatchedKeyword()
                );
            }
            case DataTable -> {
                List<TableRow> rows = getTableRows(node);
                yield new DataTable(rows.get(0).getLocation(), rows);
            }
            case Background -> {
                Token backgroundLine = node.getToken(TokenType.BackgroundLine);
                yield new Background(
                        backgroundLine.location,
                        backgroundLine.getRequiredMatchedKeyword(),
                        backgroundLine.getRequiredMatchedText(),
                        getDescription(node),
                        getSteps(node),
                        idGenerator.newId()
                );
            }
            case ScenarioDefinition -> {
                AstNode scenarioNode = node.getRequiredSingle(RuleType.Scenario);
                Token scenarioLine = scenarioNode.getToken(TokenType.ScenarioLine);

                yield new Scenario(
                        scenarioLine.location,
                        getTags(node),
                        scenarioLine.getRequiredMatchedKeyword(),
                        scenarioLine.getRequiredMatchedText(),
                        getDescription(scenarioNode),
                        getSteps(scenarioNode),
                        scenarioNode.getItems(RuleType.ExamplesDefinition),
                        idGenerator.newId()
                );
            }
            case ExamplesDefinition -> {
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

                yield new Examples(
                        examplesLine.location,
                        getTags(node),
                        examplesLine.getRequiredMatchedKeyword(),
                        examplesLine.getRequiredMatchedText(),
                        getDescription(examplesNode),
                        tableHeader,
                        tableBody,
                        idGenerator.newId()
                );
            }
            case ExamplesTable -> getTableRows(node);
            case Description -> {
                List<Token> lineTokens = node.getTokens(TokenType.Other);
                // Trim trailing empty lines
                int toIndex = lineTokens.size();
                while (toIndex > 0 && lineTokens.get(toIndex - 1).getRequiredLine().isEmpty()) {
                    toIndex--;
                }
                yield joinMatchedText(lineTokens, toIndex);
            }
            case Feature -> {
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

                yield new Feature(
                        featureLine.location,
                        tags,
                        featureLine.getRequiredMatchedLanguage(),
                        featureLine.getRequiredMatchedKeyword(),
                        featureLine.getRequiredMatchedText(),
                        getDescription(header),
                        children
                );
            }
            case Rule -> {
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

                yield new Rule(
                        ruleLine.location,
                        tags,
                        ruleLine.getRequiredMatchedKeyword(),
                        ruleLine.getRequiredMatchedText(),
                        getDescription(header),
                        children,
                        idGenerator.newId()
                );
            }
            case GherkinDocument -> {
                Feature feature = node.getSingle(RuleType.Feature);
                // feature is null when the file is empty or contains only comments/whitespace, or no Cucumber feature
                yield new GherkinDocument(uri, feature, comments);
            }
            // Do nothing.
            default -> node;
        };
    }

    private static String joinMatchedText(List<Token> lineTokens, int toIndex) {
        StringBuilder content = new StringBuilder(FEATURE_FILE_AVERAGE_LINE_LENGTH * lineTokens.size());
        for (int i = 0; i < toIndex; i++) {
            Token lineToken = lineTokens.get(i);
            String matchedText = lineToken.getRequiredMatchedText();
            content.append(matchedText).append('\n');
        }
        int contentLength = content.length();
        if (contentLength > 0) {
            // Remove the last \n
            content.setLength(contentLength - 1); 
        }
        return content.toString();
    }

    @SuppressWarnings("ForLoopReplaceableByForEach")
    private List<TableRow> getTableRows(AstNode node) {
        List<Token> tokens = node.getTokens(TokenType.TableRow);
        int tokenSize = tokens.size();
        List<TableRow> rows = new ArrayList<>(tokenSize);
        // classic 'for' loop is ~2x faster than 'for-each'
        for (int i = 0; i < tokenSize; i++) {
            Token token = tokens.get(i);
            rows.add(new TableRow(token.location, getCells(token), idGenerator.newId()));
        }
        ensureCellCount(rows);
        return rows;
    }

    @SuppressWarnings("ForLoopReplaceableByForEach")
    private void ensureCellCount(List<TableRow> rows) {
        if (rows.isEmpty())
            return;

        int firstRowCellsSize = rows.get(0).getCells().size();
        // classic 'for' loop is ~2x faster than 'for-each'
        for (int i = 0, rowsSize = rows.size(); i < rowsSize; i++) {
            TableRow row = rows.get(i);
            if (row.getCells().size() != firstRowCellsSize) {
                throw new ParserException.AstBuilderException("inconsistent cell count within the table", row.getLocation());
            }
        }
    }

    @SuppressWarnings("ForLoopReplaceableByForEach") 
    private List<TableCell> getCells(Token token) {
        List<LineSpan> matchedItems = token.matchedItems;
        if (matchedItems == null) {
            return new ArrayList<>(0);
        }
        int itemSize = matchedItems.size();
        List<TableCell> cells = new ArrayList<>(itemSize);
        // classic 'for' loop is ~2x faster than 'for-each'
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
        // tags are optional
        if (tagsNode == null) {
            return new ArrayList<>(0);
        }

        List<Token> tokens = tagsNode.getTokens(TokenType.TagLine);
        List<Tag> tags = new ArrayList<>();
        for (Token token : tokens) {
            List<LineSpan> matchedItems = token.matchedItems;
            if (matchedItems != null) {
                for (LineSpan tagItem : matchedItems) {
                    tags.add(new Tag(atColumn(token.location, tagItem.column), tagItem.text, idGenerator.newId()));
                }
            }
        }
        return tags;
    }

    @Override
    public GherkinDocument getResult() {
        return requiredCurrentNode().getRequiredSingle(RuleType.GherkinDocument);
    }

}
