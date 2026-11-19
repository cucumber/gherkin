# language: en
@benchmark @gherkin
Feature: Parse a varied collection of delivery workflows

  Background: Shared service configuration
    Given the delivery service is available
    And the test catalogue is loaded
    But no orders have been submitted

  Scenario: Feature delivery case 01
    * a customer selects the delivery option
    Then the selected destination is retained
    Given the order is submitted for validation
    Then the service returns a delivery estimate

  @regression @unicode @smoke
  Scenario Outline: Feature delivery case 02
    Then the audit log records the request for <destination> with priority <priority>
    When a customer selects the delivery option
    * the audit log records the request

      Examples: Delivery destinations
        | destination | priority |
        | north       | standard |
        | south       | express  |
        | east        | economy  |

  Scenario: Feature delivery case 03
    And the order is submitted for validation
    Then the selected destination is retained
    Given the notification remains queued
    Given the audit log records the request
    And the service returns a delivery estimate

  Scenario: Feature delivery case 04
    When the order is submitted for validation
    But the notification remains queued
    When the service returns a delivery estimate
    Then the order is submitted for validation

  Scenario: Feature delivery case 05
    But the audit log records the request
    * the service returns a delivery estimate
    When the notification remains queued
    * the audit log records the request
    When the notification remains queued

  Scenario Outline: Feature delivery case 06
    * the service returns a delivery estimate for <destination> with priority <priority>
    Then the selected destination is retained
    And the order is submitted for validation

      @examples
      Examples: Delivery destinations
        | destination | priority |
        | north       | standard |
        | south       | express  |
        | east        | economy  |

  @nightly
  Scenario: Feature delivery case 07
    Given the order is submitted for validation
    Given the audit log records the request
    And the order is submitted for validation
    When the order is submitted for validation
    Given the order is submitted for validation

  Scenario: Feature delivery case 08
    But the order is submitted for validation
    Given the notification remains queued
    When the audit log records the request
    When a customer selects the delivery option

  Scenario Outline: Feature delivery case 09
    Then the notification remains queued for <destination> with priority <priority>
    Given the notification remains queued
      | field       | value                  |
      | destination | <destination> |
      | reference   | parcel\|express        |
      | note        | first line\nsecond line |
      | path        | depot\\dispatch        |
    * the audit log records the request
    * the order is submitted for validation
    Given the notification remains queued

      @examples
      Examples: Delivery destinations
        | destination | priority |
        | north       | standard |
        | south       | express  |
        | east        | economy  |

  Scenario Outline: Feature delivery case 10
    Then the audit log records the request for <destination> with priority <priority>
    Given the audit log records the request
    Then the service returns a delivery estimate

      Examples: Delivery destinations
        | destination | priority |
        | north       | standard |
        | south       | express  |
        | east        | economy  |

  @parser @regression @smoke
  Scenario: Feature delivery case 11
    Then the order is submitted for validation
    * the audit log records the request
    When the notification remains queued
    * the service returns a delivery estimate

  @unicode @nightly @parser
  Scenario: Feature delivery case 12
    And the service returns a delivery estimate
    When a customer selects the delivery option
    Then a customer selects the delivery option
    Given the service returns a delivery estimate

  Scenario Outline: Feature delivery case 13
    Then a customer selects the delivery option for <destination> with priority <priority>
    * the notification remains queued
    And the notification remains queued
    Given the notification remains queued
    Then the notification remains queued

      Examples: Delivery destinations
        | destination | priority |
        | north       | standard |
        | south       | express  |
        | east        | economy  |

  @slow
  Scenario: Feature delivery case 14
    When a customer selects the delivery option
      """application/json
      {
        "message": "delivery details",
        "destination": "north",
        "note": "retain whitespace and punctuation: @ # |"
      }
      """
      | field       | value                  |
      | destination | north |
      | reference   | parcel\|express        |
      | note        | first line\nsecond line |
      | path        | depot\\dispatch        |
    * the order is submitted for validation
    Given the service returns a delivery estimate
    When the selected destination is retained
    Given a customer selects the delivery option

  @regression @parser @nightly
  Scenario Outline: Feature delivery case 15
    And a customer selects the delivery option for <destination> with priority <priority>
    * the order is submitted for validation
    Then the notification remains queued

      Examples: Delivery destinations
        | destination | priority |
        | north       | standard |
        | south       | express  |
        | east        | economy  |

  Scenario: Feature delivery case 16
    Given the order is submitted for validation
    When the selected destination is retained
    When the service returns a delivery estimate
    Then the service returns a delivery estimate

  Scenario: Feature delivery case 17
    * the order is submitted for validation
    Then the service returns a delivery estimate
    When the order is submitted for validation
    And the order is submitted for validation
    When a customer selects the delivery option

  @smoke
  Scenario: Feature delivery case 18
    Given a customer selects the delivery option
    Given the selected destination is retained
    But the selected destination is retained
    Then the notification remains queued

  Rule: Delivery policy 1

    Background: Policy configuration
      Given delivery policy 1 is enabled
      And the policy has an active destination
      But no policy overrides are applied

    @smoke
    Scenario Outline: Rule 1 delivery case 01
      Given the notification remains queued for <destination> with priority <priority>
      * the audit log records the request
      When the order is submitted for validation

        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    @regression @slow @nightly
    Scenario: Rule 1 delivery case 02
      Then the selected destination is retained
      When the order is submitted for validation
        """application/json
        {
          "message": "delivery details",
          "destination": "north",
          "note": "retain whitespace and punctuation: @ # |"
        }
        """
      But the notification remains queued
      But the order is submitted for validation
      But the order is submitted for validation

    Scenario Outline: Rule 1 delivery case 03
      Given a customer selects the delivery option for <destination> with priority <priority>
      Given the service returns a delivery estimate
      * the audit log records the request
      Given the notification remains queued

        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    @unicode
    Scenario Outline: Rule 1 delivery case 04
      But the service returns a delivery estimate for <destination> with priority <priority>
      Given the service returns a delivery estimate
      Then the audit log records the request
      Then a customer selects the delivery option
      But the selected destination is retained
        | field       | value                  |
        | destination | <destination> |
        | reference   | parcel\|express        |
        | note        | first line\nsecond line |
        | path        | depot\\dispatch        |

        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    @slow
    Scenario: Rule 1 delivery case 05
      And a customer selects the delivery option
      And the notification remains queued
      But a customer selects the delivery option
      Then a customer selects the delivery option
      Then the notification remains queued

    @slow @nightly @parser
    Scenario: Rule 1 delivery case 06
      And the notification remains queued
      * the notification remains queued
      * the selected destination is retained

    @regression
    Scenario: Rule 1 delivery case 07
      When the selected destination is retained
      Given a customer selects the delivery option
      Then a customer selects the delivery option

    @smoke @nightly
    Scenario Outline: Rule 1 delivery case 08
      Then the order is submitted for validation for <destination> with priority <priority>
      And the selected destination is retained
      * a customer selects the delivery option
      Then the order is submitted for validation
      * a customer selects the delivery option

        @examples
        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    Scenario: Rule 1 delivery case 09
      Then the order is submitted for validation
      But the service returns a delivery estimate
      But the service returns a delivery estimate
      And a customer selects the delivery option

    Scenario: Rule 1 delivery case 10
      And the order is submitted for validation
        | field       | value                  |
        | destination | north |
        | reference   | parcel\|express        |
        | note        | first line\nsecond line |
        | path        | depot\\dispatch        |
        """application/json
        {
          "message": "delivery details",
          "destination": "north",
          "note": "retain whitespace and punctuation: @ # |"
        }
        """
      And the selected destination is retained
      * a customer selects the delivery option

    Scenario Outline: Rule 1 delivery case 11
      Given the notification remains queued for <destination> with priority <priority>
      When the order is submitted for validation
      * the notification remains queued
      But the notification remains queued
      Given the service returns a delivery estimate

        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    Scenario: Rule 1 delivery case 12
      When a customer selects the delivery option
      Then the order is submitted for validation
      But the audit log records the request

    Scenario Outline: Rule 1 delivery case 13
      * the audit log records the request for <destination> with priority <priority>
        | field       | value                  |
        | destination | <destination> |
        | reference   | parcel\|express        |
        | note        | first line\nsecond line |
        | path        | depot\\dispatch        |
      But the selected destination is retained
      When the order is submitted for validation
      But the selected destination is retained

        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

  Rule: Delivery policy 2

    Background: Policy configuration
      Given delivery policy 2 is enabled
      And the policy has an active destination
      But no policy overrides are applied

    Scenario: Rule 2 delivery case 01
      But a customer selects the delivery option
      * the selected destination is retained
      Given the notification remains queued
      Given the service returns a delivery estimate

    Scenario: Rule 2 delivery case 02
      * a customer selects the delivery option
      Given the audit log records the request
      Then the service returns a delivery estimate

    Scenario: Rule 2 delivery case 03
      Given the service returns a delivery estimate
      Given the notification remains queued
      Given the order is submitted for validation
      And the service returns a delivery estimate

    Scenario: Rule 2 delivery case 04
      * the service returns a delivery estimate
      And the order is submitted for validation
        | field       | value                  |
        | destination | north |
        | reference   | parcel\|express        |
        | note        | first line\nsecond line |
        | path        | depot\\dispatch        |
        """application/json
        {
          "message": "delivery details",
          "destination": "north",
          "note": "retain whitespace and punctuation: @ # |"
        }
        """
      When the selected destination is retained
      Given the notification remains queued

    @parser @regression
    Scenario Outline: Rule 2 delivery case 05
      But a customer selects the delivery option for <destination> with priority <priority>
      When the service returns a delivery estimate
      * a customer selects the delivery option
      When the audit log records the request
      But the notification remains queued

        @examples
        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    @slow @unicode
    Scenario: Rule 2 delivery case 06
      When the notification remains queued
      When the audit log records the request
      When a customer selects the delivery option

    @parser
    Scenario: Rule 2 delivery case 07
      Given the selected destination is retained
      Then the selected destination is retained
      Then the order is submitted for validation
      And the service returns a delivery estimate

    Scenario: Rule 2 delivery case 08
      And the selected destination is retained
      Given the selected destination is retained
      * the notification remains queued
      But the order is submitted for validation

    Scenario Outline: Rule 2 delivery case 09
      But the notification remains queued for <destination> with priority <priority>
      When the audit log records the request
      And the audit log records the request

        @examples
        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    Scenario Outline: Rule 2 delivery case 10
      * the audit log records the request for <destination> with priority <priority>
      But the notification remains queued
      When the order is submitted for validation
      Given the selected destination is retained
      Given the order is submitted for validation

        @examples
        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    @nightly @regression
    Scenario: Rule 2 delivery case 11
      And the notification remains queued
      Then the audit log records the request
      * the service returns a delivery estimate
      Given the audit log records the request
      And the audit log records the request

    @regression @smoke @nightly
    Scenario Outline: Rule 2 delivery case 12
      But a customer selects the delivery option for <destination> with priority <priority>
      Given the order is submitted for validation
      Then the service returns a delivery estimate

        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    Scenario Outline: Rule 2 delivery case 13
      But the service returns a delivery estimate for <destination> with priority <priority>
      But the audit log records the request
      * the notification remains queued

        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    @slow
    Scenario: Rule 2 delivery case 14
      * the service returns a delivery estimate
        """application/json
        {
          "message": "delivery details",
          "destination": "north",
          "note": "retain whitespace and punctuation: @ # |"
        }
        """
        | field       | value                  |
        | destination | north |
        | reference   | parcel\|express        |
        | note        | first line\nsecond line |
        | path        | depot\\dispatch        |
      Given a customer selects the delivery option
      But the order is submitted for validation

    Scenario: Rule 2 delivery case 15
      But the audit log records the request
      But the notification remains queued
      But the selected destination is retained

    Scenario: Rule 2 delivery case 16
      Then the service returns a delivery estimate
      When a customer selects the delivery option
      And the selected destination is retained

    @regression @parser @nightly
    Scenario Outline: Rule 2 delivery case 17
      When a customer selects the delivery option for <destination> with priority <priority>
      Given the service returns a delivery estimate
      * the audit log records the request
      Then the service returns a delivery estimate
      When a customer selects the delivery option

        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    @unicode @parser
    Scenario: Rule 2 delivery case 18
      And the notification remains queued
      Given a customer selects the delivery option
      * a customer selects the delivery option

  Rule: Delivery policy 3

    Background: Policy configuration
      Given delivery policy 3 is enabled
      And the policy has an active destination
      But no policy overrides are applied

    Scenario: Rule 3 delivery case 01
      When the order is submitted for validation
      Then the service returns a delivery estimate
      When the selected destination is retained
        """application/json
        {
          "message": "delivery details",
          "destination": "north",
          "note": "retain whitespace and punctuation: @ # |"
        }
        """
      And the notification remains queued

    Scenario: Rule 3 delivery case 02
      And a customer selects the delivery option
      But the audit log records the request
      Then a customer selects the delivery option

    @parser
    Scenario: Rule 3 delivery case 03
      When the order is submitted for validation
      Given the audit log records the request
      * the service returns a delivery estimate
      When a customer selects the delivery option

    Scenario Outline: Rule 3 delivery case 04
      * the notification remains queued for <destination> with priority <priority>
      Then the service returns a delivery estimate
        """application/json
        {
          "message": "delivery details",
          "destination": "<destination>",
          "note": "retain whitespace and punctuation: @ # |"
        }
        """
      And the audit log records the request
      * the service returns a delivery estimate

        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    @smoke
    Scenario: Rule 3 delivery case 05
      * a customer selects the delivery option
      * the notification remains queued
      When the service returns a delivery estimate

    Scenario: Rule 3 delivery case 06
      * the audit log records the request
      * the order is submitted for validation
      * the audit log records the request

    @unicode @smoke
    Scenario: Rule 3 delivery case 07
      * the service returns a delivery estimate
      * a customer selects the delivery option
        """application/json
        {
          "message": "delivery details",
          "destination": "north",
          "note": "retain whitespace and punctuation: @ # |"
        }
        """
      Given the notification remains queued

    Scenario: Rule 3 delivery case 08
      And the audit log records the request
      Then the order is submitted for validation
      When the order is submitted for validation
      When the selected destination is retained

    Scenario: Rule 3 delivery case 09
      When the order is submitted for validation
      Then the audit log records the request
      Given the selected destination is retained
      When the notification remains queued
      Then the order is submitted for validation

    Scenario: Rule 3 delivery case 10
      When the service returns a delivery estimate
      Then the selected destination is retained
      * the notification remains queued

    Scenario: Rule 3 delivery case 11
      But the selected destination is retained
      Given the service returns a delivery estimate
      But a customer selects the delivery option
      And a customer selects the delivery option

    Scenario: Rule 3 delivery case 12
      But the service returns a delivery estimate
      Then the audit log records the request
      Then a customer selects the delivery option
      Given the audit log records the request

    Scenario: Rule 3 delivery case 13
      * the order is submitted for validation
      Then the selected destination is retained
        """application/json
        {
          "message": "delivery details",
          "destination": "north",
          "note": "retain whitespace and punctuation: @ # |"
        }
        """
      * the selected destination is retained

    Scenario Outline: Rule 3 delivery case 14
      When the order is submitted for validation for <destination> with priority <priority>
      When the selected destination is retained
      Then the order is submitted for validation
      When the selected destination is retained
      But the notification remains queued

        @examples
        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    @smoke @parser @nightly
    Scenario: Rule 3 delivery case 15
      Given the service returns a delivery estimate
      Given a customer selects the delivery option
      But the notification remains queued
      But the notification remains queued
      When the notification remains queued

  Rule: Delivery policy 4

    Background: Policy configuration
      Given delivery policy 4 is enabled
      And the policy has an active destination
      But no policy overrides are applied

    Scenario: Rule 4 delivery case 01
      When the notification remains queued
      When the notification remains queued
        | field       | value                  |
        | destination | north |
        | reference   | parcel\|express        |
        | note        | first line\nsecond line |
        | path        | depot\\dispatch        |
        """application/json
        {
          "message": "delivery details",
          "destination": "north",
          "note": "retain whitespace and punctuation: @ # |"
        }
        """
      When the order is submitted for validation

    Scenario: Rule 4 delivery case 02
      Given the notification remains queued
      Given the selected destination is retained
      But the audit log records the request

    Scenario Outline: Rule 4 delivery case 03
      Then a customer selects the delivery option for <destination> with priority <priority>
      When the order is submitted for validation
      * the notification remains queued
      But the selected destination is retained
        | field       | value                  |
        | destination | <destination> |
        | reference   | parcel\|express        |
        | note        | first line\nsecond line |
        | path        | depot\\dispatch        |

        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    Scenario: Rule 4 delivery case 04
      Then the service returns a delivery estimate
      But the audit log records the request
      When the notification remains queued
      When the selected destination is retained
      When a customer selects the delivery option

    Scenario: Rule 4 delivery case 05
      Then the notification remains queued
      But the selected destination is retained
      When a customer selects the delivery option
      Given the service returns a delivery estimate
      Given the selected destination is retained

    Scenario: Rule 4 delivery case 06
      And a customer selects the delivery option
      * the notification remains queued
      When the notification remains queued

    @regression
    Scenario: Rule 4 delivery case 07
      But the audit log records the request
      When the audit log records the request
      But the order is submitted for validation
      * the selected destination is retained

    Scenario: Rule 4 delivery case 08
      And the service returns a delivery estimate
      Then the service returns a delivery estimate
      Given the order is submitted for validation
      * the service returns a delivery estimate
      But the selected destination is retained

    Scenario Outline: Rule 4 delivery case 09
      But the order is submitted for validation for <destination> with priority <priority>
      Then the audit log records the request
      But a customer selects the delivery option
      * the notification remains queued
      But the order is submitted for validation

        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    Scenario Outline: Rule 4 delivery case 10
      Then a customer selects the delivery option for <destination> with priority <priority>
      * the audit log records the request
      * the audit log records the request
      When the audit log records the request

        @examples
        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    Scenario: Rule 4 delivery case 11
      And a customer selects the delivery option
      But the order is submitted for validation
      Given the selected destination is retained
      Then a customer selects the delivery option

    @parser @regression @nightly
    Scenario: Rule 4 delivery case 12
      And the order is submitted for validation
      Given the order is submitted for validation
      * the audit log records the request
      But the audit log records the request

    Scenario: Rule 4 delivery case 13
      Then the selected destination is retained
      When the order is submitted for validation
      But the audit log records the request

    @slow @parser @unicode
    Scenario: Rule 4 delivery case 14
      When the order is submitted for validation
      When the order is submitted for validation
      Then the audit log records the request

    Scenario: Rule 4 delivery case 15
      Given the notification remains queued
      When a customer selects the delivery option
      Given the notification remains queued

    Scenario: Rule 4 delivery case 16
      But the order is submitted for validation
      But the notification remains queued
      But the audit log records the request

  Rule: Delivery policy 5

    Background: Policy configuration
      Given delivery policy 5 is enabled
      And the policy has an active destination
      But no policy overrides are applied

    Scenario: Rule 5 delivery case 01
      Then a customer selects the delivery option
      When a customer selects the delivery option
      And the service returns a delivery estimate
      But the order is submitted for validation
      Then the order is submitted for validation

    Scenario: Rule 5 delivery case 02
      And the service returns a delivery estimate
      Then the service returns a delivery estimate
      * the selected destination is retained

    Scenario: Rule 5 delivery case 03
      When the order is submitted for validation
      But the order is submitted for validation
      Then the selected destination is retained
      Then the service returns a delivery estimate

    Scenario Outline: Rule 5 delivery case 04
      When the selected destination is retained for <destination> with priority <priority>
      * the notification remains queued
      When the order is submitted for validation
      But the order is submitted for validation
      But the audit log records the request

        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |

    @unicode @nightly
    Scenario: Rule 5 delivery case 05
      And the audit log records the request
      And the audit log records the request
      * the service returns a delivery estimate
      Then the selected destination is retained

    @slow
    Scenario: Rule 5 delivery case 06
      Given a customer selects the delivery option
      Then the audit log records the request
      Then the audit log records the request

    @nightly
    Scenario: Rule 5 delivery case 07
      When the notification remains queued
      When a customer selects the delivery option
      Given the audit log records the request
      When a customer selects the delivery option

    Scenario: Rule 5 delivery case 08
      And the selected destination is retained
      Given the order is submitted for validation
      And the selected destination is retained
      But the service returns a delivery estimate

    Scenario: Rule 5 delivery case 09
      * the audit log records the request
      When the service returns a delivery estimate
      Then the notification remains queued
      But a customer selects the delivery option
      But the service returns a delivery estimate

    Scenario Outline: Rule 5 delivery case 10
      When the service returns a delivery estimate for <destination> with priority <priority>
      And the order is submitted for validation
      * a customer selects the delivery option
        | field       | value                  |
        | destination | <destination> |
        | reference   | parcel\|express        |
        | note        | first line\nsecond line |
        | path        | depot\\dispatch        |
      When a customer selects the delivery option

        Examples: Delivery destinations
          | destination | priority |
          | north       | standard |
          | south       | express  |
          | east        | economy  |
