SHELL := /usr/bin/env bash
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	dotnet_build_opts := --framework netcoreapp1.1
endif

GOOD_FEATURE_FILES = $(shell find testdata/good -name "*.feature")
BAD_FEATURE_FILES  = $(shell find testdata/bad -name "*.feature")

TOKENS   = $(patsubst testdata/%.feature,acceptance/testdata/%.feature.tokens,$(GOOD_FEATURE_FILES))
ASTS     = $(patsubst testdata/%.feature,acceptance/testdata/%.feature.ast.ndjson,$(GOOD_FEATURE_FILES))
PICKLES  = $(patsubst testdata/%.feature,acceptance/testdata/%.feature.pickles.ndjson,$(GOOD_FEATURE_FILES))
SOURCES  = $(patsubst testdata/%.feature,acceptance/testdata/%.feature.source.ndjson,$(GOOD_FEATURE_FILES))
ERRORS   = $(patsubst testdata/%.feature,acceptance/testdata/%.feature.errors.ndjson,$(BAD_FEATURE_FILES))

CS_FILES = $(shell find . -type f \( -iname "*.cs" ! -iname "*.NETFramework*" \))

install: all
.PHONY: install

all: .compared
.PHONY: all

.compared: .sln_built_debug $(TOKENS) $(ASTS) $(PICKLES) $(SOURCES) $(ERRORS)
	touch $@

acceptance/testdata/%.feature.tokens: testdata/%.feature testdata/%.feature.tokens .sln_built_debug
	mkdir -p `dirname $@`

	# bin/gherkin-generate-tokens net45 $< > $@
	# diff --unified $<.tokens $@

	rm -f $@

	bin/gherkin-generate-tokens netcoreapp1.1 $< > $@
	diff --unified $<.tokens $@
.DELETE_ON_ERROR: acceptance/testdata/%.feature.tokens

acceptance/testdata/%.feature.pickles.ndjson: testdata/%.feature testdata/%.feature.pickles.ndjson .sln_built_debug
	mkdir -p `dirname $@`
	bin/gherkin netcoreapp1.1 --no-source --no-ast $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq "." $<.pickles.ndjson) <(jq "." $@)
.DELETE_ON_ERROR: acceptance/testdata/%.feature.pickles.ndjson

acceptance/testdata/%.feature.source.ndjson: testdata/%.feature testdata/%.feature.source.ndjson .sln_built_debug
	mkdir -p `dirname $@`
	bin/gherkin netcoreapp1.1 --no-pickles --no-ast $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq "." $<.source.ndjson) <(jq "." $@)
.DELETE_ON_ERROR: acceptance/testdata/%.feature.source.ndjson

acceptance/testdata/%.feature.ast.ndjson: testdata/%.feature testdata/%.feature.ast.ndjson .sln_built_debug
	mkdir -p `dirname $@`

	# bin/gherkin net45 --no-source --no-pickles $< | jq --sort-keys --compact-output "." > $@
	# diff --unified <(jq "." $<.ast.ndjson) <(jq "." $@)

	rm -f $@

	bin/gherkin netcoreapp1.1 --no-source --no-pickles $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq "." $<.ast.ndjson) <(jq "." $@)
.DELETE_ON_ERROR: acceptance/testdata/%.feature.ast.ndjson

acceptance/testdata/%.feature.errors.ndjson: testdata/%.feature testdata/%.feature.errors.ndjson .sln_built_debug
	mkdir -p `dirname $@`

	# bin/gherkin net45 --no-pickles $< | jq --sort-keys --compact-output "." > $@
	# diff --unified $<.errors.ndjson $@

	rm -f $@

	bin/gherkin netcoreapp1.1 --no-pickles $< | jq --sort-keys --compact-output "." > $@
	diff --unified $<.errors.ndjson $@
.DELETE_ON_ERROR: acceptance/testdata/%.feature.errors.ndjson

clean:
	rm -rf .compared .built acceptance Gherkin/Parser.cs
	rm -rf */bin
	rm -rf */obj
	rm -rf */packages
	rm -rf ./output
.PHONY: clean

Gherkin/Parser.cs: gherkin.berp gherkin-csharp.razor berp/berp.exe
	mono berp/berp.exe -g gherkin.berp -t gherkin-csharp.razor -o $@

.sln_built_debug: Gherkin/Parser.cs $(CS_FILES) Gherkin/gherkin-languages.json
	echo "Building on $(UNAME)"

	dotnet --version
	dotnet restore
	dotnet build $(dotnet_build_opts)

	# dotnet publish --output output/netstandard1.5  --framework netstandard1.5 Gherkin.CLI/
	# dotnet publish --output output/net45           --framework net45          Gherkin.CLI/
	# dotnet publish --output output/netcoreapp1.1   --framework netcoreapp1.1  Gherkin.CLI/

	# dotnet publish --output output/netstandard1.5  --framework netstandard1.5 Gherkin.TokensGenerator/
	# dotnet publish --output output/net45           --framework net45          Gherkin.TokensGenerator/
	# dotnet publish --output output/netcoreapp1.1   --framework netcoreapp1.1  Gherkin.TokensGenerator/

	touch $@
