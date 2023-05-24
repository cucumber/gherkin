. as $root |
[
  "#include <gherkin/dialect.hpp>\n\n",
  "namespace gherkin {\n\n",
  "const keywords_map&\n",
  "keywords(const std::string_view& language)\n",
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
  "    return kwms.at(language);\n",
  "}\n\n",
  "}\n"
] | add
