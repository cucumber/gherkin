using Gherkin.Ast;

namespace Gherkin;

public class AstBuilder<T> : IAstBuilder<T>
{
    private readonly Stack<AstNode> _stack = new();
    private AstNode CurrentNode => _stack.Peek();
    private readonly List<Comment> _comments = new();

    public AstBuilder()
    {
        Reset();
    }

    public void Reset()
    {
        _stack.Clear();
        _stack.Push(new AstNode(RuleType.None));
        _comments.Clear();
    }

    public void Build(Token token)
    {
        if (token.MatchedType == TokenType.Comment)
        {
            _comments.Add(CreateComment(GetLocation(token), token.MatchedText));
        }
        else
        {
            CurrentNode.Add((RuleType)token.MatchedType, token);
        }
    }

    public void StartRule(RuleType ruleType)
    {
        _stack.Push(new AstNode(ruleType));
    }

    public void EndRule(RuleType ruleType)
    {
        var node = _stack.Pop();
        object transformedNode = GetTransformedNode(node);
        CurrentNode.Add(node.RuleType, transformedNode);
    }

    public T GetResult()
    {
        return CurrentNode.GetSingle<T>(RuleType.GherkinDocument);
    }

    private object GetTransformedNode(AstNode node)
    {
        switch (node.RuleType)
        {
            case RuleType.Step:
                {
                    var stepLine = node.GetToken(TokenType.StepLine);
                    var stepArg = node.GetSingle<StepArgument>(RuleType.DataTable) ??
                                  node.GetSingle<StepArgument>(RuleType.DocString);
                    var keywordType = GetKeywordType(stepLine);
                    return CreateStep(GetLocation(stepLine), stepLine.MatchedKeyword, keywordType, stepLine.MatchedText, stepArg, node);
                }
            case RuleType.DocString:
                {
                    var separatorToken = node.GetTokens(TokenType.DocStringSeparator).First();
                    var contentType = separatorToken.MatchedText.Length == 0 ? null : separatorToken.MatchedText;
                    var lineTokens = node.GetTokens(TokenType.Other);
                    var content = string.Join(Environment.NewLine, lineTokens.Select(lt => lt.MatchedText));
                    var delimiter = separatorToken.MatchedKeyword.Length == 0 ? null : separatorToken.MatchedKeyword;

                    return CreateDocString(GetLocation(separatorToken), contentType, content, delimiter, node);
                }
            case RuleType.DataTable:
                {
                    var rows = GetTableRows(node);
                    return CreateDataTable(rows, node);
                }
            case RuleType.Background:
                {
                    var backgroundLine = node.GetToken(TokenType.BackgroundLine);
                    var description = GetDescription(node);
                    var steps = GetSteps(node);
                    return CreateBackground(GetLocation(backgroundLine), backgroundLine.MatchedKeyword, backgroundLine.MatchedText, description, steps, node);
                }
            case RuleType.ScenarioDefinition:
                {
                    var tags = GetTags(node);

                    var scenarioNode = node.GetSingle<AstNode>(RuleType.Scenario);
                    var scenarioLine = scenarioNode.GetToken(TokenType.ScenarioLine);

                    var description = GetDescription(scenarioNode);
                    var steps = GetSteps(scenarioNode);
                    List<Examples> examples = [.. scenarioNode.GetItems<Examples>(RuleType.ExamplesDefinition)];
                    return CreateScenario(tags, GetLocation(scenarioLine), scenarioLine.MatchedKeyword, scenarioLine.MatchedText, description, steps, examples, node);
                }
            case RuleType.ExamplesDefinition:
                {
                    var tags = GetTags(node);
                    var examplesNode = node.GetSingle<AstNode>(RuleType.Examples);
                    var examplesLine = examplesNode.GetToken(TokenType.ExamplesLine);
                    var description = GetDescription(examplesNode);

                    var allRows = examplesNode.GetSingle<List<TableRow>>(RuleType.ExamplesTable);
                    var header = allRows != null ? allRows[0] : null;
                    var rows = allRows != null ? allRows.Skip(1).ToList() : null;
                    return CreateExamples(tags, GetLocation(examplesLine), examplesLine.MatchedKeyword, examplesLine.MatchedText, description, header, rows, node);
                }
            case RuleType.ExamplesTable:
                {
                    return GetTableRows(node);
                }
            case RuleType.Description:
                {
                    IEnumerable<Token> lineTokens = node.GetTokens(TokenType.Other);

                    // Trim trailing empty lines
                    lineTokens = lineTokens.Reverse().SkipWhile(t => string.IsNullOrWhiteSpace(t.MatchedText)).Reverse();

                    return string.Join(Environment.NewLine, lineTokens.Select(lt => lt.MatchedText));
                }
            case RuleType.Feature:
                {
                    var header = node.GetSingle<AstNode>(RuleType.FeatureHeader);
                    if (header == null) return null;
                    var tags = GetTags(header);
                    var featureLine = header.GetToken(TokenType.FeatureLine);
                    if (featureLine == null) return null;
                    var children = new List<IHasLocation>();
                    var background = node.GetSingle<Background>(RuleType.Background);
                    if (background != null)
                        children.Add(background);
                    foreach (var scenarioDefinition in node.GetItems<IHasLocation>(RuleType.ScenarioDefinition))
                        children.Add(scenarioDefinition);
                    foreach (var rule in node.GetItems<IHasLocation>(RuleType.Rule))
                        children.Add(rule);
                    var description = GetDescription(header);
                    if (featureLine.MatchedGherkinDialect == null) return null;
                    var language = featureLine.MatchedGherkinDialect.Language;

                    return CreateFeature(tags, GetLocation(featureLine), language, featureLine.MatchedKeyword, featureLine.MatchedText, description, children, node);
                }
            case RuleType.Rule:
                {
                    var header = node.GetSingle<AstNode>(RuleType.RuleHeader);
                    if (header == null) return null;
                    var tags = GetTags(header);
                    var ruleLine = header.GetToken(TokenType.RuleLine);
                    if (ruleLine == null) return null;
                    var children = new List<IHasLocation>();
                    var background = node.GetSingle<Background>(RuleType.Background);
                    if (background != null)
                        children.Add(background);
                    foreach (var scenarioDefinition in node.GetItems<IHasLocation>(RuleType.ScenarioDefinition))
                        children.Add(scenarioDefinition);
                    var description = GetDescription(header);
                    if (ruleLine.MatchedGherkinDialect == null) return null;

                    return CreateRule(tags, GetLocation(ruleLine), ruleLine.MatchedKeyword, ruleLine.MatchedText, description, children, node);
                }
            case RuleType.GherkinDocument:
                {
                    var feature = node.GetSingle<Feature>(RuleType.Feature);

                    return CreateGherkinDocument(feature, _comments.ToArray(), node);
                }
        }

