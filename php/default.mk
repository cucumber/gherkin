# Please update /.templates/php/default.mk and sync:
#
#     source scripts/functions.sh && rsync_files
#
SHELL := /usr/bin/env bash
PHP_SOURCE_FILES = $(shell find . -name "*.php")

### COMMON stuff for all platforms

BERP_VERSION = 1.3.0
BERP_GRAMMAR = gherkin.berp

define berp-generate-parser =
-! dotnet tool list --tool-path /usr/bin | grep "berp\s*$(BERP_VERSION)" && dotnet tool update Berp --version $(BERP_VERSION) --tool-path /usr/bin
berp -g $(BERP_GRAMMAR) -t $< -o $@ --noBOM
endef

### Common targets for all functionalities implemented on php

default: .tested
.PHONY: default

clean:
	rm -rf .tested .deps .codegen
	rm -rf vendor composer.lock
.PHONY: clean

.tested: .deps $(PHP_SOURCE_FILES)
	vendor/bin/php-cs-fixer --dry-run --diff fix
	vendor/bin/psalm --no-cache
	vendor/bin/phpunit
	touch $@

.deps: vendor .codegen
	touch $@

.codegen:
	touch $@

vendor: composer.json
	composer update ${COMPOSER_FLAGS}
