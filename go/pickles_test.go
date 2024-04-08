package gherkin

import (
	"encoding/json"
	"fmt"
	"github.com/cucumber/messages/go/v24"
	"os"
	"strings"
	"testing"
)

func TestExampleCompilePickles(t *testing.T) {

	input := `Feature: test

  Scenario: test
    Given a <color> ball
	| ID | Name |
	| 0 | my_n123123ame |
    """
    {"payload": {"data": "va123l"}}
	"""

    Examples:
      | color |
      |  red  |
`
	r := strings.NewReader(input)

	gherkinDocument, err := ParseGherkinDocument(r, (&messages.Incrementing{}).NewId)
	if err != nil {
		fmt.Fprintf(os.Stdout, "%s\n", err)
		return
	}

	pickles := Pickles(*gherkinDocument, "test.feature", (&messages.Incrementing{}).NewId)

	marshal, err := json.Marshal(pickles)
	fmt.Fprintf(os.Stdout, string(marshal))

	// Output:
	//
	// [{"id":"1","uri":"test.feature","name":"test","language":"en","steps":[{"argument":{"docString":{"content":"{\"payload\": {\"data\": \"va123l\"}}"},"dataTable":{"rows":[{"cells":[{"value":"ID"},{"value":"Name"}]},{"cells":[{"value":"0"},{"value":"my_n123123ame"}]}]}},"astNodeIds":["2","4"],"id":"0","type":"Context","text":"a red ball"}],"tags":[],"astNodeIds":["6","4"]}]P
}
