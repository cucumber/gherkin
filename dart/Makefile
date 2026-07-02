SHELL := /usr/bin/env bash

GHERKIN_LANGUAGES_JSON = lib/src/assets/gherkin-languages.json
GHERKIN_DIALECTS = lib/src/language/dialects_builtin.g.dart
GHERKIN_DIALECTS_JQ = lib/src/language/dialects_builtin.g.dart.jq
GHERKIN_PARSER = lib/src/parser/parser.g.dart
GHERKIN_RAZOR = gherkin-dart.razor
GHERKIN = dart run bin/gherkin.dart
GHERKIN_GENERATE_TOKENS = dart run bin/gherkin_generate_tokens.dart

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

$(GHERKIN_PARSER): $(GHERKIN_RAZOR) ../gherkin.berp
	berp -g ../gherkin.berp -t $(GHERKIN_RAZOR) -o $@ --noBOM

clean-generate: ## Remove generated Gherkin parser files
	rm -f $(GHERKIN_PARSER)
.PHONY: clean-generate

copy-gherkin-languages: $(GHERKIN_DIALECTS) ## Copy gherkin-languages.json and/or generate derived files
.PHONY: copy-gherkin-languages

$(GHERKIN_DIALECTS): $(GHERKIN_LANGUAGES_JSON) $(GHERKIN_DIALECTS_JQ)
	jq --sort-keys --from-file $(GHERKIN_DIALECTS_JQ) --raw-output --compact-output $< > $@

clean-gherkin-languages: ## Remove gherkin-languages.json and any derived files
	rm -f $(GHERKIN_LANGUAGES_JSON) $(GHERKIN_DIALECTS)
.PHONY: clean-gherkin-languages

mostlyclean:
	rm -rf acceptance
.PHONY: mostlyclean

clean: mostlyclean
.PHONY: clean

# NOTE: This recipe shells out to bash/jq/diff and is intended for the
# Linux/macOS monorepo CI. On Windows (or for a quick cross-platform check of
# the same coverage), run the pure-Dart equivalent instead:
#
#     dart test test/acceptance/gherkin_acceptance_test.dart
#
# which compares ASTs, pickles, sources, and errors for every fixture
# (including the Markdown `.feature.md` fixtures) without needing bash/jq/diff.
acceptance: $(TOKENS) $(ASTS) $(PICKLES) $(ERRORS) $(SOURCES) ## Build acceptance test dir and compare results with reference

acceptance/testdata/%.tokens: ../testdata/% ../testdata/%.tokens
	mkdir -p $(@D)
	$(GHERKIN_GENERATE_TOKENS) $< > $@
	diff --unified $<.tokens $@

acceptance/testdata/%.ast.ndjson: ../testdata/% ../testdata/%.ast.ndjson
	mkdir -p $(@D)
	$(GHERKIN) --predictable-ids --no-source --no-pickles $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq --sort-keys "." $<.ast.ndjson) <(jq --sort-keys "." $@)

acceptance/testdata/%.pickles.ndjson: ../testdata/% ../testdata/%.pickles.ndjson
	mkdir -p $(@D)
	$(GHERKIN) --predictable-ids --no-source --no-ast $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq --sort-keys "." $<.pickles.ndjson) <(jq --sort-keys "." $@)

acceptance/testdata/%.source.ndjson: ../testdata/% ../testdata/%.source.ndjson
	mkdir -p $(@D)
	$(GHERKIN) --no-ast --no-pickles $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq --sort-keys "." $<.source.ndjson) <(jq --sort-keys "." $@)

acceptance/testdata/%.errors.ndjson: ../testdata/% ../testdata/%.errors.ndjson
	mkdir -p $(@D)
	$(GHERKIN) --predictable-ids --no-source $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq --sort-keys "." $<.errors.ndjson) <(jq --sort-keys "." $@)
.PHONY: acceptance

.DELETE_ON_ERROR:

$(GHERKIN_LANGUAGES_JSON):
	mkdir -p $(@D)
	cp ../gherkin-languages.json $@
