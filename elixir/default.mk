SHELL := /usr/bin/env bash
ELIXIR_SOURCE_FILES = $(shell find . -name "*.ex")

default: .tested

.tested: .deps $(ELIXIR_SOURCE_FILES)
	mix test
	touch $@

.deps:
	mix local.hex --force
	mix deps.get
	touch $@

update-dependencies:
	@echo -e "\033[0;31mPlease update dependencies for elixir manually in mix.exs!! Check https://hex.pm/ for the latest version.\033[0m"
	@echo -e "\033[0;31mSome packages require some options (such as ex_doc), check the package its readme / hexdocs.\033[0m"
.PHONY: update-dependencies

remove-local-dependencies:
	cat mix.exs | sed 's|{:cucumber_messages, "\([^"]*\)", path: "../../messages/elixir"}|{:cucumber_messages, "\1"}|' > mix.exs.tmp
	mv mix.exs.tmp mix.exs
.PHONY: remove-local-dependencies

pre-release: remove-local-dependencies update-version update-dependencies clean default
	[ -f '/home/cukebot/import-gpg-key.sh' ] && /home/cukebot/import-gpg-key.sh
.PHONY: pre-release

update-version:
ifdef NEW_VERSION
	sed -Ei 's/@vsn "[^"]+"/@vsn "$(NEW_VERSION)"/' mix.exs
else
	@echo -e "\033[0;31mNEW_VERSION is not defined. Can't update version :-(\033[0m"
	exit 1
endif
.PHONY: update-version

publish: .deps
ifdef HEX_API_KEY
	mix hex.publish --yes
else
	@echo -e "\033[0;31mHEX_API_KEY is not defined. Can't update version :-(\033[0m"
	exit 1
endif

.PHONY: publish

post-release:
	cat mix.exs | sed 's|{:cucumber_messages, "\([^"]*\)"}|{:cucumber_messages, "\1", path: "../../messages/elixir"}|' > mix.exs.tmp
	mv mix.exs.tmp mix.exs
.PHONY: post-release

clean:
	rm -rf _build deps .deps .tested
