part of 'exceptions.dart';

final class NoSuchLanguageException extends ParserException {
  NoSuchLanguageException(String language, [Location location = Location.empty])
    : super.located('Language not supported: $language', location);
}
