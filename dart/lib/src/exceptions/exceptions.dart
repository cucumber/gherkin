/// The Gherkin exception hierarchy.
///
/// These types live in a single library so that [ParserException] and
/// [TokenParserException] can be `sealed`: Dart only permits subtypes of a
/// sealed class within the same library. The individual `part` files below
/// keep the source split one-class-per-file for readability, while the public
/// `package:cucumber_gherkin/cucumber_gherkin.dart` library re-exports these
/// types.
library;

import 'package:cucumber_gherkin/src/language/location.dart';
import 'package:cucumber_gherkin/src/language/token.dart';

part 'ast_builder_exception.dart';
part 'composite_parser_exception.dart';
part 'gherkin_exception.dart';
part 'no_such_language_exception.dart';
part 'parser_exception.dart';
part 'token_parser_exception.dart';
part 'unexpected_eof_exception.dart';
part 'unexpected_token_exception.dart';
