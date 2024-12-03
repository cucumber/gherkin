# Contributing to Gherkin

Gherkin is implemented in several languages. Each implementation is
in a separate subdirectory in this repository.

## Project organisation

Each subdirectory is a stand-alone project using the preferred tools for
that language, you can find more detailed information in `<language>/CONTRIBUTING.md`.

Each gherkin implementation depends on two common files.
 * `gherkin-langauges.json` containing translations of the Gherkin Keywords
 * `gherkin.berp` from which a parser is generated.

To reduce the complexity of common tasks: copying and/or generating
localisations and generating the parser is done separately from building each project.  

## Contributing changes

* Create a feature branch for your change.
* Don't lump unrelated changes together.
* If you change code, please make sure all implementations are changed accordingly.
  * If you don't to do this, we might reject your patch because the burden to keep parsers in sync is now on us.

## Generating parsers

*Either* start a docker container

```shell
docker build --tag berp-env . 
docker run --rm --interactive --tty --volume ".:/app" berp-env
```

*Or* install on your system

* .NET 8.0 (to run `berp` to generate parsers)
* `berp` (install with `dotnet tool update Berp --version 1.4.0 --tool-path /usr/bin` )
* `make`
* `diff`

With either of these done run:

```shell
make clean-generate
make generate
```

## Adding or updating an i18n language

1) Edit `gherkin-languages.json`.

2) Distribute the changes to the different parser implementations:

    *Either* start a docker container. See [Generating Parsers](#generating-parsers)

    *Or* install on your system

   * `make`
   * `jq` (>= 1.4 for `--sort-keys` option)

    Then with either of these done run

    ```shell
    make clean-gherkin-languages
    make copy-gherkin-languages
    ```

3) Make a pull request with the changed files.

## Running tests

Each subproject has its own unit tests that are run during the build of that project.

In addition to these tests, `make acceptance` will run acceptance tests that verify the output of:

* the scanner
* the parser
* the compiler (WIP)

This is done by consuming the `*.feature` files under `../testdata` and comparing the actual
output with expected output (`*.feature.tokens` and `*.feature.ast.json` files) using `diff`.

`make` will remove the generated file unless it is identical to the expected file so that
it will try to regenerate it the next time you run `make`.

When all files are identical and successfully compared, `make` will create the `.compared`
file, indicating that the acceptance tests passed.

## Consistency between implementations

TL;DR anyone who only knows one of the supported programming languages should be
able to fix a bug or add a feature in all the other implementations. - By virtue of
finding their way around a consistently organised codebase.

As of May 2016 Gherkin is implemented in 8 languages. This number is likely to
increase to a dozen within a year or two. Very few programmers are intimate with
all those languages. Therefore, in order to make it as easy as possible to refactor,
fix bugs, add features and release packages it is essential that all implementations
have a similar structure.

For example, I (Aslak) don't currently know go at all, and very little Python.
Still, I have been able to fix bugs and refactor the go and python code simply
because I know where to find stuff since all implementations follow the same structure.

If one implementation looks completely different, this becomes a huge burden that
will slow everything down.

So for this reason, please don't start a new implementation that does not use Berp,
or add a feature in one implementation without also doing it in all the other
implementations. Don't refactor the code to follow some nice design pattern if
it makes the code so different from the other implementations that it can no longer
be maintained by someone who doesn't know the language.

## Implementing a parser for a new language

First off, fork the repository and create a branch for the new language.

Create a new directory for the new language and copy the `Makefile` from one
of the existing implementations. Now, modify the parts of the `Makefile` that
generates the `Parser.x` file, referring to the `gherkin-x.razor` file you're
about to create.

When you run `make generate` it should complain that `gherkin-x.razor` does not exist.

Now, copy a `.razor` file from one of the other implementations.

Your `.built` target should compile your code (if necessary) and run unit tests.
You won't need a lot of unit tests (the cross-platform acceptance tests are pretty
good), but writing a few during development might help you progress.

You'll spend quite a bit of time fiddling with the `.razor` template to make it
generate code that is syntactically correct.

When you get to that stage, `make clean acceptance` will run the acceptance tests, which iterate
over all the `.feature` files under `../testdata`, passes them through your
`bin/gherkin-generate-tokens` and `bin/gherkin-generate-ast` command-line programs,
and compares the output using `diff`.

You'll start out with lots of errors, and now you just code until all acceptance tests
pass!

Then send us a pull-request :-)

And if you're stuck - please shoot message to the #commiters channel in the 
[Cucumber Discord](https://cucumber.io/docs/community/get-in-touch/#discord).

## Make a release

See [RELEASING.md](./RELEASING.md)

## Verify all of Cucumber's i18n examples

If you have [cucumber-ruby](https://github.com/cucumber/cucumber-ruby) cloned
next to the gherkin directory, try processing all of the files.

With just the scanner:

    [LANGUAGE]/bin/gherkin-generate-tokens `find ../cucumber-ruby/examples -name "*.feature"`

With the parser:

    [LANGUAGE]/bin/gherkin-generate-ast `find ../cucumber-ruby/examples -name "*.feature"`

## Adding or changing good testdata

Test data for acceptance testing are available in the top-level `testdata`

### Approach 1

1) Work in a specific `gherkin/<lang>` folder
1) Create empty testdata `ndjson`/`tokens` files (or delete the contents if you are updating existing tests)
    * `<test>.feature.ast.ndjson`
   * `<test>.feature.pickles.ndjson`
   * `<test>.feature.source.ndjson`
   * `<test>.feature.tokens`
1) Run `make` and watch it fail
1) Inspect the diff error to approve the output
    * Copy approved output to the matching, empty `ndjson`/`tokens` file
    * Repeat until the build succeeds

### Approach 2

1) Add/edit a `.feature` file in `testdata/good`

2) Generate the tokens:

    *For example:*

    cd [LANGUAGE]
    bin/gherkin-generate-tokens \
    ../testdata/good/new_file.feature > \
    ../testdata/good/new_file.feature.tokens

3) Inspect the generated `.feature.tokens` file manually to see if it's good.

4) Generate the ast:
    cd [LANGUAGE]
    bin/gherkin --no-source --no-pickles \
    ../testdata/good/new_file.feature | \
    jq --sort-keys --compact-output "." > \
    ../testdata/good/new_file.feature.ast.ndjson

5) Inspect the generated `.feature.ast.ndjson` file manually to see if it's good.

6) Generate the pickles:

    cd [LANGUAGE]
    bin/gherkin --no-source --no-ast \
    ../testdata/good/new_file.feature | \
    jq --sort-keys --compact-output "." > \
    ../testdata/good/new_file.feature.pickles.ndjson

7) Inspect the generated `.feature.pickles.json` file manually to see if it's good.

8) Run `make acceptance` from the root directory to verify that all parsers parse it ok.
