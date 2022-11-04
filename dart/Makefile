SHELL := /usr/bin/env bash

GHERKIN_LANGUAGES_JSON = assets/gherkin-languages.json

.DEFAULT_GOAL = help

help: ## Show this help
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make <target>\n\nWhere <target> is one of:\n"} /^[$$()% a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)

generate:
	echo "Nothing to do"

clean-generate: ## Remove generated Gherkin parser files ## Generate gherkin parser files
	rm -f $(GHERKIN_PARSER)

copy-gherkin-languages: $(GHERKIN_LANGUAGES_JSON) ## Copy gherkin-languages.json and/or generate derived files

clean-gherkin-languages: ## Remove gherkin-languages.json and any derived files
	rm -f $(GHERKIN_LANGUAGES_JSON)

.DELETE_ON_ERROR:

$(GHERKIN_LANGUAGES_JSON):
	cp ../gherkin-languages.json $@