import 'dart:convert';
import 'dart:io';

import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:cucumber_gherkin/exceptions.dart';
import 'package:cucumber_gherkin/gherkin.dart';

Future<void> main(List<String> args) async {
  var includeSource = true;
  var includeAst = true;
  var includePickles = true;
  var defaultDialect = 'en';
  var idGenerator = IdGenerator.uuidGenerator;
  final paths = <String>[];

  for (var i = 0; i < args.length; i++) {
    final arg = args[i];
    switch (arg) {
      case '--no-source':
        includeSource = false;
      case '--no-ast':
        includeAst = false;
      case '--no-pickles':
        includePickles = false;
      case '--predictable-ids':
        idGenerator = IdGenerator.incrementingGenerator;
      case '--default-dialect':
        if (i + 1 >= args.length) {
          throw ArgumentError('--default-dialect requires a value');
        }
        defaultDialect = args[++i];
      default:
        if (arg.startsWith('--default-dialect=')) {
          defaultDialect = arg.substring('--default-dialect='.length);
        } else {
          paths.add(arg);
        }
    }
  }

  final parser = GherkinParser(
    includeSource: includeSource,
    includeGherkinDocument: includeAst,
    includePickles: includePickles,
    defaultDialect: defaultDialect,
    idGenerator: idGenerator,
  );

  final envelopeStream =
      paths.isEmpty
          ? parser.parseEnvelopes(
            messages.decodeNdjsonEnvelopes(
              stdin.transform(utf8.decoder).transform(const LineSplitter()),
            ),
          )
          : parser.parsePaths(paths);

  await printMessages(envelopeStream);
}

Future<void> printMessages(Stream<messages.Envelope> messagesStream) async {
  try {
    await for (final line in messages.encodeNdjsonEnvelopes(messagesStream)) {
      stdout.write(line);
    }
  } on IOException catch (e) {
    throw GherkinException("Couldn't print messages", e);
  }
}
