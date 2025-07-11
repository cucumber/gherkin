package main

import (
	"fmt"
	gherkin "github.com/cucumber/gherkin/go/v33"
	"io"
	"os"
	"strings"
)

func main() {

	var readers []io.Reader
	if len(os.Args) <= 1 {
		readers = append(readers, os.Stdin)
	} else {
		for i := range os.Args[1:] {
			file, err := os.Open(os.Args[i+1])
			if err != nil {
				fmt.Fprintf(os.Stderr, "Error: %s\n", err)
				os.Exit(1)
				return
			}
			defer file.Close()
			readers = append(readers, file)
		}
	}

	for i := range readers {
		err := GenerateTokens(readers[i], os.Stdout)
		if err != nil {
			fmt.Fprintf(os.Stderr, "Error: %s\n", err)
			os.Exit(1)
			return
		}
	}
}

type tokenGenerator struct {
	out io.Writer
}

func FormatToken(token *gherkin.Token) string {
	if token.IsEOF() {
		return "EOF"
	}
	var items []string
	for i := range token.Items {
		items = append(items, token.Items[i].String())
	}
	var keyword string
	if token.Keyword == "" {
		keyword = token.Keyword
	} else if token.KeywordType == "" {
		keyword = fmt.Sprintf("()%s", token.Keyword)
	} else {
		keyword = fmt.Sprintf("(%s)%s", token.KeywordType, token.Keyword)
	}
	var text string
	if token.Type.Name() == "Empty" {
		text = ""
	} else {
		text = token.Text
	}

	return fmt.Sprintf("(%d:%d)%s:%s/%s/%s",
		token.Location.Line,
		token.Location.Column,
		token.Type.Name(),
		keyword,
		text,
		strings.Join(items, ","),
	)
}

func (t *tokenGenerator) Build(tok *gherkin.Token) (bool, error) {
	fmt.Fprintln(t.out, FormatToken(tok))
	return true, nil
}
func (t *tokenGenerator) StartRule(r gherkin.RuleType) (bool, error) {
	return true, nil
}
func (t *tokenGenerator) EndRule(r gherkin.RuleType) (bool, error) {
	return true, nil
}
func (t *tokenGenerator) Reset() {
}

func GenerateTokens(in io.Reader, out io.Writer) error {

	builder := &tokenGenerator{out}
	parser := gherkin.NewParser(builder)
	parser.StopAtFirstError(true)
	matcher := gherkin.NewMatcher(gherkin.DialectsBuiltin())

	scanner := gherkin.NewScanner(in)

	return parser.Parse(scanner, matcher)
}
