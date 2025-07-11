using Gherkin.Ast;
using Io.Cucumber.Messages.Types;
using Background = Io.Cucumber.Messages.Types.Background;
using Comment = Io.Cucumber.Messages.Types.Comment;
using DataTable = Io.Cucumber.Messages.Types.DataTable;
using DocString = Io.Cucumber.Messages.Types.DocString;
using Examples = Io.Cucumber.Messages.Types.Examples;
using Feature = Io.Cucumber.Messages.Types.Feature;
using GherkinDocument = Io.Cucumber.Messages.Types.GherkinDocument;
using Location = Io.Cucumber.Messages.Types.Location;
using Rule = Io.Cucumber.Messages.Types.Rule;
using Scenario = Io.Cucumber.Messages.Types.Scenario;
using Step = Io.Cucumber.Messages.Types.Step;
using TableCell = Io.Cucumber.Messages.Types.TableCell;
using TableRow = Io.Cucumber.Messages.Types.TableRow;
using Tag = Io.Cucumber.Messages.Types.Tag;

namespace Gherkin.CucumberMessages;

public class AstMessagesConverter(IIdGenerator idGenerator)
{
    public GherkinDocument ConvertGherkinDocumentToEventArgs(Ast.GherkinDocument gherkinDocument, string sourceEventUri)
    {
        return new GherkinDocument(sourceEventUri, ConvertFeature(gherkinDocument), ConvertComments(gherkinDocument));
    }

    private List<Comment> ConvertComments(Ast.GherkinDocument gherkinDocument)
    {
        return gherkinDocument.Comments.Select(c =>
            new Comment(ConvertLocation(c.Location), c.Text)
        ).ToList();
    }

    private Feature ConvertFeature(Ast.GherkinDocument gherkinDocument)
    {
        var feature = gherkinDocument.Feature;
        if (feature == null)
        {
            return null;
        }

        var children = feature.Children.Select(ConvertToFeatureChild).ToList();
        var tags = feature.Tags.Select(ConvertTag).ToList();

        return new Feature(
            ConvertLocation(feature.Location),
            tags,
            feature.Language,
            feature.Keyword,
            CucumberMessagesDefaults.UseDefault(feature.Name, CucumberMessagesDefaults.DefaultName),
            CucumberMessagesDefaults.UseDefault(feature.Description, CucumberMessagesDefaults.DefaultDescription),
            children
        );
    }

    private static Location ConvertLocation(Ast.Location location)
    {
        return new Location(location.Line, location.Column);
    }

    private FeatureChild ConvertToFeatureChild(IHasLocation hasLocation)
    {
        var tuple = ConvertToChild(hasLocation);
        return new FeatureChild(tuple.Item2, tuple.Item1, tuple.Item3);
    }

    private RuleChild ConvertToRuleChild(IHasLocation hasLocation)
    {
        var tuple = ConvertToChild(hasLocation);
        return new RuleChild(tuple.Item1, tuple.Item3);
    }

    private Tuple<Background, Rule, Scenario> ConvertToChild(IHasLocation hasLocation)
    {
        switch (hasLocation)
        {
            case Gherkin.Ast.Background background:
                var backgroundSteps = background.Steps.Select(ConvertStep).ToList();
                return new Tuple<Background, Rule, Scenario>(new Background(
                    ConvertLocation(background.Location),
                    background.Keyword,
                    CucumberMessagesDefaults.UseDefault(background.Name, CucumberMessagesDefaults.DefaultName),
                    CucumberMessagesDefaults.UseDefault(background.Description, CucumberMessagesDefaults.DefaultDescription),
                    backgroundSteps,
                    idGenerator.GetNewId()
                ), null, null);
            case Ast.Scenario scenario:
                var steps = scenario.Steps.Select(ConvertStep).ToList();
                var examples = scenario.Examples.Select(ConvertExamples).ToList();
                var tags = scenario.Tags.Select(ConvertTag).ToList();
                return new Tuple<Background, Rule, Scenario>(null, null, new Scenario(
                    ConvertLocation(scenario.Location),
                    tags,
                    scenario.Keyword,
                    CucumberMessagesDefaults.UseDefault(scenario.Name, CucumberMessagesDefaults.DefaultName),
                    CucumberMessagesDefaults.UseDefault(scenario.Description, CucumberMessagesDefaults.DefaultDescription),
                    steps,
                    examples,
                    idGenerator.GetNewId()
                ));
            case Ast.Rule rule:
                {
                    var ruleChildren = rule.Children.Select(ConvertToRuleChild).ToList();
                    var ruleTags = rule.Tags.Select(ConvertTag).ToList();
                    return new Tuple<Background, Rule, Scenario>(null, new Rule(
                        ConvertLocation(rule.Location),
                        ruleTags,
                        rule.Keyword,
                        CucumberMessagesDefaults.UseDefault(rule.Name, CucumberMessagesDefaults.DefaultName),
                        CucumberMessagesDefaults.UseDefault(rule.Description, CucumberMessagesDefaults.DefaultDescription),
                        ruleChildren,
                        idGenerator.GetNewId()
                    ), null);
                }
            default:
                throw new NotImplementedException();
        }

    }

