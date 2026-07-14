import 'package:gherkin/ast.dart';
import 'package:gherkin/extensions.dart';
import 'package:gherkin/language.dart';
import 'package:gherkin/pickles.dart';

class PickleCompiler
{
  final IdGenerator _idGenerator;

  PickleCompiler(this._idGenerator);

  List<Pickle> compile(GherkinDocument gherkinDocument, String uri) {
    var pickles = <Pickle>[];
    var feature = gherkinDocument.feature;
    if (feature.isEmpty) {
      return pickles;
    }

    var language = feature.language;

    compileFeature(pickles, feature, language, uri);
    return pickles;
  }

  void compileFeature(List<Pickle> pickles, Feature feature, String language
      , String uri)
  {
    var tags = feature.tags.toList();
    var featureBackgroundSteps = <Step>[];
    for (var child in feature.children) {
      if (child.background.isNotEmpty) {
        featureBackgroundSteps.addAll(child.background.steps);
      }
      else if (child.rule.isNotEmpty) {
        _compileRule(pickles, child.rule, tags, featureBackgroundSteps, language, uri);
      }
      else {
        var scenario = child.scenario;
        if (scenario.examples.isEmpty) {
          _compileScenario(pickles, scenario, tags, featureBackgroundSteps, language, uri);
        }
        else {
          _compileScenarioOutline(pickles, scenario, tags, featureBackgroundSteps, language, uri);
        }
      }
    }
  }

  void _compileRule(List<Pickle> pickles, Rule rule, List<Tag> tags
      , List<Step> featureBackgroundSteps, String language, String uri)
  {
    final ruleBackgroundSteps = List<Step>.from(featureBackgroundSteps);
    for (var child in rule.children) {
      if (child.background.isNotEmpty) {
        ruleBackgroundSteps.addAll(child.background.steps);
      }
      else {
        var scenario = child.scenario;
        if (scenario.examples.isEmpty) {
          _compileScenario(pickles, scenario, tags, ruleBackgroundSteps, language, uri);
        }
        else {
          _compileScenarioOutline(pickles, scenario, tags, ruleBackgroundSteps, language, uri);
        }
      }
    }
  }

  void _compileScenario(List<Pickle> pickles, Scenario scenario
      , List<Tag> parentTags, List<Step> backgroundSteps, String language
      , String uri)
  {
    final steps = <PickleStep>[];
    if (scenario.steps.isNotEmpty) {
      var lastKeywordType = 'Unknown';
      lastKeywordType = _appendPickleSteps(steps, backgroundSteps, lastKeywordType);
      _appendPickleSteps(steps, scenario.steps, lastKeywordType);
    }

    final scenarioTags = <Tag>[];
    scenarioTags.addAll(parentTags);
    scenarioTags.addAll(scenario.tags);

    final pickleTags = _buildPickleTags(scenarioTags);

    var sourceIds = <String>[scenario.id];
    var pickle = Pickle(
        _idGenerator.newId(),
        uri,
        scenario.location,
        scenario.name,
        language,
        steps,
        pickleTags,
        sourceIds);

    pickles.add(pickle);
  }

  void _compileScenarioOutline(List<Pickle> pickles, Scenario scenario
      , List<Tag> featureTags, List<Step> backgroundSteps, String language
      , String uri) 
  {
    for (final examples in scenario.examples)
    {
      if (examples.tableHeader.isEmpty) {
        continue;
      }
      
      var variableCells = examples.tableHeader.cells;

      for (final valuesRow in examples.tableBody)
      {
        var valueCells = valuesRow.cells;

        var steps = <PickleStep>[];

        if (scenario.steps.isNotEmpty) {
          var lastKeywordType = 'Unknown';
          lastKeywordType = _appendPickleSteps(steps, backgroundSteps, lastKeywordType);
          _appendPickleSteps(steps, scenario.steps, lastKeywordType
              , variableCells: variableCells, valuesRow: valuesRow);
        }

        var tags = <Tag>[];
        tags.addAll(featureTags);
        tags.addAll(scenario.tags);
        tags.addAll(examples.tags);

        var sourceIds = <String>[scenario.id, valuesRow.id];
        final name = _interpolate(scenario.name, variableCells, valueCells);
        final pickleTags = _buildPickleTags(tags);

        var pickle = Pickle(
          _idGenerator.newId(),
          uri,
          valuesRow.location,
          name,
          language,
          steps,
          pickleTags,
          sourceIds);

        pickles.add(pickle);
      }
    }
  }

