/// The Gherkin parser error types.
// Sealed types and their subtypes share this library; `part` files keep one
// class per file.
library;

import 'package:cucumber_gherkin/src/language/location.dart';
import 'package:cucumber_gherkin/src/language/token.dart';

part 'ast_builder_exception.dart';
part 'composite_parser_exception.dart';
part 'no_such_language_exception.dart';
part 'parser_exception.dart';
part 'token_parser_exception.dart';
part 'unexpected_eof_exception.dart';
part 'unexpected_token_exception.dart';
