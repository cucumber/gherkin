import 'dart:collection';

import 'package:cucumber_gherkin/src/ast/ast_node.dart';
import 'package:cucumber_gherkin/src/exceptions/exceptions.dart';
import 'package:cucumber_gherkin/src/extensions/strings.dart';
import 'package:cucumber_gherkin/src/extensions/token_type_extension.dart';
import 'package:cucumber_gherkin/src/language/location.dart';
import 'package:cucumber_gherkin/src/language/token.dart';
import 'package:cucumber_gherkin/src/parser/builder.dart';
import 'package:cucumber_gherkin/src/parser/parser.g.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// A [Builder] that assembles parser events into a Cucumber Messages
/// [messages.GherkinDocument].
class MessagesGherkinDocumentBuilder
    implements Builder<messages.GherkinDocument> {
  /// Creates a builder that assigns ids using [_idGenerator].
  MessagesGherkinDocumentBuilder(this._idGenerator) {
    reset();
  }

  final String Function() _idGenerator;
  // LIFO stack of rules being reduced. The top is kept at the queue's end, so
  // `addLast`/`removeLast`/`last` are O(1) push/pop/peek.
  final ListQueue<AstNode> _stack = ListQueue<AstNode>();
  final List<messages.Comment> _comments = <messages.Comment>[];

  AstNode get _currentNode => _stack.last;

  @override
  void build(Token token) {
    if (token.matchedType == TokenType.comment) {
      _comments.add(
        messages.Comment(
          location: _messageLocation(token.location),
          text: token.matchedText,
        ),
      );
    } else {
      _currentNode.add(token.matchedType.toRuleType(), token);
    }
  }

  @override
  void endRule(RuleType ruleType) {
    final node = _stack.removeLast();
    final transformedNode = _transformNode(node);
    _currentNode.add(node.ruleType, transformedNode);
  }

  @override
  void reset() {
    _stack
      ..clear()
      ..addLast(AstNode(RuleType.none));
    _comments.clear();
  }

  @override
  messages.GherkinDocument get result =>
      _currentNode.getSingle<messages.GherkinDocument>(
        RuleType.gherkinDocument,
      ) ??
      const messages.GherkinDocument(comments: <messages.Comment>[]);

  @override
  void startRule(RuleType ruleType) => _stack.addLast(AstNode(ruleType));

  Object? _transformNode(AstNode node) {
    switch (node.ruleType) {
      case RuleType.step:
        return _createStep(node);
      case RuleType.docString:
        return _createDocString(node);
      case RuleType.dataTable:
        return _createDataTable(node);
      case RuleType.background:
        return _createBackground(node);
      case RuleType.scenarioDefinition:
        return _createScenario(node);
      case RuleType.examplesDefinition:
        return _createExamplesDefinition(node);
      case RuleType.examplesTable:
        return _getTableRows(node);
      case RuleType.description:
        return _createDescription(node);
      case RuleType.feature:
        return _createFeature(node);
      case RuleType.rule:
        return _createRule(node);
      case RuleType.gherkinDocument:
        return _createGherkinDocument(node);
      // Keep this exhaustive so new rule types must be handled explicitly.
      case RuleType.none:
      case RuleType.eof:
      case RuleType.empty:
      case RuleType.comment:
      case RuleType.tagLine:
      case RuleType.featureLine:
      case RuleType.ruleLine:
      case RuleType.backgroundLine:
      case RuleType.scenarioLine:
      case RuleType.examplesLine:
      case RuleType.stepLine:
      case RuleType.docStringSeparator:
      case RuleType.tableRow:
      case RuleType.language:
      case RuleType.other:
      case RuleType.featureHeader:
      case RuleType.ruleHeader:
      case RuleType.scenario:
      case RuleType.examples:
      case RuleType.stepArg:
      case RuleType.dataTableAndMaybeDocString:
      case RuleType.docStringAndMaybeDataTable:
      case RuleType.tags:
      case RuleType.descriptionHelper:
        return node;
    }
  }

  messages.Step _createStep(AstNode node) {
    final stepLine = node.getToken(TokenType.stepLine)!;
    final dataTables = node.getItems<messages.DataTable>(RuleType.dataTable);
    final docStrings = node.getItems<messages.DocString>(RuleType.docString);
    return messages.Step(
      id: _idGenerator(),
      location: _messageLocation(stepLine.location),
      keyword: stepLine.matchedKeyword,
      keywordType: stepLine.matchedKeywordType,
      text: stepLine.matchedText,
      dataTable: dataTables.isEmpty ? null : dataTables.first,
      docString: docStrings.isEmpty ? null : docStrings.first,
    );
  }

  messages.DocString _createDocString(AstNode node) {
    final separatorToken = node.getTokens(TokenType.docStringSeparator).first;
    final mediaType =
        separatorToken.matchedText.isEmpty ? null : separatorToken.matchedText;
    final lineTokens = node.getTokens(TokenType.other);
    final content = lineTokens.map((token) => token.matchedText).join('\n');
    return messages.DocString(
      location: _messageLocation(separatorToken.location),
      mediaType: mediaType,
      content: content,
      delimiter: separatorToken.matchedKeyword,
    );
  }

  messages.DataTable _createDataTable(AstNode node) {
    final rows = _getTableRows(node);
    return messages.DataTable(location: rows.first.location, rows: rows);
  }

  List<messages.TableRow> _getTableRows(AstNode node) {
    final tokens = node.getTokens(TokenType.tableRow);
    final rows =
        tokens
            .map(
              (token) => messages.TableRow(
                id: _idGenerator(),
                location: _messageLocation(token.location),
                cells: _getCells(token),
              ),
            )
            .toList();
    _checkCellCountConsistency(rows);
    return rows;
  }

  List<messages.TableCell> _getCells(Token token) =>
      token.matchedItems
          .map(
            (item) => messages.TableCell(
              location: _messageLocation(token.location, item.column),
              value: item.text,
            ),
          )
          .toList();

  void _checkCellCountConsistency(List<messages.TableRow> rows) {
    if (rows.isEmpty) {
      return;
    }
    final cellCount = rows.first.cells.length;
    for (final row in rows) {
      if (row.cells.length != cellCount) {
        throw AstBuilderException(
          'inconsistent cell count within the table',
          Location(row.location.line, row.location.column ?? 0),
        );
      }
    }
  }

  messages.Background _createBackground(AstNode node) {
    final backgroundLine = node.getToken(TokenType.backgroundLine)!;
    return messages.Background(
      id: _idGenerator(),
      location: _messageLocation(backgroundLine.location),
      keyword: backgroundLine.matchedKeyword,
      name: backgroundLine.matchedText,
      description: _getDescription(node),
      steps: _getSteps(node),
    );
  }

  messages.Scenario _createScenario(AstNode node) {
    final tags = _getTags(node);
    final scenarioNode = node.getSingle<AstNode>(RuleType.scenario)!;
    final scenarioLine = scenarioNode.getToken(TokenType.scenarioLine)!;
    return messages.Scenario(
      id: _idGenerator(),
      location: _messageLocation(scenarioLine.location),
      tags: tags,
      keyword: scenarioLine.matchedKeyword,
      name: scenarioLine.matchedText,
      description: _getDescription(scenarioNode),
      steps: _getSteps(scenarioNode),
      examples: scenarioNode.getItems<messages.Examples>(
        RuleType.examplesDefinition,
      ),
    );
  }

  String _getDescription(AstNode node) =>
      node.getSingle<String>(RuleType.description) ?? '';

  List<messages.Step> _getSteps(AstNode node) =>
      node.getItems<messages.Step>(RuleType.step);

  messages.Examples _createExamplesDefinition(AstNode node) {
    final tags = _getTags(node);
    final examplesNode = node.getSingle<AstNode>(RuleType.examples)!;
    final examplesLine = examplesNode.getToken(TokenType.examplesLine)!;
    final allRows =
        examplesNode.getSingle<List<messages.TableRow>>(
          RuleType.examplesTable,
        ) ??
        const <messages.TableRow>[];
    return messages.Examples(
      id: _idGenerator(),
      location: _messageLocation(examplesLine.location),
      tags: tags,
      keyword: examplesLine.matchedKeyword,
      name: examplesLine.matchedText,
      description: _getDescription(examplesNode),
      tableHeader: allRows.isEmpty ? null : allRows.first,
      tableBody:
          allRows.isEmpty ? <messages.TableRow>[] : allRows.skip(1).toList(),
    );
  }

  List<messages.Tag> _getTags(AstNode node) {
    final tagsNode = node.getSingle<AstNode>(RuleType.tags);
    if (tagsNode == null) {
      return <messages.Tag>[];
    }
    return tagsNode.getTokens(TokenType.tagLine).expand((token) {
      return token.matchedItems.map(
        (tagItem) => messages.Tag(
          id: _idGenerator(),
          location: _messageLocation(token.location, tagItem.column),
          name: tagItem.text,
        ),
      );
    }).toList();
  }

  String _createDescription(AstNode node) {
    final lineTokens = node.getTokens(TokenType.other).toList();
    while (lineTokens.isNotEmpty &&
        lineTokens.last.matchedText.isEmptyOrWhiteSpace) {
      lineTokens.removeLast();
    }
    return lineTokens.map((token) => token.matchedText).join('\n');
  }

  messages.Feature? _createFeature(AstNode node) {
    final header = node.getSingle<AstNode>(RuleType.featureHeader);
    if (header == null) {
      return null;
    }
    final featureLine = header.getToken(TokenType.featureLine);
    final language = featureLine?.matchedLanguage;
    if (featureLine == null || language == null) {
      return null;
    }

    final children = <messages.FeatureChild>[];
    final backgrounds = node.getItems<messages.Background>(RuleType.background);
    if (backgrounds.isNotEmpty) {
      children.add(messages.FeatureChild(background: backgrounds.first));
    }
    for (final scenario in node.getItems<messages.Scenario>(
      RuleType.scenarioDefinition,
    )) {
      children.add(messages.FeatureChild(scenario: scenario));
    }
    for (final rule in node.getItems<messages.Rule>(RuleType.rule)) {
      children.add(messages.FeatureChild(rule: rule));
    }

    return messages.Feature(
      location: _messageLocation(featureLine.location),
      tags: _getTags(header),
      language: language,
      keyword: featureLine.matchedKeyword,
      name: featureLine.matchedText,
      description: _getDescription(header),
      children: children,
    );
  }

  messages.Rule? _createRule(AstNode node) {
    final header = node.getSingle<AstNode>(RuleType.ruleHeader);
    if (header == null) {
      return null;
    }
    final ruleLine = header.getToken(TokenType.ruleLine);
    if (ruleLine == null) {
      return null;
    }

    final children = <messages.RuleChild>[];
    final backgrounds = node.getItems<messages.Background>(RuleType.background);
    if (backgrounds.isNotEmpty) {
      children.add(messages.RuleChild(background: backgrounds.first));
    }
    for (final scenario in node.getItems<messages.Scenario>(
      RuleType.scenarioDefinition,
    )) {
      children.add(messages.RuleChild(scenario: scenario));
    }

    // Allocate tag IDs before the rule's own ID: tags precede the keyword line
    // in source, so get lower IDs.
    final tags = _getTags(header);

    return messages.Rule(
      id: _idGenerator(),
      location: _messageLocation(ruleLine.location),
      tags: tags,
      keyword: ruleLine.matchedKeyword,
      name: ruleLine.matchedText,
      description: _getDescription(header),
      children: children,
    );
  }

  messages.GherkinDocument _createGherkinDocument(AstNode node) {
    final features =
        node
            .getItems<messages.Feature?>(RuleType.feature)
            .whereType<messages.Feature>();
    return messages.GherkinDocument(
      feature: features.isEmpty ? null : features.first,
      comments: List<messages.Comment>.unmodifiable(_comments),
    );
  }

  messages.Location _messageLocation(Location location, [int? column]) {
    return messages.Location(
      line: location.line,
      column: column ?? (location.hasColumn ? location.column : null),
    );
  }
}
