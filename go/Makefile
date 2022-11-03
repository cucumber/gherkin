SHELL := /usr/bin/env bash

GOOD_FEATURE_FILES = $(shell find ../testdata/good -name "*.feature")
BAD_FEATURE_FILES  = $(shell find ../testdata/bad -name "*.feature")

TOKENS       = $(patsubst ../testdata/%,acceptance/testdata/%.tokens,$(GOOD_FEATURE_FILES))
ASTS         = $(patsubst ../testdata/%,acceptance/testdata/%.ast.ndjson,$(GOOD_FEATURE_FILES))
PICKLES      = $(patsubst ../testdata/%,acceptance/testdata/%.pickles.ndjson,$(GOOD_FEATURE_FILES))
SOURCES      = $(patsubst ../testdata/%,acceptance/testdata/%.source.ndjson,$(GOOD_FEATURE_FILES))
ERRORS       = $(patsubst ../testdata/%,acceptance/testdata/%.errors.ndjson,$(BAD_FEATURE_FILES))

.DEFAULT_GOAL = help
GHERKIN = bin/gherkin
GHERKIN_GENERATE_TOKENS = bin/gherkin-generate-tokens

help: ## Show this help
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make <target>\n\nWhere <target> is one of:\n"} /^[$$()% a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)

generate: parser.go ## Generate gherkin parser files

clean-generate: ## Remove generated Gherkin parser files ## Generate gherkin parser files
	rm -f parser.go

copy-gherkin-languages: dialects_builtin.go ## Copy gherkin-languages.json and/or generate derived files

clean-gherkin-languages: ## Remove gherkin-languages.json and any derived files
	rm -f dialects_builtin.go
	rm -f gherkin-languages.json

clean:
	rm -rf acceptance
	rm -rf bin

.DELETE_ON_ERROR:

acceptance: bin/gherkin-generate-tokens bin/gherkin $(TOKENS) $(ASTS) $(PICKLES) $(ERRORS) $(SOURCES) ## Build acceptance test dir and compare results with reference

bin/gherkin-generate-tokens:
	go build -o $@ ./gherkin-generate-tokens

bin/gherkin:
	go build -o $@ -a ./cmd

gherkin-languages.json:
	cp ../gherkin-languages.json $@

dialects_builtin.go: gherkin-languages.json dialects_builtin.go.jq
	cat $< | jq --sort-keys --from-file dialects_builtin.go.jq --raw-output --compact-output > $@

parser.go: parser.go.razor ../gherkin.berp
	berp -g ../gherkin.berp -t $< -o $@ --noBOM
	gofmt -w $@

acceptance/testdata/%.tokens: ../testdata/% ../testdata/%.tokens
	mkdir -p $(@D)
	$(GHERKIN_GENERATE_TOKENS) $< > $@
	diff --unified $<.tokens $@

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
