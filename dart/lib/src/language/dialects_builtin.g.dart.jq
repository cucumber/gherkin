# Generates lib/src/language/dialects_builtin.g.dart from gherkin-languages.json.
#
# This mirrors the Go implementation's dialects_builtin.go.jq: the dialect data
# is emitted as final, formatted Dart source directly by jq, so the monorepo
# codegen job (which has jq + berp but no Dart SDK) can regenerate and validate
# it without a Dart toolchain.
#
# The output must be byte-identical to what `dart format` produces, so list
# literals are wrapped exactly the way the formatter would: a list is kept on a
# single line when its rendered form fits within the 80 code point page width,
# and is otherwise split with one element per line. Every dialect keyword list
# in gherkin-languages.json is short enough that code point width (what jq's
# `length` measures) matches the formatter's width decision.
#
# Usage:
#
#   jq --sort-keys --from-file dialects_builtin.g.dart.jq --raw-output \
#     --compact-output gherkin-languages.json > dialects_builtin.g.dart

# Renders a Dart single-line string literal for the input string.
#
# @json handles quotes, backslashes and control characters; the extra
# gsub escapes `$` so it is not treated as Dart string interpolation.
def dart_string: @json | gsub("\\$"; "\\$");

# Renders a List<String> literal for the input array, wrapping to match
# `dart format`. `$indent` is the leading whitespace of the opening line.
def dart_list($indent):
  [.[] | dart_string] as $elems
  | ($indent + "[" + ($elems | join(", ")) + "],") as $inline
  | if ($inline | length) <= 80
    then $inline + "\n"
    else
      ($indent + "[\n")
      + ([$elems[] | $indent + "  " + . + ",\n"] | add)
      + ($indent + "],\n")
    end;

# Emits the GherkinLanguageKeywords positional arguments for a dialect,
# in the order expected by the constructor.
def dialect_body:
  .value as $d
  | "    " + ($d.name | dart_string) + ",\n"
  + "    " + ($d.native | dart_string) + ",\n"
  + ([
      "feature", "rule", "background", "scenario", "scenarioOutline",
      "examples", "given", "when", "then", "and", "but"
    ] | map($d[.] | dart_list("    ")) | add);

"// GENERATED CODE - DO NOT MODIFY BY HAND\n"
+ "// ignore_for_file: type=lint\n"
+ "\n"
+ "import 'package:cucumber_gherkin/src/language/gherkin_language_keywords.dart';\n"
+ "\n"
+ "/// The Gherkin dialects bundled with this package, keyed by\n"
+ "/// language tag, embedded from `gherkin-languages.json`.\n"
+ "const Map<String, GherkinLanguageKeywords> builtinDialects = {\n"
+ ([
    to_entries | sort_by(.key)[]
    | "  " + (.key | dart_string) + ": GherkinLanguageKeywords(\n"
      + dialect_body
      + "  ),\n"
  ] | add)
+ "};"
