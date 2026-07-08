import 'dart:io';

import 'package:cucumber_gherkin/cucumber_gherkin_io.dart';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;

Future<void> main(List<String> args) async {
  var includeSource = true;
  var includeAst = true;
  var includePickles = true;
  var idGenerator = IdGenerator.uuidGenerator;
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
        idGenerator = IdGenerator.incrementingGenerator;
      default:
        paths.add(arg);
    }
  }

  final parser = GherkinParser(
    includeSource: includeSource,
    includeGherkinDocument: includeAst,
    includePickles: includePickles,
    idGenerator: idGenerator,
  );

  await printMessages(parser.parsePaths(paths));
}

Future<void> printMessages(Stream<messages.Envelope> messagesStream) async {
  try {
    await messages.encodeNdjsonEnvelopes(messagesStream).forEach(stdout.write);
  } on IOException catch (e) {
    throw GherkinException("Couldn't print messages", e);
  }
}