        return node;
    }

    protected virtual StepKeywordType GetKeywordType(Token stepLine)
    {
        var stepKeywordType = stepLine.MatchedGherkinDialect.GetStepKeywordType(stepLine.MatchedKeyword);
        if (stepKeywordType == null || stepKeywordType == StepKeywordType.Unspecified)
            return StepKeywordType.Unspecified;
        return stepKeywordType.Value;
    }

    protected virtual Background CreateBackground(Location location, string keyword, string name, string description, IEnumerable<Step> steps, AstNode node)
    {
        return new Background(location, keyword, name, description, steps);
    }

    protected virtual DataTable CreateDataTable(List<TableRow> rows, AstNode node)
    {
        return new DataTable(rows);
    }

    protected virtual Comment CreateComment(Location location, string text)
    {
        return new Comment(location, text);
    }

    protected virtual Examples CreateExamples(IEnumerable<Tag> tags, Location location, string keyword, string name, string description, TableRow header, IEnumerable<TableRow> body, AstNode node)
    {
        return new Examples(tags, location, keyword, name, description, header, body);
    }

    protected virtual Scenario CreateScenario(IEnumerable<Tag> tags, Location location, string keyword, string name, string description, IEnumerable<Step> steps, IEnumerable<Examples> examples, AstNode node)
    {
        return new Scenario(tags, location, keyword, name, description, steps, examples);
    }

