# Please update /.templates/default.mk and sync:
#
#     source scripts/functions.sh && rsync_files
#
ALPINE = $(shell which apk 2> /dev/null)
LIBNAME = $(shell basename $$(pwd))

default: $(patsubst %/Makefile,default-%,$(MAKEFILES))
.PHONY: default

default-%: %
	cd $< && make default
.PHONY: default-%

update-dependencies: $(patsubst %/Makefile,update-dependencies-%,$(MAKEFILES))
.PHONY: update-dependencies

update-dependencies-%: %
	cd $< && make update-dependencies
.PHONY: update-dependencies-%

update-version: $(patsubst %/Makefile,update-version-%,$(MAKEFILES))

update-version: update-changelog

update-changelog:
ifdef NEW_VERSION
	cat CHANGELOG.md | ../scripts/update_changelog.sh $(NEW_VERSION) > CHANGELOG.md.tmp
	mv CHANGELOG.md.tmp CHANGELOG.md
else
	@echo -e "\033[0;31mNEW_VERSION is not defined. Can't update version :-(\033[0m"
	exit 1
endif
.PHONY: update-changelog

update-version-%: %
	cd $< && make update-version
.PHONY: update-version-%

release: update-version clean default publish release-tag
.PHONY: release

publish: $(patsubst %/Makefile,publish-%,$(MAKEFILES))
.PHONY: publish

publish-%: %
	cd $< && make publish
.PHONY: publish-%

post-release: $(patsubst %/Makefile,post-release-%,$(MAKEFILES))
.PHONY: post-release

post-release: commit-post-release-and-push-all

post-release-%: %
	cd $< && make post-release
.PHONY: post-release-%

release-tag:
	git commit -am "Release $(LIBNAME) v$(NEW_VERSION)"
	git tag -s "$(LIBNAME)/v$(NEW_VERSION)" -m "Release $(LIBNAME) v$(NEW_VERSION)"
.PHONY: release-tag

commit-post-release-and-push-all:
	git commit -am "Post release $(LIBNAME) v$(NEW_VERSION)"
	git push && git push --tags
.PHONY: commit-post-release-and-push-all

clean: $(patsubst %/Makefile,clean-%,$(MAKEFILES))
.PHONY: clean

clean-%: %
	cd $< && make clean
.PHONY: clean-%
