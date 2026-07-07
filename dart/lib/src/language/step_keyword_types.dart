import 'package:cucumber_gherkin/src/language/gherkin_dialect.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

/// Shared step-keyword-to-[messages.StepKeywordType] mapping for the token
/// matchers.
///
/// The plain matcher classifies `Given` as [messages.StepKeywordType.context],
/// `When` as [messages.StepKeywordType.action], `Then` as
/// [messages.StepKeywordType.outcome], and `And`/`But` as
/// [messages.StepKeywordType.conjunction]. A keyword may map to more than one
/// type (e.g. a dialect reusing one word across step kinds), so the mapping
/// stores a list per keyword.
mixin StepKeywordTypes {
  final Map<String, List<messages.StepKeywordType>> _keywordTypesMap =
      <String, List<messages.StepKeywordType>>{};

  /// Rebuilds the keyword-type mappings from [dialect].
  ///
  /// Call this whenever the active dialect changes (including on `reset()`).
  void initializeKeywordTypes(GherkinDialect dialect) {
    _keywordTypesMap.clear();
    _addKeywordTypeMappings(
      dialect.givenStepKeywords,
      messages.StepKeywordType.context,
    );
    _addKeywordTypeMappings(
      dialect.whenStepKeywords,
      messages.StepKeywordType.action,
    );
    _addKeywordTypeMappings(
      dialect.thenStepKeywords,
      messages.StepKeywordType.outcome,
    );
    _addKeywordTypeMappings(
      dialect.andStepKeywords,
      messages.StepKeywordType.conjunction,
    );
    _addKeywordTypeMappings(
      dialect.butStepKeywords,
      messages.StepKeywordType.conjunction,
    );
  }

  void _addKeywordTypeMappings(
    Iterable<String> keywords,
    messages.StepKeywordType keywordType,
  ) {
    for (final keyword in keywords) {
      _keywordTypesMap
          .putIfAbsent(keyword, () => <messages.StepKeywordType>[])
          .add(keywordType);
    }
  }

  /// Resolves the step keyword type for [keyword], or `null` when the keyword
  /// is not a known step keyword in the active dialect.
  ///
  /// A keyword that maps to exactly one type returns that type; a keyword that
  /// maps to more than one type is ambiguous and returns
  /// [messages.StepKeywordType.unknown]. Callers decide how to treat the
  /// absent (`null`) case.
  messages.StepKeywordType? keywordTypeOrNull(String keyword) {
    final keywordTypes = _keywordTypesMap[keyword];
    if (keywordTypes == null) {
      return null;
    }
    if (keywordTypes.length != 1) {
      return messages.StepKeywordType.unknown;
    }
    return keywordTypes.single;
  }
}
