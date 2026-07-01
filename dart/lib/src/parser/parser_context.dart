import 'dart:collection';

import 'package:gherkin/exceptions.dart';
import 'package:gherkin/src/language/token.dart';
import 'package:gherkin/src/parser/token_matcher.dart';
import 'package:gherkin/src/parser/token_scanner.dart';

/// The mutable state threaded through a single parse run.
class ParserContext {
  /// Creates a context from the collaborators used during a parse.
  ParserContext(
    this.tokenScanner,
    this.tokenMatcher,
    this.tokenQueue,
    this.errors,
  );

  /// The scanner the tokens are read from.
  final TokenScanner tokenScanner;

  /// The matcher used to classify each token.
  final TokenMatcher tokenMatcher;

  /// Tokens that have been read ahead and not yet consumed.
  final Queue<Token> tokenQueue;

  /// The parse errors collected so far.
  final List<ParserException> errors;
}
