SHELL := /usr/bin/env bash

GHERKIN_LANGUAGES_JSON = assets/gherkin-languages.json

.DEFAULT_GOAL = help

help: ## Show this help
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make <target>\n\nWhere <target> is one of:\n"} /^[$$()% a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)
.PHONY: help

generate:
	echo "Nothing to do"
.PHONY: generate

clean-generate: ## Remove generated Gherkin parser files ## Generate gherkin parser files
	rm -f $(GHERKIN_PARSER)
.PHONY: clean-generate

copy-gherkin-languages: $(GHERKIN_LANGUAGES_JSON) ## Copy gherkin-languages.json and/or generate derived files
.PHONY: copy-gherkin-languages

clean-gherkin-languages: ## Remove gherkin-languages.json and any derived files
	rm -f $(GHERKIN_LANGUAGES_JSON)
.PHONY: clean-gherkin-languages

clean:
	echo "Nothing to do"
.PHONY: clean

acceptance:
	echo "Nothing to do"

.DELETE_ON_ERROR:

$(GHERKIN_LANGUAGES_JSON):
	cp ../gherkin-languages.json $@