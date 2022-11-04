SHELL := /usr/bin/env bash

GHERKIN_LANGUAGES_JSON = src/gherkin-languages.json
GHERKIN_PARSER = lib/gherkin/gherkin-languages.json
GHERKIN_RAZOR = gherkin-javascript.razor
SOURCE_FILES = $(shell find . -name "*.js")

GHERKIN = npx gherkin-javascript

GOOD_FEATURE_FILES = $(shell find ../testdata/good -name "*.feature" -o -name "*.feature.md")
BAD_FEATURE_FILES  = $(shell find ../testdata/bad -name "*.feature" -o -name "*.feature.md")

ASTS         = $(patsubst ../testdata/%,acceptance/testdata/%.ast.ndjson,$(GOOD_FEATURE_FILES))
PICKLES      = $(patsubst ../testdata/%,acceptance/testdata/%.pickles.ndjson,$(GOOD_FEATURE_FILES))
SOURCES      = $(patsubst ../testdata/%,acceptance/testdata/%.source.ndjson,$(GOOD_FEATURE_FILES))
ERRORS       = $(patsubst ../testdata/%,acceptance/testdata/%.errors.ndjson,$(BAD_FEATURE_FILES))

.DEFAULT_GOAL = help

help: ## Show this help
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make <target>\n\nWhere <target> is one of:\n"} /^[$$()% a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)

generate: src/Parser.ts ## Generate gherkin parser files

clean-generate: ## Remove generated Gherkin parser files ## Generate gherkin parser files
	rm -f src/Parser.ts

copy-gherkin-languages: $(GHERKIN_LANGUAGES_JSON) ## Copy gherkin-languages.json and/or generate derived files

clean-gherkin-languages: ## Remove gherkin-languages.json and any derived files
	rm -f $(GHERKIN_LANGUAGES_JSON)

clean:
	rm -rf .built
	rm -rf acceptance
	rm -rf node_modules

.DELETE_ON_ERROR:

acceptance: .built $(ASTS) $(PICKLES) $(ERRORS) $(SOURCES) ## Build acceptance test dir and compare results with reference

.built: node_modules $(SOURCE_FILES)

node_modules:
	npm install

$(GHERKIN_PARSER): $(GHERKIN_RAZOR) ../gherkin.berp
	berp -g ../gherkin.berp -t $< -o $@ --noBOM

$(GHERKIN_LANGUAGES_JSON):
	cp ../gherkin-languages.json $@

acceptance/testdata/%.ast.ndjson: ../testdata/% ../testdata/%.ast.ndjson
	mkdir -p $(@D)
	$(GHERKIN) --no-source --no-pickles --predictable-ids $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq "." $<.ast.ndjson) <(jq "." $@)

acceptance/testdata/%.pickles.ndjson: ../testdata/% ../testdata/%.pickles.ndjson
	mkdir -p $(@D)
	$(GHERKIN) --no-source --no-ast --predictable-ids $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq "." $<.pickles.ndjson) <(jq "." $@)

acceptance/testdata/%.source.ndjson: ../testdata/% ../testdata/%.source.ndjson
	mkdir -p $(@D)
	$(GHERKIN) --no-ast --no-pickles --predictable-ids $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq "." $<.source.ndjson) <(jq "." $@)

acceptance/testdata/%.errors.ndjson: ../testdata/% ../testdata/%.errors.ndjson
	mkdir -p $(@D)
	$(GHERKIN) --no-source --predictable-ids $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq "." $<.errors.ndjson) <(jq "." $@)
