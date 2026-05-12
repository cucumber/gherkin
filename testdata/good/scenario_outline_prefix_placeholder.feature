Feature: Scenario outline with prefix placeholder

  Scenario Outline: scenario
    Given the <parentflag>

    Examples:

      | parent | parentflag |
      | v      | v          |