    protected virtual DocString CreateDocString(Location location, string contentType, string content, string delimiter, AstNode node)
    {
        return new DocString(location, contentType, content, delimiter);
    }

    protected virtual Step CreateStep(Location location, string keyword, StepKeywordType keywordType, string text, StepArgument argument, AstNode node)
    {
        return new Step(location, keyword, keywordType, text, argument);
    }

    protected virtual GherkinDocument CreateGherkinDocument(Feature feature, IEnumerable<Comment> gherkinDocumentComments, AstNode node)
    {
        return new GherkinDocument(feature, gherkinDocumentComments);
    }

    protected virtual Feature CreateFeature(IEnumerable<Tag> tags, Location location, string language, string keyword, string name, string description, IEnumerable<IHasLocation> children, AstNode node)
    {
        return new Feature(tags, location, language, keyword, name, description, children);
    }

    protected virtual Rule CreateRule(IEnumerable<Tag> tags, Location location, string keyword, string name, string description, IEnumerable<IHasLocation> children, AstNode node)
    {
        return new Rule(tags, location, keyword, name, description, children);
    }

    protected virtual Tag CreateTag(Location location, string name, AstNode node)
    {
        return new Tag(location, name);
    }

    protected Location CreateLocation(int line, int column)
    {
        return new Location(line, column);
    }

    protected virtual TableRow CreateTableRow(Location location, IEnumerable<TableCell> cells, AstNode node)
    {
        return new TableRow(location, cells);
    }

    protected TableCell CreateTableCell(Location location, string value)
    {
        return new TableCell(location, value);
    }

    private Location GetLocation(Token token, int column = 0)
    {
        return column == 0 ? token.Location : CreateLocation(token.Location.Line, column);
    }

    private IEnumerable<Tag> GetTags(AstNode node)
    {
        var tagsNode = node.GetSingle<AstNode>(RuleType.Tags);
        if (tagsNode == null)
            return [];

        var tags = new List<Tag>();
        foreach (var line in tagsNode.GetTokens(TokenType.TagLine))
        {
            foreach (var matchedItem in line.MatchedItems)
                tags.Add(CreateTag(GetLocation(line, matchedItem.Column), matchedItem.Text, tagsNode));
        }
        return tags;
    }

    private List<TableRow> GetTableRows(AstNode node)
    {
        var rows = new List<TableRow>();
        int cellCount = 0;
        bool firstRow = true;
        foreach (var rowToken in node.GetTokens(TokenType.TableRow))
        {
            var rowLocation = GetLocation(rowToken);
            var cells = new List<TableCell>();
            foreach (var cellItem in rowToken.MatchedItems)
                cells.Add(CreateTableCell(GetLocation(rowToken, cellItem.Column), cellItem.Text));
            if (firstRow)
            {
                cellCount = cells.Count;
                firstRow = false;
            }
            else if (cells.Count != cellCount)
            {
                HandleAstError("inconsistent cell count within the table", rowLocation);
            }
            rows.Add(CreateTableRow(rowLocation, cells, node));
        }
        return rows;
    }

    protected virtual void HandleAstError(string message, Location location)
    {
        throw new AstBuilderException(message, location);
    }

    private static List<Step> GetSteps(AstNode scenarioDefinitionNode)
    {
        return [..scenarioDefinitionNode.GetItems<Step>(RuleType.Step)];
    }

    private static string GetDescription(AstNode scenarioDefinitionNode)
    {
        return scenarioDefinitionNode.GetSingle<string>(RuleType.Description);
    }
}
