SHELL := /usr/bin/env bash

.DEFAULT_GOAL = help

help: ## Show this help
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make <target>\n\nWhere <target> is one of:\n"} /^[$$()% a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)

generate:
	echo "Nothing to do"

clean-generate:
	echo "Nothing to do"

copy-gherkin-languages: assets/gherkin-languages.json

clean-gherkin-languages:
	rm -f assets/gherkin-languages.json

.DELETE_ON_ERROR:

assets/gherkin-languages.json:
	cp ../gherkin-languages.json $@
