import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// Compiles [gherkinDocument] (loaded from [uri]) into executable pickles.
///
/// Returns an empty list when the document has no feature.
List<messages.Pickle> compilePickles(
  messages.GherkinDocument gherkinDocument,
  String uri,
  String Function() idGenerator,
) {
  final pickles = <messages.Pickle>[];
  final feature = gherkinDocument.feature;
  if (feature == null) {
    return pickles;
  }

  /// Builds pickle steps for [scenario], optionally interpolating from an
  /// examples row. Background steps are never interpolated.
  List<messages.PickleStep> buildSteps(
    List<messages.Step> backgroundSteps,
    messages.Scenario scenario, [
    List<messages.TableCell> variableCells = const <messages.TableCell>[],
    messages.TableRow? valuesRow,
  ]) {
    final steps = <messages.PickleStep>[];
    var lastKeywordType = messages.StepKeywordType.unknown;
    if (scenario.steps.isNotEmpty) {
      lastKeywordType = _appendPickleSteps(
        steps,
        backgroundSteps,
        const <messages.TableCell>[],
        null,
        lastKeywordType,
        idGenerator,
      );
    }
    _appendPickleSteps(
      steps,
      scenario.steps,
      variableCells,
      valuesRow,
      lastKeywordType,
      idGenerator,
    );
    return steps;
  }

  void compileScenario(
    List<messages.Tag> inheritedTags,
    List<messages.Step> backgroundSteps,
    messages.Scenario scenario,
    String language,
  ) {
    // Allocate step IDs before the pickle ID to match acceptance fixtures.
    final steps = buildSteps(backgroundSteps, scenario);
    pickles.add(
      messages.Pickle(
        id: idGenerator(),
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

  void compileScenarioOutline(
    List<messages.Tag> inheritedTags,
    List<messages.Step> backgroundSteps,
    messages.Scenario scenario,
    String language,
  ) {
    for (final examples in scenario.examples) {
      final variableCells = examples.tableHeader?.cells;
      if (variableCells == null) {
        continue;
      }

      for (final valuesRow in examples.tableBody) {
        // Allocate step IDs before the pickle ID to match acceptance fixtures.
        final steps = buildSteps(
          backgroundSteps,
          scenario,
          variableCells,
          valuesRow,
        );
        pickles.add(
          messages.Pickle(
            id: idGenerator(),
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

  void compileScenarioOrOutline(
    List<messages.Tag> inheritedTags,
    List<messages.Step> backgroundSteps,
    messages.Scenario scenario,
    String language,
  ) {
    if (scenario.examples.isEmpty) {
      compileScenario(inheritedTags, backgroundSteps, scenario, language);
    } else {
      compileScenarioOutline(
        inheritedTags,
        backgroundSteps,
        scenario,
        language,
      );
    }
  }

  void compileRule(
    List<messages.Tag> featureTags,
    List<messages.Step> featureBackgroundSteps,
    messages.Rule rule,
    String language,
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
        compileScenarioOrOutline(
          inheritedTags,
          ruleBackgroundSteps,
          child.scenario!,
          language,
        );
      }
    }
  }

  final featureBackgroundSteps = <messages.Step>[];
  for (final child in feature.children) {
    if (child.background != null) {
      featureBackgroundSteps
        ..clear()
        ..addAll(child.background!.steps);
    } else if (child.rule != null) {
      compileRule(
        feature.tags,
        featureBackgroundSteps,
        child.rule!,
        feature.language,
      );
    } else if (child.scenario != null) {
      compileScenarioOrOutline(
        feature.tags,
        featureBackgroundSteps,
        child.scenario!,
        feature.language,
      );
    }
  }
  return pickles;
}

messages.StepKeywordType _appendPickleSteps(
  List<messages.PickleStep> steps,
  Iterable<messages.Step> sourceSteps,
  List<messages.TableCell> variableCells,
  messages.TableRow? valuesRow,
  messages.StepKeywordType lastKeywordType,
  String Function() idGenerator,
) {
  var keywordType = lastKeywordType;
  for (final step in sourceSteps) {
    keywordType = _effectiveKeywordType(step.keywordType, keywordType);
    steps.add(
      _pickleStep(step, variableCells, valuesRow, keywordType, idGenerator),
    );
  }
  return keywordType;
}

messages.PickleStep _pickleStep(
  messages.Step step,
  List<messages.TableCell> variableCells,
  messages.TableRow? valuesRow,
  messages.StepKeywordType keywordType,
  String Function() idGenerator,
) {
  final valueCells = valuesRow?.cells ?? const <messages.TableCell>[];
  final astNodeIds = <String>[step.id];
  if (valuesRow != null) {
    astNodeIds.add(valuesRow.id);
  }
  return messages.PickleStep(
    id: idGenerator(),
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
  final dataTable =
      step.dataTable == null
          ? null
          : messages.PickleTable(
            rows:
                step.dataTable!.rows.map((row) {
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
          );

  final docString =
      step.docString == null
          ? null
          : messages.PickleDocString(
            mediaType:
                step.docString!.mediaType == null
                    ? null
                    : _interpolate(
                      step.docString!.mediaType!,
                      variableCells,
                      valueCells,
                    ),
            content: _interpolate(
              step.docString!.content,
              variableCells,
              valueCells,
            ),
          );

  if (dataTable != null || docString != null) {
    return messages.PickleStepArgument(
      dataTable: dataTable,
      docString: docString,
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
  if (!value.contains('<')) {
    return value;
  }
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

messages.PickleStepType? _pickleStepType(messages.StepKeywordType keywordType) {
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
