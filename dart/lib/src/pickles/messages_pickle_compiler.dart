import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:cucumber_gherkin/src/language/id_generator.dart';

/// Compiles a [messages.GherkinDocument] into the list of executable
/// [messages.Pickle]s it describes.
class MessagesPickleCompiler {
  /// Creates a compiler that assigns ids using [_idGenerator].
  MessagesPickleCompiler(this._idGenerator);

  final IdGenerator _idGenerator;

  /// Compiles [gherkinDocument] (loaded from [uri]) into pickles.
  ///
  /// Returns an empty list when the document has no feature.
  List<messages.Pickle> compile(
    messages.GherkinDocument gherkinDocument,
    String uri,
  ) {
    final pickles = <messages.Pickle>[];
    final feature = gherkinDocument.feature;
    if (feature == null) {
      return pickles;
    }

    final featureBackgroundSteps = <messages.Step>[];
    for (final child in feature.children) {
      if (child.background != null) {
        featureBackgroundSteps
          ..clear()
          ..addAll(child.background!.steps);
      } else if (child.rule != null) {
        _compileRule(
          pickles,
          feature.tags,
          featureBackgroundSteps,
          child.rule!,
          feature.language,
          uri,
        );
      } else if (child.scenario != null) {
        final scenario = child.scenario!;
        if (scenario.examples.isEmpty) {
          _compileScenario(
            pickles,
            feature.tags,
            featureBackgroundSteps,
            scenario,
            feature.language,
            uri,
          );
        } else {
          _compileScenarioOutline(
            pickles,
            feature.tags,
            featureBackgroundSteps,
            scenario,
            feature.language,
            uri,
          );
        }
      }
    }
    return pickles;
  }

  void _compileRule(
    List<messages.Pickle> pickles,
    List<messages.Tag> featureTags,
    List<messages.Step> featureBackgroundSteps,
    messages.Rule rule,
    String language,
    String uri,
  ) {
    final ruleBackgroundSteps = List<messages.Step>.from(
      featureBackgroundSteps,
    );
    final inheritedTags = <messages.Tag>[...featureTags, ...rule.tags];
    for (final child in rule.children) {
      if (child.background != null) {
        ruleBackgroundSteps
          ..clear()
          ..addAll(featureBackgroundSteps)
          ..addAll(child.background!.steps);
      } else if (child.scenario != null) {
        final scenario = child.scenario!;
        if (scenario.examples.isEmpty) {
          _compileScenario(
            pickles,
            inheritedTags,
            ruleBackgroundSteps,
            scenario,
            language,
            uri,
          );
        } else {
          _compileScenarioOutline(
            pickles,
            inheritedTags,
            ruleBackgroundSteps,
            scenario,
            language,
            uri,
          );
        }
      }
    }
  }

  void _compileScenario(
    List<messages.Pickle> pickles,
    List<messages.Tag> inheritedTags,
    List<messages.Step> backgroundSteps,
    messages.Scenario scenario,
    String language,
    String uri,
  ) {
    var lastKeywordType = messages.StepKeywordType.unknown;
    final steps = <messages.PickleStep>[];

    if (scenario.steps.isNotEmpty) {
      for (final step in backgroundSteps) {
        lastKeywordType = _effectiveKeywordType(
          step.keywordType,
          lastKeywordType,
        );
        steps.add(
          _pickleStep(
            step,
            const <messages.TableCell>[],
            null,
            lastKeywordType,
          ),
        );
      }
    }

    for (final step in scenario.steps) {
      lastKeywordType = _effectiveKeywordType(
        step.keywordType,
        lastKeywordType,
      );
      steps.add(
        _pickleStep(step, const <messages.TableCell>[], null, lastKeywordType),
      );
    }

    pickles.add(
      messages.Pickle(
        id: _idGenerator.newId(),
        uri: uri,
        location: scenario.location,
        name: scenario.name,
        language: language,
        steps: steps,
        tags: _pickleTags(<messages.Tag>[...inheritedTags, ...scenario.tags]),
        astNodeIds: <String>[scenario.id],
      ),
    );
  }