  String _appendPickleSteps(List<PickleStep> steps, Iterable<Step> sourceSteps
      , String lastKeywordType
      , {Iterable<TableCell> variableCells = const <TableCell>[]
      , TableRow valuesRow = TableRow.empty} )
  {
    for (var step in sourceSteps) {
      var stepKeywordType = step.keywordType.isEmpty
          ? 'Unknown'
          : step.keywordType;
      var pickleStepType = stepKeywordType == 'Conjunction'
          ? lastKeywordType
          : stepKeywordType;
      if (stepKeywordType != 'Conjunction') {
        lastKeywordType = stepKeywordType;
      }
      steps.add(_buildPickleStep(step, variableCells, valuesRow, pickleStepType));
    }
    return lastKeywordType;
  }

  PickleStep _buildPickleStep(Step step
      , [Iterable<TableCell> variableCells = const <TableCell>[]
      , TableRow valuesRow = TableRow.empty
      , String type = 'Unknown'] )
  {
    var valueCells = valuesRow.isEmpty ? <TableCell>[] : valuesRow.cells;
    var stepText = _interpolate(step.text, variableCells
        , valueCells);

    PickleStepArgument argument = PickleStepArgument.empty;

    var dataTable = PickleTable.empty;
    var pickleDocString = PickleDocString.empty;

    if (step.dataTable.isNotEmpty) {
      dataTable = _buildPickleDataTable(step.dataTable, variableCells
          , valueCells);
    }
    if (step.docString.isNotEmpty) {
      pickleDocString = _buildPickleDocString(step.docString
          , variableCells, valueCells);
    }
    if (dataTable.isNotEmpty || pickleDocString.isNotEmpty) {
      argument = PickleStepArgument(dataTable: dataTable
          , docString: pickleDocString);
    }

    var pickleStep = PickleStep(_idGenerator.newId(), stepText, argument
        , type: type);

    pickleStep.astNodeIds.add(step.id);

    if(valuesRow.isNotEmpty) {
      pickleStep.astNodeIds.add(valuesRow.id);
    }

    return pickleStep;
  }

  List<PickleTag> _buildPickleTags(List<Tag> tags) {
    var result = <PickleTag>[];
    for (var tag in tags) {
      result.add(buildPickleTag(tag));
    }
    return result;
  }

  PickleTag buildPickleTag(Tag tag) {
    return PickleTag(tag.name, tag.id);
  }

  PickleTable _buildPickleDataTable(DataTable dataTable
      , Iterable<TableCell> variableCells, Iterable<TableCell> valueCells)
  {
    var rows = dataTable.rows;
    var newRows = <PickleTableRow>[];
    for (var row in rows)
    {
      var cells = row.cells;
      var newCells = <PickleTableCell>[];

      for (var cell in cells)
      {
        final value = _interpolate(cell.value, variableCells, valueCells);
        final pickleTableCell = PickleTableCell(value);
        newCells.add( pickleTableCell );
      }

      final pickleTableRow = PickleTableRow(newCells);

      newRows.add(pickleTableRow);
    }

    final pickleTable = PickleTable(newRows);
    return pickleTable;
  }

  PickleDocString _buildPickleDocString(DocString docString
      , Iterable<TableCell> variableCells, Iterable<TableCell> valueCells)
  {
    final content = _interpolate(docString.content, variableCells, valueCells);
    final mediaType = docString.mediaType.isEmpty
        ? Strings.empty
        : _interpolate(docString.mediaType, variableCells, valueCells);

    return PickleDocString(mediaType, content);
  }

  String _interpolate(String name, Iterable<TableCell> variableCells
      , Iterable<TableCell> valueCells) {
    var col = 0;
    for (var variableCell in variableCells) {
      final valueCell = valueCells.elementAt(col++);
      final header = variableCell.value;
      final value = valueCell.value;
      name = name.replaceAll('<' + header + '>', value);
    }
    return name;
  }
}
