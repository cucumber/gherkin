languages = c dart dotnet elixir go java javascript perl php python ruby

.DEFAULT_GOAL = help

help: ## Show this help
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make <target>\n\nWhere <target> is one of:\n"} /^[$$()% a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)

acceptance: $(patsubst %,acceptance-%,$(languages)) ## Build acceptance test dir and compare results with reference for all supported languages
.PHONY: acceptance

acceptance-%: %
	cd $< && make acceptance
.PHONY: acceptance-%

clean: $(patsubst %,clean-%,$(languages)) ## Remove all build artifacts and files generated by the acceptance tests  for all supported languages
.PHONY: clean

clean-%: %
	cd $< && make clean
.PHONY: clean-%

generate: $(patsubst %,generate-%,$(languages)) ## Generate parsers for all supported languages
.PHONY: generate

generate-%: %
	cd $< && make generate
.PHONY: generate-%

clean-generate: $(patsubst %,clean-generate-%,$(languages)) ## Clean generated parsers for all supported languages
.PHONY: clean-generate

clean-generate-%: %
	cd $< && make clean-generate
.PHONY: clean-generate-%

copy-gherkin-languages: $(patsubst %,copy-gherkin-languages-%,$(languages)) ## Copy gherkin-languages.json to all supported languages
.PHONY: copy-gherkin-languages

copy-gherkin-languages-%: %
	cd $< && make copy-gherkin-languages
.PHONY: generate-%

clean-gherkin-languages: $(patsubst %,clean-gherkin-languages-%,$(languages)) ## Clean gherkin-languages.json
.PHONY: clean-gherkin-languages

clean-gherkin-languages-%: %
	cd $< && make clean-gherkin-languages
.PHONY: clean-gherkin-languages-%

docker-run:
	[ -d "${HOME}/.m2/repository" ] || mkdir -p "${HOME}/.m2/repository"
	docker run \
	  --publish "6006:6006" \
	  --volume "${shell pwd}":/app \
	  --volume "${HOME}/.m2/repository":/home/cukebot/.m2/repository \
	  --user 1000 \
	  --rm \
	  --interactive \
	  --tty \
	  cucumber/cucumber-build:0.13.0 \
	  bash
.PHONY: