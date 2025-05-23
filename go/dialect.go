package gherkin

import (
	"sort"
	"sync"

	messages "github.com/cucumber/messages/go/v24"
)

type Dialect struct {
	Language     string
	Name         string
	Native       string
	Keywords     map[string][]string
	KeywordTypes map[string]messages.StepKeywordType

	stepKeywordBuilder sync.Once
	stepKeywordsCache  []string
}

func (g *Dialect) FeatureKeywords() []string {
	return g.Keywords["feature"]
}

func (g *Dialect) RuleKeywords() []string {
	return g.Keywords["rule"]
}

func (g *Dialect) ScenarioKeywords() []string {
	return g.Keywords["scenario"]
}

func (g *Dialect) StepKeywords() []string {
	// This only needs to be calculated the once, not every time
	g.stepKeywordBuilder.Do(func() {
		result := g.Keywords["given"]
		result = append(result, g.Keywords["when"]...)
		result = append(result, g.Keywords["then"]...)
		result = append(result, g.Keywords["and"]...)
		result = append(result, g.Keywords["but"]...)

		sort.Slice(result, func(i, j int) bool {
			return result[i] > result[j]
		})
		g.stepKeywordsCache = result
	})

	return g.stepKeywordsCache
}

func (g *Dialect) BackgroundKeywords() []string {
	return g.Keywords["background"]
}

func (g *Dialect) ScenarioOutlineKeywords() []string {
	return g.Keywords["scenarioOutline"]
}

func (g *Dialect) ExamplesKeywords() []string {
	return g.Keywords["examples"]
}

func (g *Dialect) StepKeywordType(keyword string) messages.StepKeywordType {
	return g.KeywordTypes[keyword]
}

type DialectProvider interface {
	GetDialect(language string) *Dialect
}

type gherkinDialectMap map[string]*Dialect

func (g gherkinDialectMap) GetDialect(language string) *Dialect {
	return g[language]
}
