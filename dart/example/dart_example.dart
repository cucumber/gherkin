import 'dart:io';

import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:cucumber_gherkin/gherkin.dart';

/// Parses a feature file and prints the names of the compiled pickles.
///
/// Run with:
///
///     dart run example/dart_example.dart ../testdata/good/minimal.feature
Future<void> main(List<String> args) async {
  final path =
      args.isNotEmpty ? args.first : '../testdata/good/minimal.feature';

  final parser =
      (GherkinParser.builder()
            ..includeSource = false
            ..idGenerator = IdGenerator.incrementingGenerator)
          .build();

  final envelopes = await parser.parsePath(path).toList();

  final pickles =
      envelopes
          .map((messages.Envelope e) => e.pickle)
          .whereType<messages.Pickle>();

  for (final pickle in pickles) {
    stdout.writeln('Pickle: ${pickle.name} (${pickle.steps.length} steps)');
  }
}
