. as $root |
[
  "#include <gherkin/dialect.hpp>\n\n",
  "namespace gherkin {\n\n",
  "const keywords_maps&\n",
  "all_keywords()\n",
  "{\n",
  "    static const keywords_maps kwms = {\n",
  "    ",
  (
    [
      to_entries[] | .key as $lang | .value |
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
                  [.value[] | [@json] | add] | join(", ")
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
  "    return kwms;",
  "}\n\n",
  "const keywords_map&\n",
  "keywords(const std::string_view& language)\n",
  "{\n",
  "    return all_keywords().at(language);\n",
  "}\n\n",
  "}\n"
] | add
