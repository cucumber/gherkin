import 'dart:io';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:gherkin/src/messages/message_writer.dart';

/// An [IMessageWriter] that serializes each message as newline-delimited JSON
/// (NDJSON) to an [IOSink].
class MessageToNdjsonWriter implements IMessageWriter {
  /// Creates a writer that emits to [_out].
  MessageToNdjsonWriter(this._out);

  final IOSink _out;

  @override
  void write(Object message) {
    if (message is! messages.Envelope) {
      throw ArgumentError.value(message, 'message', 'Expected an Envelope');
    }
    _out
      ..write(messages.envelopeToJsonString(message))
      ..write('\n')
      ..flush();
  }
}
