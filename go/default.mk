SHELL := /usr/bin/env bash
ALPINE := $(shell which apk 2> /dev/null)
GOPATH := $(shell go env GOPATH)
PATH := $(PATH):$(GOPATH)/bin
GO_SOURCE_FILES := $(shell find . -name "*.go" | sort)
LIBNAME := $(shell cat .subrepo | cut -d'/' -f2)
GOX_LDFLAGS := "-X main.version=${TRAVIS_TAG}"
EXES := $(shell find dist -name '$(LIBNAME)-*')
UPX_EXES = $(patsubst dist/$(LIBNAME)-%,dist_compressed/$(LIBNAME)-%,$(EXES))

default: .gofmt .tested
.PHONY: default

ifneq (,$(wildcard ./cmd/main.go))
ifndef ALPINE
# Cross-compile executables if there is a CLI. Disabled on Alpine Linux builds
# (monorepo build in Docker) where cross compilation fails for certain platforms.
# Subrepo builds don't run in Docker/Alpine, so cross compile will happen there.
default: .dist
endif
endif

.dist: .deps dist/$(LIBNAME)-darwin-amd64
	touch $@

dist/$(LIBNAME)-%: $(GO_SOURCE_FILES)
	mkdir -p dist
	gox -ldflags $(GOX_LDFLAGS) -output "dist/$(LIBNAME)-{{.OS}}-{{.Arch}}" -rebuild ./cmd

.dist-compressed: $(UPX_EXES)
	touch $@

dist_compressed/$(LIBNAME)-%: dist/$(LIBNAME)-%
	mkdir -p dist_compressed
	# requires upx in PATH to compress supported binaries
	# may produce an error ARCH not supported
	-upx $< -o $@

	# Test the integrity
	if [ -f "$@" ]; then upx -t $@ || rm $@; fi

.gofmt: $(GO_SOURCE_FILES)
	gofmt -w $^
	touch $@

.tested: .deps $(GO_SOURCE_FILES)
	go test ./...
	touch $@

clean: clean-go
.PHONY: clean

clean-go:
	rm -rf .deps .tested dist/* dist_compressed
.PHONY: clean-go
