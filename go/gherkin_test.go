package gherkin_test

import (
	"bytes"
	"io"
	"testing"

	gherkin "github.com/cucumber/gherkin/go/v26"
	"github.com/gofrs/uuid"
)

func Benchmark_ParseGherkinDocumentForLanguage(b *testing.B) {
	eatGodogContents := `
Feature: eat godogs
  In order to be happy
  As a hungry gopher
  I need to be able to eat godogs
  Scenario: Eat 5 out of 12
    Given there are 12 godogs
    When I eat 5
    Then there should be 7 remaining`

	r := bytes.NewReader([]byte(eatGodogContents))
	buf := new(bytes.Buffer)
	newIDFunc := func() string {
		return uuid.Must(uuid.NewV4()).String()
	}
	for i := 0; i < b.N; i++ {
		gherkin.ParseGherkinDocumentForLanguage(io.TeeReader(r, buf), gherkin.DefaultDialect, newIDFunc)
	}
}
