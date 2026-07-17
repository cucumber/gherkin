docker run --rm --volumes-from $(hostname) --workdir /workspaces/gherkin/cpp --entrypoint /workspaces/gherkin/cpp/.berp-entrypoint.sh berp-env make clean-generate generate
