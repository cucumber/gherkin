SHELL := /usr/bin/env bash
ALPINE := $(shell which apk 2> /dev/null)

GOOD_FEATURE_FILES = $(shell find ../testdata/good -name "*.feature")
BAD_FEATURE_FILES  = $(shell find ../testdata/bad -name "*.feature")

TOKENS   = $(patsubst ../testdata/%.feature,acceptance/testdata/%.feature.tokens,$(GOOD_FEATURE_FILES))
ASTS     = $(patsubst ../testdata/%.feature,acceptance/testdata/%.feature.ast.ndjson,$(GOOD_FEATURE_FILES))
ERRORS   = $(patsubst ../testdata/%.feature,acceptance/testdata/%.feature.errors.ndjson,$(BAD_FEATURE_FILES))

M_FILES = $(shell find . -type f \( -iname "*.m" \))

ifdef ALPINE
	DEFAULT_TARGET=skip_build
else
	DEFAULT_TARGET=.compared
endif

.DELETE_ON_ERROR:

default: $(DEFAULT_TARGET)
.PHONY: default

skip_build:
	@echo -e "\x1b[31;01mSKIPPING GHERKIN OBJECTIVE-C BUILD ON ALPINE\x1b[0m"
.PHONY: skip_build

.compared: .built $(TOKENS)
#.compared: .built $(TOKENS) $(ASTS) $(ERRORS)
	touch $@

.built: build/AstGenerator build/TokensGenerator LICENSE
	touch $@

acceptance/testdata/%.feature.tokens: ../testdata/%.feature ../testdata/%.feature.tokens .built
	mkdir -p $(@D)
	bin/gherkin-generate-tokens $< > $@
	diff --unified $<.tokens $@

acceptance/testdata/%.feature.ast.ndjson: ../testdata/%.feature ../testdata/%.feature.ast.ndjson .built
	mkdir -p $(@D)
	bin/gherkin-generate-ast $< | jq --sort-keys "." > $@
	diff --unified <(jq "." $<.ast.ndjson) <(jq "." $@)

acceptance/testdata/%.feature.errors.ndjson: ../testdata/%.feature ../testdata/%.feature.errors.ndjson .built
	mkdir -p $(@D)
	bin/gherkin $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq "." $<.errors.ndjson) <(jq "." $@)

mostlyclean:
	rm -rf .compared .built acceptance
	rm -rf build/
	rm -rf *~
.PHONY: mostlyclean

clean: mostlyclean
.PHONY: clean

clobber: clean
	rm -rf Gherkin/GHParser.m Gherkin/GHParser.h
.PHONY: clobber

define berp-generate-parser =
berp -g ../gherkin.berp -t $< -o $@ --noBOM
endef

Gherkin/GHParser.h: gherkin-objective-c-header.razor ../gherkin.berp
	$(berp-generate-parser)

Gherkin/GHParser.m: gherkin-objective-c-implementation.razor ../gherkin.berp
	$(berp-generate-parser)

build/AstGenerator: Gherkin/GHParser.h Gherkin/GHParser.m $(M_FILES) GherkinLanguages/gherkin-languages.json
	xcodebuild -scheme "AstGenerator" CONFIGURATION_BUILD_DIR=build/

build/TokensGenerator: Gherkin/GHParser.h Gherkin/GHParser.m $(M_FILES) GherkinLanguages/gherkin-languages.json
	xcodebuild -scheme "TokensGenerator" CONFIGURATION_BUILD_DIR=build/
