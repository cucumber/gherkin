SHELL := /usr/bin/env bash

GOOD_FEATURE_FILES = $(shell find ../testdata/good -name "*.feature")
BAD_FEATURE_FILES  = $(shell find ../testdata/bad -name "*.feature")

TOKENS       = $(patsubst ../testdata/%,acceptance/testdata/%.tokens,$(GOOD_FEATURE_FILES))
ASTS         = $(patsubst ../testdata/%,acceptance/testdata/%.ast.ndjson,$(GOOD_FEATURE_FILES))
PICKLES      = $(patsubst ../testdata/%,acceptance/testdata/%.pickles.ndjson,$(GOOD_FEATURE_FILES))
SOURCES      = $(patsubst ../testdata/%,acceptance/testdata/%.source.ndjson,$(GOOD_FEATURE_FILES))
ERRORS       = $(patsubst ../testdata/%,acceptance/testdata/%.errors.ndjson,$(BAD_FEATURE_FILES))

SRC_FILES = $(shell find src -name "*.[ch]*")

GHERKIN=stage/bin/gherkin
RUN_GHERKIN=$(GHERKIN)
GHERKIN_GENERATE_TOKENS=stage/bin/gherkin-generate-tokens
RUN_GHERKIN_GENERATE_TOKENS=$(GHERKIN_GENERATE_TOKENS)

HERE = $(shell pwd)
CMAKE_BUILDROOT = $(HERE)/build/root
CMAKELISTS = $(shell find src -name CMakeLists.txt)

.DELETE_ON_ERROR:

default: .compared
.PHONY: default

acceptance: .compared ## Build acceptance test dir and compare results with reference

.compared: .built $(TOKENS) $(ASTS) $(PICKLES) $(ERRORS) $(SOURCES) .run
	touch $@

generate: ./include/gherkin/rule_type.hpp ./include/gherkin/parser.hpp ## Generate gherkin parser files

clean-generate: ## Remove generated Gherkin parser files ## Generate gherkin parser files
	rm -f ./include/gherkin/rule_type.hpp ./include/gherkin/parser.hpp
.PHONY: clean-generate

copy-gherkin-languages: src/lib/gherkin/dialect.cpp ## Copy gherkin-languages.json and/or generate derived files
	echo "Nothing to do"

clean-gherkin-languages: ## Remove gherkin-languages.json and any derived files
	rm -f src/lib/gherkin/dialect.cpp

.built: generate $(SRC_FILES) .configured
	cmake --build build/gherkin --parallel $(NPROCS)
	cmake --install build/gherkin
	touch $@

.configured:
	rm -rf build/gherkin && mkdir -p build/gherkin
	cmake \
	    -DCMAKE_PREFIX_PATH=$(CMAKE_BUILDROOT) \
	    -DCMAKE_INSTALL_PREFIX=$(HERE)/stage \
	    -S . \
	    -B build/gherkin \
	    --toolchain cmake/toolchains/ext.cmake
	touch $@

clean:
	rm -rf .compared .configured .built .run acceptance build ext
.PHONY: clean

.run: $(GHERKIN) $(GOOD_FEATURE_FILES)
	$(RUN_GHERKIN) $(GOOD_FEATURE_FILES) | jq . > /dev/null
	touch $@

define berp-generate-parser =
berp -g ../gherkin.berp -t $< -o $@ --noBOM
endef

./include/gherkin/rule_type.hpp: gherkin-cpp-rule-type.razor gherkin.berp
	$(berp-generate-parser)

./include/gherkin/parser.hpp: gherkin-cpp-parser.razor gherkin.berp
	$(berp-generate-parser)

src/lib/gherkin/dialect.cpp: ../gherkin-languages.json dialect.cpp.jq
	cat $< | jq -f dialect.cpp.jq -r -c > $@

acceptance/testdata/%.feature.tokens: ../testdata/%.feature ../testdata/%.feature.tokens $(GHERKIN_GENERATE_TOKENS)
	mkdir -p $(@D)
	echo $(RUN_GHERKIN_GENERATE_TOKENS)
	$(RUN_GHERKIN_GENERATE_TOKENS) $< > $@
	diff --strip-trailing-cr --unified $<.tokens $@

acceptance/testdata/%.feature.ast.ndjson: ../testdata/%.feature ../testdata/%.feature.ast.ndjson $(GHERKIN)
	mkdir -p $(@D)
	$(RUN_GHERKIN) --no-source --no-pickles $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq "." $<.ast.ndjson) <(jq "." $@)

acceptance/testdata/%.feature.errors.ndjson: ../testdata/%.feature ../testdata/%.feature.errors.ndjson $(GHERKIN)
	mkdir -p $(@D)
	$(RUN_GHERKIN) --no-source --no-pickles $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq "." $<.errors.ndjson) <(jq "." $@)

acceptance/testdata/%.feature.pickles.ndjson: ../testdata/%.feature ../testdata/%.feature.pickles.ndjson $(GHERKIN)
	mkdir -p $(@D)
	$(RUN_GHERKIN) --no-source --no-ast $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq "." $<.pickles.ndjson) <(jq "." $@)

acceptance/testdata/%.feature.source.ndjson: ../testdata/%.feature ../testdata/%.feature.source.ndjson .built
	mkdir -p $(@D)
	$(RUN_GHERKIN) --no-ast --no-pickles $< | jq --sort-keys --compact-output "." > $@
	diff --unified <(jq "." $<.source.ndjson) <(jq "." $@)

install-deps:
	./scripts/build-externals deps.txt
.PHONY: install-deps
