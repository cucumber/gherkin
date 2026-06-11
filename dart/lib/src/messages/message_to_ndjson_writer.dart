import 'dart:io';
import 'package:cucumber_messages/cucumber_messages.dart' as messages;
import 'package:gherkin/src/messages/message_writer.dart';

class MessageToNdjsonWriter implements IMessageWriter {
  final IOSink _out;

  MessageToNdjsonWriter(this._out);

  @override
  void write(Object message) {
    if (message is! messages.Envelope) {
      throw ArgumentError.value(message, 'message', 'Expected an Envelope');
    }
    _out.write(messages.envelopeToJsonString(message));
    _out.write('\n');
    _out.flush();
  }
}
