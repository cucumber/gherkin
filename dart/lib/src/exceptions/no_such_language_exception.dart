part of 'exceptions.dart';

final class NoSuchLanguageException extends ParserException {
  NoSuchLanguageException(
    String language, [
    messages.Location location = ParserException._emptyLocation,
  ]) : super.located('Language not supported: $language', location);
}
