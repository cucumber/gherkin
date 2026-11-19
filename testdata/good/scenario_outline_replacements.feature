Feature: Scenario Outline replacements

  Variables can be used in scenario outlines. These are replaced by going through
  the examples table from left to right, replacing the `<` + header + `>` with the
  value from the first matching column.

  Scenario Outline: the variable must match the exact column name
    Given <a>
    When <ax>
    Then <ay>

    Examples:
      | a      | ax      |
      | pickle | gherkin |

  Scenario Outline: the first matching column is used
    Given <a>

    Examples:
      | a      | a       |
      | pickle | gherkin |
