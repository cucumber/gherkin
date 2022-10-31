# Please update /.templates/java/default.mk and sync:
#
#     source scripts/functions.sh && rsync_files
#
SHELL := /usr/bin/env bash
JAVA_SOURCE_FILES = $(shell find . -name "*.java")
IS_TESTDATA = $(findstring -testdata,${CURDIR})

# https://stackoverflow.com/questions/2483182/recursive-wildcards-in-gnu-make
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

default: .tested
.PHONY: default

.codegen:
	touch $@

.tested: .deps .built
	touch $@

.built: pom.xml $(JAVA_SOURCE_FILES) .codegen
	mvn install
	touch $@

.deps:
	touch $@

clean: clean-java
.PHONY: clean

clean-java:
	rm -rf target .deps .tested* .built acceptance .codegen
	mvn clean
.PHONY: clean-java

### COMMON stuff for all platforms

BERP_VERSION = 1.3.0
BERP_GRAMMAR = gherkin.berp

define berp-generate-parser =
-! dotnet tool list --tool-path /usr/bin | grep "berp\s*$(BERP_VERSION)" && dotnet tool update Berp --version $(BERP_VERSION) --tool-path /usr/bin
berp -g $(BERP_GRAMMAR) -t $< -o $@ --noBOM
endef
