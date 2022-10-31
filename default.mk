# Please update /.templates/default.mk and sync:
#
#     source scripts/functions.sh && rsync_files
#
SHELL := /usr/bin/env bash
ALPINE = $(shell which apk 2> /dev/null)
LIBNAME = $(shell basename $$(pwd))
LANGUAGES ?= $(wildcard */)

# https://stackoverflow.com/questions/2483182/recursive-wildcards-in-gnu-make
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

default: $(patsubst %,default-%,$(LANGUAGES))
.PHONY: default

default-%: %
	if [[ -d $< ]]; then cd $< && make default; fi
.PHONY: default-%

# Need to declare these phonies to avoid errors for packages without a particular language
.PHONY: c dotnet go java javascript objective-c perl python ruby

clean: $(patsubst %,clean-%,$(LANGUAGES))
.PHONY: clean

clean-%: %
	if [[ -d $< ]]; then cd $< && make clean; fi
.PHONY: clean-%
