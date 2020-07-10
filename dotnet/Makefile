SHELL := /usr/bin/env bash
ALPINE := $(shell which apk 2> /dev/null)
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	dotnet_build_opts := --framework netcoreapp2.0
endif

GOOD_FEATURE_FILES = $(shell find testdata/good -name "*.feature")
BAD_FEATURE_FILES  = $(shell find testdata/bad -name "*.feature")

TOKENS   = $(patsubst testdata/%.feature,acceptance/testdata/%.feature.tokens,$(GOOD_FEATURE_FILES))
ASTS     = $(patsubst testdata/%.feature,acceptance/testdata/%.feature.ast.ndjson,$(GOOD_FEATURE_FILES))
PICKLES  = $(patsubst testdata/%.feature,acceptance/testdata/%.feature.pickles.ndjson,$(GOOD_FEATURE_FILES))
SOURCES  = $(patsubst testdata/%.feature,acceptance/testdata/%.feature.source.ndjson,$(GOOD_FEATURE_FILES))
ERRORS   = $(patsubst testdata/%.feature,acceptance/testdata/%.feature.errors.ndjson,$(BAD_FEATURE_FILES))

CS_FILES = $(shell find . -type f \( -iname "*.cs" ! -iname "*.NETFramework*" \))

ifdef ALPINE
	DEFAULT_TARGET=skip_build
else
	DEFAULT_TARGET=.compared
endif

.DELETE_ON_ERROR:

default: $(DEFAULT_TARGET)
.PHONY: default

skip_build:
	@echo -e "\x1b[31;01mSKIPPING GHERKIN .NET BUILD ON ALPINE\x1b[0m"
.PHONY: skip_build

.compared: .sln_built_debug .run_tests $(TOKENS) $(ASTS) $(PICKLES) $(SOURCES) $(ERRORS)
	touch $@

clean:
	rm -rf .compared .built .run_tests acceptance .sln_built_debug
	rm -rf */bin
	rm -rf */obj
	rm -rf */packages
	rm -rf ./output
.PHONY: clean

clobber: clean
	rm -rf Gherkin/Parser.cs
.PHONY: clobber

Gherkin/Parser.cs: gherkin.berp gherkin-csharp.razor
	mono  /var/lib/berp/1.1.1/tools/net471/Berp.exe -g gherkin.berp -t gherkin-csharp.razor -o $@

.sln_built_debug: Gherkin/Parser.cs $(CS_FILES) Gherkin/gherkin-languages.json
	echo "Building on $(UNAME)"

	dotnet build

	touch $@

.run_tests:

	cd Gherkin.Specs; dotnet test --no-build -f netcoreapp2.0
	touch $@
