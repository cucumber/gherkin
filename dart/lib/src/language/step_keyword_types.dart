import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:cucumber_gherkin/src/language/gherkin_dialect.dart';

/// Shared step-keyword-to-[messages.StepKeywordType] mapping for the token
/// matchers.
///
/// Both the plain (`.feature`) and Markdown (`.feature.md`) matchers classify
/// step keywords identically: `Given` keywords are [messages.StepKeywordType.context],
/// `When` keywords are [messages.StepKeywordType.action], `Then` keywords are
/// [messages.StepKeywordType.outcome], and both `And` and `But` keywords are
/// [messages.StepKeywordType.conjunction]. A single keyword may map to more
/// than one type (for example a dialect that reuses one word across step
/// kinds), which is why the mapping stores a list per keyword.
///
/// The matchers differ only in how they treat keywords that are *not* mapped:
/// the plain matcher reports [messages.StepKeywordType.unknown], while the
/// Markdown matcher reports `null`. [keywordTypeOrNull] exposes that shared
/// three-way result (mapped / ambiguous / absent) so each matcher can apply its
/// own policy for the absent case.
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
