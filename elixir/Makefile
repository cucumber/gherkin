SHELL := /usr/bin/env bash

.DEFAULT_GOAL = help
GHERKIN = bundle exec bin/gherkin
GHERKIN_GENERATE_TOKENS = bundle exec bin/gherkin-generate-tokens

help: ## Show this help
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make <target>\n\nWhere <target> is one of:\n"} /^[$$()% a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)

clean: ## Remove automatically generated files and related artifacts
	rm -f priv/gherkin_languages.json
	rm -f lib/gherkin/parser.ex
	rm -rf acceptance
	rm -rf _build
	rm -rf deps

.DELETE_ON_ERROR:

generate: priv/gherkin_languages.json lib/gherkin/parser.ex ## Generate Gherkin parser code

acceptance: generate ## Build acceptance test dir and compare results with reference
	mix local.hex --force
	mix deps.get
	mix test
	touch $@

priv/gherkin_languages.json:
	cp ../gherkin-languages.json $@

lib/gherkin/parser.ex: gherkin-elixir.razor ../gherkin.berp
	berp -g ../gherkin.berp -t $< -o $@ --noBOM
