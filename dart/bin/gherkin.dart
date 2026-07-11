import 'dart:io';

import 'package:cucumber_gherkin/src/gherkin/gherkin_parser.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

Future<void> main(List<String> args) async {
  var includeSource = true;
  var includeAst = true;
  var includePickles = true;
  String Function()? idGenerator;
  var nextId = 0;
  final paths = <String>[];

  for (final arg in args) {
    switch (arg) {
      case '--no-source':
        includeSource = false;
      case '--no-ast':
        includeAst = false;
      case '--no-pickles':
        includePickles = false;
      case '--predictable-ids':
        idGenerator = () => (nextId++).toString();
      default:
        paths.add(arg);
    }
  }

  final envelopes = Stream.fromIterable(paths).asyncExpand((path) async* {
    yield* parseFeature(
      await File(path).readAsString(),
      path,
      includeSource: includeSource,
      includeGherkinDocument: includeAst,
      includePickles: includePickles,
      idGenerator: idGenerator,
    );
  });
  await messages.encodeNdjsonEnvelopes(envelopes).forEach(stdout.write);
}
