#!/usr/bin/env bash

F=$1
N=$(basename $F)

stage/bin/gherkin \
    --no-source --no-pickles \
    $F \
    | jq \
    --sort-keys --compact-output "." \
    > acceptance/testdata/good/$N.ast.ndjson

meld \
    <(jq "." $F.ast.ndjson) \
    <(jq "." acceptance/testdata/good/$N.ast.ndjson)
