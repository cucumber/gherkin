import 'dart:io';

import 'package:cucumber_gherkin/cucumber_gherkin.dart';
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

  final options = GherkinOptions(
    includeSource: includeSource,
    includeGherkinDocument: includeAst,
    includePickles: includePickles,
    idGenerator: idGenerator,
  );

  final envelopes = Stream.fromIterable(paths).asyncExpand((path) async* {
    yield* Stream.fromIterable(
      generateMessages(await File(path).readAsString(), path, options),
    );
  });
  await messages.encodeNdjsonEnvelopes(envelopes).forEach(stdout.write);
}
