package gherkin

import (
	"encoding/json"
	"fmt"
	"os"
	"strings"

	messages "github.com/cucumber/messages/go/v32"
)

func ExamplePickles() {

	input := `Feature: test

  Scenario: test
    Given a <color> ball

    Examples:
      | color |
      |  red  |
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
	// [{"id":"1","uri":"test.feature","location":{"line":8,"column":7},"name":"test","language":"en","steps":[{"astNodeIds":["0","2"],"id":"0","type":"Context","text":"a red ball"}],"tags":[],"astNodeIds":["4","2"]}]
}
