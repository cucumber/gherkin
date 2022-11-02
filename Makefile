languages = javascript java ruby go php elixir python perl dotnet

.DEFAULT_GOAL = help

help: ## Show this help
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make <target>\n\nWhere <target> is one of:\n"} /^[$$()% a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)

generate-all: $(patsubst %,generate-%,$(languages)) ## Generate code for all supported languages
.PHONY: generate-code

acceptance-all: $(patsubst %,acceptance-%,$(languages)) ## Run acceptance tests for all supported languages
.PHONY: acceptance-all

clean-all: $(patsubst %,clean-%,$(languages)) ## Clean generated code of all supported languages
.PHONY: clean-all

generate-%: %
	cd $< && make generate
.PHONY: generate-%

acceptance-%: %
	cd $< && make acceptance
.PHONY: acceptance-%

clean-%: %
	cd $< && make clean
.PHONY: clean-%

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