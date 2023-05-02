. as $root |
[
  "#include <gherkin/dialect.hpp>\n\n",
  "namespace gherkin {\n\n",
  "const keywords_map&\n",
  "keywords(const std::string_view& language)\n",
  "{\n",
  "    const keywords_maps kwms = {\n",
  "    ",
  (
    [
      to_entries[] | .key as $lang_orig |
      (.key | split("-") | join("_")) as $lang | .value |
      [
        ("{\n        \"",$lang,"\",\n        {\n"),
        ("            "),
        (
          [
            {
              "and", "background", "but", "examples", "feature", "given",
              "rule", "scenario", "scenarioOutline", "then", "when"
            } | to_entries[] |
            [
                "{ \"", .key, "\", { ",
                (
                  [.value[] |
                  sub("^[[:space:]]+"; "") | sub("[[:space:]]+$"; "") |
                  [@json] | add] | join(", ")
                ),
                " } }"
            ] | add
          ] | join(",\n            ")
        ),
        ("\n        }\n    }")
      ] | add
    ] | join(",\n    ")
  ),
  "\n    };\n\n",
  "    return kwms.at(language);\n",
  "}\n\n",
  "const string_views&\n",
  "keyword(const std::string_view& language, const std::string_view& kw)\n",
  "{ return keywords(language).at(kw); }\n\n",
  "}\n"
] | add
