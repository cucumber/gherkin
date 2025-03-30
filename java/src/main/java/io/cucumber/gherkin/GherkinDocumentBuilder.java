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
import java.util.regex.Pattern;

import static io.cucumber.gherkin.Locations.atColumn;
import static io.cucumber.gherkin.Parser.Builder;
import static io.cucumber.gherkin.Parser.RuleType;
import static io.cucumber.gherkin.Parser.TokenType;

class GherkinDocumentBuilder implements Builder<GherkinDocument> {
    public static final Pattern PATTERN_SPACES = Pattern.compile("\\s*");
    /**
     * Cache of Long objects for the range 0-3999. This is used
     * to avoid creating a huge amount of Long objects in getLocation().
     * We can't use Long.valueOf() because it caches only the first 128
     * values, and typical feature files have much more lines.
     */
    private final static Long[] longs = new Long[4000];
    static {
        for (int i = 0; i < longs.length; i++) {
            longs[i] = (long) i;
        }
    }
    private final List<Comment> comments = new ArrayList<>();
    private final IdGenerator idGenerator;
    private String uri;

    private Deque<AstNode> stack;

    public GherkinDocumentBuilder(IdGenerator idGenerator, String uri) {
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
                        node.getSingle(RuleType.DocString, null),
                        node.getSingle(RuleType.DataTable, null),
                        idGenerator.newId()
                );
            }
            case DocString: {
                Token separatorToken = node.getTokens(TokenType.DocStringSeparator).get(0);
                String mediaType = separatorToken.matchedText.isEmpty() ? null : separatorToken.matchedText;
                List<Token> lineTokens = node.getTokens(TokenType.Other);
                String content = concatMatchedText(lineTokens);
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
                AstNode scenarioNode = node.getSingle(RuleType.Scenario, null);
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
                AstNode examplesNode = node.getSingle(RuleType.Examples, null);
                Token examplesLine = examplesNode.getToken(TokenType.ExamplesLine);
                List<TableRow> rows = examplesNode.getSingle(RuleType.ExamplesTable, null);
                TableRow tableHeader = rows != null && !rows.isEmpty() ? rows.get(0) : null;
                List<TableRow> tableBody = rows != null && !rows.isEmpty() ? rows.subList(1, rows.size()) : Collections.emptyList();

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
                int end = lineTokens.size();
                while (end > 0 && PATTERN_SPACES.matcher(lineTokens.get(end - 1).matchedText).matches()) {
                    end--;
                }
                lineTokens = lineTokens.subList(0, end);
                return concatMatchedText(lineTokens);
            }
            case Feature: {
                AstNode header = node.getSingle(RuleType.FeatureHeader, new AstNode(RuleType.FeatureHeader));
                if (header == null) return null;
                List<Tag> tags = getTags(header);
                Token featureLine = header.getToken(TokenType.FeatureLine);
                if (featureLine == null) return null;

                List<FeatureChild> children = new ArrayList<>();
                Background background = node.getSingle(RuleType.Background, null);
                if (background != null) {
                    children.add(new FeatureChild(null, background, null));
                }
                for (Scenario scenario : node.<Scenario>getItems(RuleType.ScenarioDefinition)) {
                    children.add(new FeatureChild(null, null, scenario));
                }
                for (Rule rule : node.<Rule>getItems(RuleType.Rule)) {
                    children.add(new FeatureChild(rule, null, null));
                }
                String description = getDescription(header);
                if (featureLine.matchedGherkinDialect == null)
                    return null;
                String language = featureLine.matchedGherkinDialect.getLanguage();

                return new Feature(
                        featureLine.location,
                        tags,
                        language,
                        featureLine.matchedKeyword,
                        featureLine.matchedText,
                        description,
                        children
                );
            }
            case Rule: {
                AstNode header = node.getSingle(RuleType.RuleHeader, new AstNode(RuleType.RuleHeader));
                if (header == null) return null;
                Token ruleLine = header.getToken(TokenType.RuleLine);
                if (ruleLine == null) return null;

                List<RuleChild> children = new ArrayList<>();
                List<Tag> tags = getTags(header);

                Background background = node.getSingle(RuleType.Background, null);
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
                Feature feature = node.getSingle(RuleType.Feature, null);
                return new GherkinDocument(uri, feature, comments);
            }

        }
        return node;
    }

    private static String concatMatchedText(List<Token> lineTokens) {
        // we guess that the average line is about 50 characters
        StringBuilder content = new StringBuilder(50 * lineTokens.size());
        for (Token lineToken : lineTokens) {
            content.append(lineToken.matchedText).append("\n");
        }
        int contentLength = content.length();
        if (contentLength > 0) {
            content.setLength(contentLength - 1); // Remove the last \n
        }
        return content.toString();
    }

    private List<TableRow> getTableRows(AstNode node) {
        List<Token> tokens = node.getTokens(TokenType.TableRow);
        List<TableRow> rows = new ArrayList<>(tokens.size());

        for (Token token : tokens) {
            rows.add(new TableRow(token.location, getCells(token), idGenerator.newId()));
        }
        ensureCellCount(rows);
        return rows;
    }

    private void ensureCellCount(List<TableRow> rows) {
        if (rows.isEmpty())
            return;

        int cellCount = rows.get(0).getCells().size();
        for (TableRow row : rows) {
            if (row.getCells().size() != cellCount) {
                throw new ParserException.AstBuilderException("inconsistent cell count within the table", row.getLocation());
            }
        }
    }

    private List<TableCell> getCells(Token token) {
        List<TableCell> cells = new ArrayList<>(token.matchedItems.size());
        for (GherkinLineSpan cellItem : token.matchedItems) {
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
        AstNode tagsNode = node.getSingle(RuleType.Tags, new AstNode(RuleType.None));
        if (tagsNode == null)
            return Collections.emptyList();

        List<Token> tokens = tagsNode.getTokens(TokenType.TagLine);
        List<Tag> tags = new ArrayList<>();
        for (Token token : tokens) {
            for (GherkinLineSpan tagItem : token.matchedItems) {
                tags.add(new Tag(atColumn(token.location, tagItem.column), tagItem.text, idGenerator.newId()));
            }
        }
        return tags;
    }

    @Override
    public GherkinDocument getResult() {
        return currentNode().getSingle(RuleType.GherkinDocument, null);
    }

    private static Long getLong(int i) {
        if (i>=longs.length) return (long) i;
        return longs[i];
    }

}
