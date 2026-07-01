import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:gherkin/exceptions.dart';
import 'package:gherkin/src/ast/ast_node.dart';
import 'package:gherkin/src/collections/stack.dart';
import 'package:gherkin/src/extensions/int_extensions.dart';
import 'package:gherkin/src/extensions/strings.dart';
import 'package:gherkin/src/extensions/token_type_extension.dart';
import 'package:gherkin/src/language/id_generator.dart';
import 'package:gherkin/src/language/location.dart';
import 'package:gherkin/src/language/token.dart';
import 'package:gherkin/src/language/token_type.dart';
import 'package:gherkin/src/parser/builder.dart';
import 'package:gherkin/src/parser/rule_type.dart';

/// A [Builder] that assembles parser events into a Cucumber Messages
/// [messages.GherkinDocument].
class MessagesGherkinDocumentBuilder
    implements Builder<messages.GherkinDocument> {
  /// Creates a builder that assigns ids using [idGenerator].
  MessagesGherkinDocumentBuilder(this.idGenerator) {
    reset();
  }

  /// The generator used to assign ids to the produced messages.
  final IdGenerator idGenerator;
  final Stack<AstNode> _stack = Stack<AstNode>();
  final List<messages.Comment> _comments = <messages.Comment>[];

  AstNode get _currentNode => _stack.top;

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
    final node = _stack.pop();
    final transformedNode = _transformNode(node);
    _currentNode.add(node.ruleType, transformedNode);
  }

  @override
  void reset() {
    _stack
      ..clear()
      ..push(AstNode(RuleType.none));
    _comments.clear();
  }

  @override
  messages.GherkinDocument get result => _currentNode.singleOrDefault(
    RuleType.gherkinDocument,
    const messages.GherkinDocument(comments: <messages.Comment>[]),
  );

  @override
  void startRule(RuleType ruleType) => _stack.push(AstNode(ruleType));

  dynamic _transformNode(AstNode node) {
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
      // All other rule types are structural/intermediate nodes that are
      // returned unchanged. An exhaustive switch is not possible because
      // RuleType also declares library-private token rule types that cannot
      // be referenced from this library.
      // ignore: no_default_cases
      default:
        return node;
    }
  }

  messages.Step _createStep(AstNode node) {
    final stepLine = node.getToken(TokenType.stepLine)!;
    final dataTables = node.items<messages.DataTable>(RuleType.dataTable);
    final docStrings = node.items<messages.DocString>(RuleType.docString);
    return messages.Step(
      id: idGenerator.newId(),
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
                id: idGenerator.newId(),
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
          _langLocation(row.location),
        );
      }
    }
  }

  messages.Background _createBackground(AstNode node) {
    final backgroundLine = node.getToken(TokenType.backgroundLine)!;
    return messages.Background(
      id: idGenerator.newId(),
      location: _messageLocation(backgroundLine.location),
      keyword: backgroundLine.matchedKeyword,
      name: backgroundLine.matchedText,
      description: _getDescription(node),
      steps: _getSteps(node),
    );
  }

  messages.Scenario _createScenario(AstNode node) {
    final tags = _getTags(node);
    final scenarioNode = node.singleOrNull<AstNode>(RuleType.scenario)!;
    final scenarioLine = scenarioNode.getToken(TokenType.scenarioLine)!;
    return messages.Scenario(
      id: idGenerator.newId(),
      location: _messageLocation(scenarioLine.location),
      tags: tags,
      keyword: scenarioLine.matchedKeyword,
      name: scenarioLine.matchedText,
      description: _getDescription(scenarioNode),
      steps: _getSteps(scenarioNode),
      examples: scenarioNode.items<messages.Examples>(
        RuleType.examplesDefinition,
      ),
    );
  }

  String _getDescription(AstNode node) =>
      node.singleOrDefault<String>(RuleType.description, Strings.empty);

  List<messages.Step> _getSteps(AstNode node) =>
      node.items<messages.Step>(RuleType.step);

  messages.Examples _createExamplesDefinition(AstNode node) {
    final tags = _getTags(node);
    final examplesNode = node.singleOrNull<AstNode>(RuleType.examples)!;
    final examplesLine = examplesNode.getToken(TokenType.examplesLine)!;
    final allRows = examplesNode.singleOrDefault<List<messages.TableRow>>(
      RuleType.examplesTable,
      const <messages.TableRow>[],
    );
    return messages.Examples(
      id: idGenerator.newId(),
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
    final tagsNode = node.singleOrNull<AstNode>(RuleType.tags);
    if (tagsNode == null) {
      return <messages.Tag>[];
    }
    return tagsNode.getTokens(TokenType.tagLine).expand((token) {
      return token.matchedItems.map(
        (tagItem) => messages.Tag(
          id: idGenerator.newId(),
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
    final header = node.singleOrNull<AstNode>(RuleType.featureHeader);
    if (header == null) {
      return null;
    }
    final featureLine = header.getToken(TokenType.featureLine);
    if (featureLine == null || featureLine.matchedGherkinDialect == null) {
      return null;
    }

    final children = <messages.FeatureChild>[];
    final backgrounds = node.items<messages.Background>(RuleType.background);
    if (backgrounds.isNotEmpty) {
      children.add(messages.FeatureChild(background: backgrounds.first));
    }
    for (final scenario in node.items<messages.Scenario>(
      RuleType.scenarioDefinition,
    )) {
      children.add(messages.FeatureChild(scenario: scenario));
    }
    for (final rule in node.items<messages.Rule>(RuleType.rule)) {
      children.add(messages.FeatureChild(rule: rule));
    }

    return messages.Feature(
      location: _messageLocation(featureLine.location),
      tags: _getTags(header),
      language: featureLine.matchedGherkinDialect!.language,
      keyword: featureLine.matchedKeyword,
      name: featureLine.matchedText,
      description: _getDescription(header),
      children: children,
    );
  }

  messages.Rule? _createRule(AstNode node) {
    final header = node.singleOrNull<AstNode>(RuleType.ruleHeader);
    if (header == null) {
      return null;
    }
    final ruleLine = header.getToken(TokenType.ruleLine);
    if (ruleLine == null) {
      return null;
    }

    final children = <messages.RuleChild>[];
    final backgrounds = node.items<messages.Background>(RuleType.background);
    if (backgrounds.isNotEmpty) {
      children.add(messages.RuleChild(background: backgrounds.first));
    }
    for (final scenario in node.items<messages.Scenario>(
      RuleType.scenarioDefinition,
    )) {
      children.add(messages.RuleChild(scenario: scenario));
    }

    // Allocate tag IDs before the rule's own ID so the ID sequence matches
    // the other first-party Gherkin implementations (tags appear before the
    // keyword line in source and therefore receive lower IDs).
    final tags = _getTags(header);

    return messages.Rule(
      id: idGenerator.newId(),
      location: _messageLocation(ruleLine.location),
      tags: tags,
      keyword: ruleLine.matchedKeyword,
      name: ruleLine.matchedText,
      description: _getDescription(header),
      children: children,
    );
  }

  messages.GherkinDocument _createGherkinDocument(AstNode node) {
    final features = node.items<messages.Feature?>(RuleType.feature);
    return messages.GherkinDocument(
      feature:
          features.whereType<messages.Feature>().isEmpty
              ? null
              : features.whereType<messages.Feature>().first,
      comments: List<messages.Comment>.unmodifiable(_comments),
    );
  }

  messages.Location _messageLocation(Location location, [int? column]) {
    return messages.Location(
      line: location.line,
      column: column ?? (location.column.isMin ? null : location.column),
    );
  }

  Location _langLocation(messages.Location location) =>
      Location(location.line, location.column ?? 0);
}