  void _compileScenarioOutline(
    List<messages.Pickle> pickles,
    List<messages.Tag> inheritedTags,
    List<messages.Step> backgroundSteps,
    messages.Scenario scenario,
    String language,
    String uri,
  ) {
    for (final examples in scenario.examples) {
      final variableCells = examples.tableHeader?.cells;
      if (variableCells == null) {
        continue;
      }

      for (final valuesRow in examples.tableBody) {
        var lastKeywordType = messages.StepKeywordType.unknown;
        final steps = <messages.PickleStep>[];
        if (scenario.steps.isNotEmpty) {
          for (final step in backgroundSteps) {
            lastKeywordType = _effectiveKeywordType(
              step.keywordType,
              lastKeywordType,
            );
            // Background steps are interpolated but do NOT reference the
            // specific example row â€” they belong to the background node only.
            steps.add(
              _pickleStep(
                step,
                variableCells,
                valuesRow,
                lastKeywordType,
                trackRowInAstNodeIds: false,
              ),
            );
          }
        }

        for (final step in scenario.steps) {
          lastKeywordType = _effectiveKeywordType(
            step.keywordType,
            lastKeywordType,
          );
          steps.add(
            _pickleStep(step, variableCells, valuesRow, lastKeywordType),
          );
        }

        pickles.add(
          messages.Pickle(
            id: _idGenerator.newId(),
            uri: uri,
            location: valuesRow.location,
            name: _interpolate(scenario.name, variableCells, valuesRow.cells),
            language: language,
            steps: steps,
            tags: _pickleTags(<messages.Tag>[
              ...inheritedTags,
              ...scenario.tags,
              ...examples.tags,
            ]),
            astNodeIds: <String>[scenario.id, valuesRow.id],
          ),
        );
      }
    }
  }

  messages.PickleStep _pickleStep(
    messages.Step step,
    List<messages.TableCell> variableCells,
    messages.TableRow? valuesRow,
    messages.StepKeywordType keywordType, {
    bool trackRowInAstNodeIds = true,
  }) {
    final valueCells = valuesRow?.cells ?? const <messages.TableCell>[];
    final astNodeIds = <String>[step.id];
    if (valuesRow != null && trackRowInAstNodeIds) {
      astNodeIds.add(valuesRow.id);
    }
    return messages.PickleStep(
      id: _idGenerator.newId(),
      text: _interpolate(step.text, variableCells, valueCells),
      type: _pickleStepType(keywordType),
      argument: _pickleStepArgument(step, variableCells, valueCells),
      astNodeIds: astNodeIds,
    );
  }

  messages.PickleStepArgument? _pickleStepArgument(
    messages.Step step,
    List<messages.TableCell> variableCells,
    List<messages.TableCell> valueCells,
  ) {
    final dataTable = step.dataTable;
    if (dataTable != null) {
      return messages.PickleStepArgument(
        dataTable: messages.PickleTable(
          rows:
              dataTable.rows.map((row) {
                return messages.PickleTableRow(
                  cells:
                      row.cells.map((cell) {
                        return messages.PickleTableCell(
                          value: _interpolate(
                            cell.value,
                            variableCells,
                            valueCells,
                          ),
                        );
                      }).toList(),
                );
              }).toList(),
        ),
      );
    }

    final docString = step.docString;
    if (docString != null) {
      return messages.PickleStepArgument(
        docString: messages.PickleDocString(
          mediaType:
              docString.mediaType == null
                  ? null
                  : _interpolate(
                    docString.mediaType!,
                    variableCells,
                    valueCells,
                  ),
          content: _interpolate(docString.content, variableCells, valueCells),
        ),
      );
    }
    return null;
  }

  List<messages.PickleTag> _pickleTags(List<messages.Tag> tags) =>
      tags
          .map((tag) => messages.PickleTag(name: tag.name, astNodeId: tag.id))
          .toList();

  String _interpolate(
    String value,
    List<messages.TableCell> variableCells,
    List<messages.TableCell> valueCells,
  ) {
    var result = value;
    for (var i = 0; i < variableCells.length; i++) {
      final pattern = '<${variableCells[i].value}>';
      result = result.replaceAll(pattern, valueCells[i].value);
    }
    return result;
  }

  messages.StepKeywordType _effectiveKeywordType(
    messages.StepKeywordType? current,
    messages.StepKeywordType previous,
  ) {
    if (current == null || current == messages.StepKeywordType.conjunction) {
      return previous;
    }
    return current;
  }

  messages.PickleStepType? _pickleStepType(
    messages.StepKeywordType keywordType,
  ) {
    switch (keywordType) {
      case messages.StepKeywordType.context:
        return messages.PickleStepType.context;
      case messages.StepKeywordType.action:
        return messages.PickleStepType.action;
      case messages.StepKeywordType.outcome:
        return messages.PickleStepType.outcome;
      case messages.StepKeywordType.unknown:
        return messages.PickleStepType.unknown;
      case messages.StepKeywordType.conjunction:
        return null;
    }
  }
}
