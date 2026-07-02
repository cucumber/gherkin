import 'dart:convert';
import 'dart:io';

/// Generates `lib/src/language/dialects_builtin.g.dart` from
/// `gherkin-languages.json`, embedding every Gherkin dialect as const Dart
/// source.
///
/// This mirrors the Go implementation's `dialects_builtin.go`, removing the
/// need to load the dialect JSON as a runtime asset.
///
/// Usage:
///
/// ```
/// dart run bin/gherkin_generate_dialects.dart <input-json> <output-dart>
/// ```
void main(List<String> args) {
  if (args.length != 2) {
    stderr.writeln(
      'Usage: dart run bin/gherkin_generate_dialects.dart '
      '<input-json> <output-dart>',
    );
    exitCode = 64; // EX_USAGE
    return;
  }

  final inputPath = args[0];
  final outputPath = args[1];

  final json = jsonDecode(File(inputPath).readAsStringSync());
  final map = (json as Map<String, dynamic>);

  // Sort entries by language tag so the generated output is deterministic.
  final tags = map.keys.toList()..sort();

  final buffer = StringBuffer();
  buffer.writeln('// GENERATED CODE - DO NOT MODIFY BY HAND');
  buffer.writeln('// ignore_for_file: type=lint');
  buffer.writeln();
  buffer.writeln(
    "import 'package:cucumber_gherkin/src/language/"
    "gherkin_language_keywords.dart';",
  );
  buffer.writeln();
  buffer.writeln(
    '/// The Gherkin dialects bundled with this package, keyed by',
  );
  buffer.writeln('/// language tag, embedded from `gherkin-languages.json`.');
  buffer.writeln(
    'const Map<String, GherkinLanguageKeywords> builtinDialects = {',
  );
  for (final tag in tags) {
    final entry = map[tag] as Map<String, dynamic>;
    buffer.writeln('  ${_string(tag)}: GherkinLanguageKeywords(');
    buffer.writeln('    ${_string(entry['name'] as String)},');
    buffer.writeln('    ${_string(entry['native'] as String)},');
    for (final key in const [
      'feature',
      'rule',
      'background',
      'scenario',
      'scenarioOutline',
      'examples',
      'given',
      'when',
      'then',
      'and',
      'but',
    ]) {
      buffer.write(_list(entry[key] as List<dynamic>));
    }
    buffer.writeln('  ),');
  }
  buffer.writeln('};');

  File(outputPath).writeAsStringSync(buffer.toString(), encoding: utf8);

  // Format the generated file so `dart format --set-exit-if-changed` stays
  // clean and regeneration is byte-stable. Running `dart format` here means the
  // generator's line layout does not need to replicate the formatter's exact
  // wrapping rules.
  final formatResult = Process.runSync(
    'dart',
    ['format', outputPath],
    stdoutEncoding: utf8,
    stderrEncoding: utf8,
  );
  if (formatResult.exitCode != 0) {
    stderr.writeln('dart format failed:\n${formatResult.stderr}');
    exitCode = formatResult.exitCode;
    return;
  }

  stdout.writeln('Embedded ${tags.length} dialects into $outputPath.');
}

/// Renders a `List<String>` argument, one element per line, matching the layout
/// `dart format` produces for a multi-line list literal.
String _list(List<dynamic> values) {
  if (values.isEmpty) {
    return '    [],\n';
  }
  final buffer = StringBuffer('    [\n');
  for (final value in values) {
    buffer.writeln('      ${_string(value as String)},');
  }
  buffer.writeln('    ],');
  return buffer.toString();
}

/// Produces a valid single-line Dart string literal for [value].
///
/// Uses [jsonEncode] for the base escaping (quotes, backslashes, control
/// characters) and additionally escapes `$` so it is not interpreted as Dart
/// string interpolation. Non-ASCII characters are preserved as literal UTF-8.
String _string(String value) {
  final encoded = jsonEncode(value);
  return encoded.replaceAll(r'$', r'\$');
}