    private Examples ConvertExamples(Ast.Examples examples)
    {
        var header = ConvertTableHeader(examples);
        var body = ConvertToTableBody(examples);
        var tags = examples.Tags.Select(ConvertTag).ToList();
        return new Examples(
            ConvertLocation(examples.Location),
            tags,
            examples.Keyword,
            CucumberMessagesDefaults.UseDefault(examples.Name, CucumberMessagesDefaults.DefaultName),
            CucumberMessagesDefaults.UseDefault(examples.Description, CucumberMessagesDefaults.DefaultDescription),
            header,
            body,
            idGenerator.GetNewId()
        );
    }

    private List<TableRow> ConvertToTableBody(Ast.Examples examples)
    {
        if (examples.TableBody == null)
            return new List<TableRow>();

        return ConvertToTableRow(examples.TableBody);
    }

    private List<TableRow> ConvertToTableRow(IEnumerable<Gherkin.Ast.TableRow> rows)
    {
        return rows.Select(b =>
            new TableRow
            (
                ConvertLocation(b.Location),
                b.Cells.Select(ConvertCell).ToList(),
                idGenerator.GetNewId()
           )).ToList();
    }

    private TableRow ConvertTableHeader(Ast.Examples examples)
    {
        if (examples.TableHeader == null)
            return null;

        return new TableRow
        (
            ConvertLocation(examples.TableHeader.Location),
            examples.TableHeader.Cells.Select(ConvertCell).ToList(),
            idGenerator.GetNewId()
        );
    }

    private Tag ConvertTag(Ast.Tag tag)
    {
        return new Tag
        (
            ConvertLocation(tag.Location),
            tag.Name,
            idGenerator.GetNewId()

        );
    }

    private TableCell ConvertCell(Ast.TableCell c)
    {
        return new TableCell(
            ConvertLocation(c.Location),
            CucumberMessagesDefaults.UseDefault(c.Value, CucumberMessagesDefaults.DefaultCellValue)
        );
    }

    private Step ConvertStep(Ast.Step step)
    {
        DataTable dataTable = null;
        if (step.Argument is Gherkin.Ast.DataTable astDataTable)
        {
            var rows = ConvertToTableRow(astDataTable.Rows);
            dataTable = new DataTable(
                ConvertLocation(astDataTable.Location), 
                rows
            );
        }

        DocString docString = null;
        if (step.Argument is Gherkin.Ast.DocString astDocString)
        {
            docString = new DocString(
                ConvertLocation(astDocString.Location),
                astDocString.ContentType,
                astDocString.Content,
                astDocString.Delimiter ?? "\"\"\"" //TODO: store DocString delimiter in Gherkin AST
            );
        }

        return new Step(
            ConvertLocation(step.Location),
            step.Keyword,
            ConvertStepKeywordType(step.KeywordType),
            step.Text,
            docString,
            dataTable,
            idGenerator.GetNewId()
        );
    }

    private Io.Cucumber.Messages.Types.StepKeywordType ConvertStepKeywordType(StepKeywordType keywordType)
    {
        return keywordType switch
        {
            StepKeywordType.Context => Io.Cucumber.Messages.Types.StepKeywordType.CONTEXT,
            StepKeywordType.Action => Io.Cucumber.Messages.Types.StepKeywordType.ACTION,
            StepKeywordType.Outcome => Io.Cucumber.Messages.Types.StepKeywordType.OUTCOME,
            StepKeywordType.Conjunction => Io.Cucumber.Messages.Types.StepKeywordType.CONJUNCTION,
            _ => Io.Cucumber.Messages.Types.StepKeywordType.UNKNOWN
        };
    }
}