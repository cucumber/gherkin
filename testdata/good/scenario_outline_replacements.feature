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

  Scenario Outline: the variables are replaced by going through from left to right through the examples table
    Given <b<a>> and <a>

    Examples:
      | a      | b<a>    |
      | pickle | gherkin |

  Scenario Outline: the first matching column is used
    Given <a>

    Examples:
      | a      | a       |
      | pickle | gherkin |

  Scenario Outline: variables are replaced once
    Given <a> and <b>

    Examples:
      | a   | b   |
      | <b> | pickle |
