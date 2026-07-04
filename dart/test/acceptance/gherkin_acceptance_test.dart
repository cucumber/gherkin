import 'dart:collection';
import 'dart:convert';
import 'dart:io';

import 'package:cucumber_gherkin/cucumber_gherkin_io.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:test/test.dart';

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

/// Recursively sort every map by key so key-order differences don't matter.
///
/// Also applies two normalizations to make cross-platform comparison fair:
/// 1. Empty strings are stripped: proto3 JSON serialization omits zero-value
///    string fields, so both sides must be normalized the same way.
/// 2. CRLF (\r\n) is collapsed to LF (\n): some fixtures have intentional
///    mixed line-endings and the reference .ndjson files (generated on Linux)
///    preserve them, but on a Windows checkout `core.autocrlf` rewrites the
///    input feature files, so the verbatim `source.data` cannot be compared
///    byte-for-byte portably. Collapsing CRLF on both sides keeps this suite
///    platform-independent. The byte-exact `source.data` parity check is
///    performed by the Makefile acceptance target (raw `diff`) in CI.
dynamic _sortKeys(dynamic v) {
  if (v is Map<String, dynamic>) {
    final m = SplayTreeMap<String, dynamic>();
    for (final k in v.keys) {
      final val = _sortKeys(v[k]);
      // Skip empty strings (proto3 zero-value omission).
      if (val is String && val.isEmpty) continue;
      m[k] = val;
    }
    return m;
  }
  if (v is List) return v.map(_sortKeys).toList();
  if (v is String) {
    // Normalize CRLF so line-ending differences don't cause spurious failures.
    return v.replaceAll('\r\n', '\n').replaceAll('\r', '\n');
  }
  return v;
}

/// Parse a concatenation of JSON objects into a list of sorted-key objects.
///
/// Reference fixtures are normally NDJSON (one compact object per line), but a
/// few are committed pretty-printed, so a single object can span several lines.
/// This scans by brace depth (ignoring braces inside strings) instead of
/// splitting on newlines, which also makes the result insensitive to how a
/// checkout rewrites line endings (e.g. `core.autocrlf` on Windows).
List<Map<String, dynamic>> _parseNdjson(String ndjson) {
  final objects = <Map<String, dynamic>>[];
  final buffer = StringBuffer();
  var depth = 0;
  var inString = false;
  var escaped = false;

  for (final rune in ndjson.runes) {
    final char = String.fromCharCode(rune);

    if (depth == 0 && char.trim().isEmpty) {
      continue; // Skip whitespace between top-level objects.
    }
    buffer.write(char);

    if (inString) {
      if (escaped) {
        escaped = false;
      } else if (char == r'\') {
        escaped = true;
      } else if (char == '"') {
        inString = false;
      }
      continue;
    }

    switch (char) {
      case '"':
        inString = true;
      case '{':
        depth++;
      case '}':
        depth--;
        if (depth == 0) {
          objects.add(
            _sortKeys(jsonDecode(buffer.toString())) as Map<String, dynamic>,
          );
          buffer.clear();
        }
    }
  }

  return objects;
}

/// Run the Gherkin parser on [relativePath] with the given output toggles.
/// Returns a list of sorted-key JSON objects, one per emitted envelope.
Future<List<Map<String, dynamic>>> _parse(
  String relativePath, {
  required bool source,
  required bool ast,
  required bool pickles,
}) async {
  final parser = GherkinParser(
    includeSource: source,
    includeGherkinDocument: ast,
    includePickles: pickles,
    idGenerator: IncrementingIdGenerator(),
  );
  final envelopes = await parser.parsePath(relativePath).toList();
  return envelopes
      .map(
        (e) =>
            _sortKeys(jsonDecode(messages.envelopeToJsonString(e)))
                as Map<String, dynamic>,
      )
      .toList();
}

/// Fixture basenames (sorted) whose paths end with any of [exts].
List<String> _fixtures(String dir, List<String> exts) {
  final d = Directory(dir);
  if (!d.existsSync()) return [];
  return d
      .listSync()
      .whereType<File>()
      .map((f) => f.path.replaceAll(r'\', '/').split('/').last)
      .where((name) => exts.any(name.endsWith))
      .toList()
    ..sort();
}

/// Assert [actual] and [expected] have the same envelope count and content.
void _compare(
  String label,
  List<Map<String, dynamic>> actual,
  List<Map<String, dynamic>> expected,
) {
  expect(
    actual.length,
    equals(expected.length),
    reason:
        '$label: envelope count mismatch (got ${actual.length}, '
        'expected ${expected.length})',
  );
  for (var i = 0; i < actual.length; i++) {
    expect(
      jsonEncode(actual[i]),
      equals(jsonEncode(expected[i])),
      reason: '$label: envelope $i differs',
    );
  }
}

// ---------------------------------------------------------------------------
// Test groups
// ---------------------------------------------------------------------------

void main() {
  const goodDir = '../testdata/good';
  const badDir = '../testdata/bad';
  const exts = ['.feature', '.feature.md'];

  final goodNames = _fixtures(goodDir, exts);
  final badNames = _fixtures(badDir, exts);

  // -- AST --------------------------------------------------------------------
  group('acceptance/ast', () {
    for (final name in goodNames) {
      test(name, () async {
        final path = '$goodDir/$name';
        final actual = await _parse(
          path,
          source: false,
          ast: true,
          pickles: false,
        );
        final expected = _parseNdjson(
          await File('$path.ast.ndjson').readAsString(),
        );
        _compare(name, actual, expected);
      });
    }
  });

  // -- Pickles ----------------------------------------------------------------
  group('acceptance/pickles', () {
    for (final name in goodNames) {
      test(name, () async {
        final path = '$goodDir/$name';
        final actual = await _parse(
          path,
          source: false,
          ast: false,
          pickles: true,
        );
        final expected = _parseNdjson(
          await File('$path.pickles.ndjson').readAsString(),
        );
        _compare(name, actual, expected);
      });
    }
  });

  // -- Source -----------------------------------------------------------------
  group('acceptance/source', () {
    for (final name in goodNames) {
      test(name, () async {
        final path = '$goodDir/$name';
        final actual = await _parse(
          path,
          source: true,
          ast: false,
          pickles: false,
        );
        final expected = _parseNdjson(
          await File('$path.source.ndjson').readAsString(),
        );
        _compare(name, actual, expected);
      });
    }
  });

  // -- Errors (bad fixtures) --------------------------------------------------
  group('acceptance/errors', () {
    for (final name in badNames) {
      test(name, () async {
        final path = '$badDir/$name';
        final actual = await _parse(
          path,
          source: false,
          ast: true,
          pickles: true,
        );
        final expected = _parseNdjson(
          await File('$path.errors.ndjson').readAsString(),
        );
        _compare(name, actual, expected);
      });
    }
  });
}
