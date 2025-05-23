SHELL := /usr/bin/env bash

GHERKIN_LANGUAGES_JSON = resources/gherkin-languages.json
GHERKIN_PARSER = src-generated/Parser.php
GHERKIN_RAZOR = gherkin-php.razor
SOURCE_FILES = $(shell find . -name "*.php"  | grep -v $(GHERKIN_PARSER))

GHERKIN = bin/gherkin
GHERKIN_GENERATE_TOKENS = bin/gherkin-generate-tokens

GOOD_FEATURE_FILES = $(shell find ../testdata/good -name "*.feature")
BAD_FEATURE_FILES  = $(shell find ../testdata/bad -name "*.feature")

TOKENS       = $(patsubst ../testdata/%,acceptance/testdata/%.tokens,$(GOOD_FEATURE_FILES))
ASTS         = $(patsubst ../testdata/%,acceptance/testdata/%.ast.ndjson,$(GOOD_FEATURE_FILES))
PICKLES      = $(patsubst ../testdata/%,acceptance/testdata/%.pickles.ndjson,$(GOOD_FEATURE_FILES))
SOURCES      = $(patsubst ../testdata/%,acceptance/testdata/%.source.ndjson,$(GOOD_FEATURE_FILES))
ERRORS       = $(patsubst ../testdata/%,acceptance/testdata/%.errors.ndjson,$(BAD_FEATURE_FILES))

.DEFAULT_GOAL = help

help: ## Show this help
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make <target>\n\nWhere <target> is one of:\n"} /^[$$()% a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)
.PHONY: help

generate: $(GHERKIN_PARSER) ## Generate gherkin parser files
.PHONY: generate

clean-generate: ## Remove generated Gherkin parser files
	rm -f $(GHERKIN_PARSER)
.PHONY: help

copy-gherkin-languages: $(GHERKIN_LANGUAGES_JSON) ## Copy gherkin-languages.json and/or generate derived files
.PHONY: clean-generate

clean-gherkin-languages: ## Remove gherkin-languages.json and any derived files
	rm -f $(GHERKIN_LANGUAGES_JSON)
.PHONY: clean-gherkin-languages

mostlyclean:
	rm -f .built
	rm -rf acceptance
.PHONY: mostlyclean

clean: mostlyclean ## Remove all build artifacts and files generated by the acceptance tests
	rm -rf vendor
.PHONY: clean

.DELETE_ON_ERROR:

acceptance: .built $(TOKENS) $(ASTS) $(PICKLES) $(ERRORS) $(SOURCES) ## Build acceptance test dir and compare results with reference

.built: vendor $(SOURCE_FILES)
	touch $@

vendor: composer.json
	composer update

$(GHERKIN_PARSER): $(GHERKIN_RAZOR) ../gherkin.berp
	mkdir -p build
	berp -g ../gherkin.berp -t $< -o build/classes.php --noBOM
	csplit --quiet --prefix=build/Generated --suffix-format=%02d.php.tmp --elide-empty-files build/classes.php /^[A-Za-z\/]*\.php$$/ {*}
	for file in build/Generated**; do mkdir -p src-generated/$$(head -n 1 $$file | sed 's/[^/]*.php$$//'); done
	for file in build/Generated**; do tail -n +2 $$file > src-generated/$$(head -n 1 $$file); rm $$file; done
	rm -f build/classes.php

$(GHERKIN_LANGUAGES_JSON):
	cp ../gherkin-languages.json $@

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
