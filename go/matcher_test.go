package gherkin_test

import (
	"testing"

	gherkin "github.com/cucumber/gherkin/go/v26"
	"github.com/gofrs/uuid"
)

func BenchmarkMatcher_MatchTagLine(b *testing.B) {
	builder := gherkin.NewAstBuilder(func() string {
		return uuid.Must(uuid.NewV4()).String()
	})
	parser := gherkin.NewParser(builder)
	parser.StopAtFirstError(false)
	matcher := gherkin.NewLanguageMatcher(gherkin.DialectsBuiltin(), gherkin.DefaultDialect)

	lines := []gherkin.Line{{
		LineText:        "    @hello # there",
		AtEof:           false,
		LineNumber:      0,
		TrimmedLineText: "@hello # there",
	}, {
		LineText:        "    @yes # there",
		AtEof:           false,
		LineNumber:      0,
		TrimmedLineText: "@yes # there",
	}}

	for i := 0; i < b.N; i++ {
		for _, line := range lines {
			matcher.MatchTagLine(&line)
		}
	}
}
