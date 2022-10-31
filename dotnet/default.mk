# Please update /.templates/dotnet/default.mk and sync:
#
#     source scripts/functions.sh && rsync_files
#
SHELL := /usr/bin/env bash
ALPINE := $(shell which apk 2> /dev/null)
SLN_FILES = $(shell find . -name "*.sln")
CSPROJ_FILES = $(shell find . -name "*.csproj")
CSHARP_SOURCE_FILES = $(shell find . -name "*.cs")

# https://stackoverflow.com/questions/2483182/recursive-wildcards-in-gnu-make
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

default: .packed
.PHONY: default

.built: $(SLN_FILES) $(CSPROJ_FILES) $(CSHARP_SOURCE_FILES) .generated
	dotnet build -c Release -p:SnapshotSuffix="$(SNAPSHOT_SUFFIX)"
	touch $@

.generated:
	touch $@

.tested: .built
	dotnet test
	touch $@

.packed: .tested
	touch $@

clean: clean-dotnet
.PHONY: clean

clean-dotnet:
	rm -rf .generated .tested .built .packed
	rm -rf */bin
	rm -rf */obj
.PHONY: clean-dotnet

### COMMON stuff for all platforms

BERP_VERSION = 1.3.0
BERP_GRAMMAR = gherkin.berp

define berp-generate-parser =
-! dotnet tool list --tool-path /usr/bin | grep "berp\s*$(BERP_VERSION)" && dotnet tool update Berp --version $(BERP_VERSION) --tool-path /usr/bin
berp -g $(BERP_GRAMMAR) -t $< -o $@ --noBOM
endef
