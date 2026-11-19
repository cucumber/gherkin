Feature: Scenario Outline with example column names that are prefixes of each other

Scenario Outline: minimalistic
    Given the <value> and the <value_2>

Examples:
  | value | value_2 |
  | foo   | bar     |
