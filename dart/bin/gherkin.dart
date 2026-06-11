import 'dart:convert';
import 'dart:io';

import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:gherkin/gherkin.dart';
import 'package:gherkin/exceptions.dart';
import 'package:gherkin/language.dart';

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
        break;
      case '--no-ast':
        includeAst = false;
        break;
      case '--no-pickles':
        includePickles = false;
        break;
      case '--predictable-ids':
        idGenerator = IdGenerator.incrementingGenerator;
        break;
      case '--default-dialect':
        if (i + 1 >= args.length) {
          throw ArgumentError('--default-dialect requires a value');
        }
        defaultDialect = args[++i];
        break;
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
