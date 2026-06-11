import 'i_gherkin_dialect.dart';
import 'location.dart';

abstract class IGherkinDialectProvider {
  IGherkinDialect get defaultDialect;

  IGherkinDialect getDialect(String language, Location location);

  List<String> get languages;
}
