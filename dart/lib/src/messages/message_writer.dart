/// A sink that serializes Cucumber [Object] messages to an output.
///
/// This is an extension point with potentially several implementations (for
/// example writing NDJSON, protobuf, or buffering in memory), so it is
/// modelled as an interface rather than a standalone function.
// ignore: one_member_abstracts
abstract class IMessageWriter {
  /// Writes a single message [object] to the underlying output.
  void write(Object object);
}
