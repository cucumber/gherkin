Please read [CONTRIBUTING](https://github.com/cucumber/gherkin/blob/master/CONTRIBUTING.md) first.
You should clone the [cucumber/gherkin](https://github.com/cucumber/gherkin) repo if you want
to contribute.

# pre-commit hooks

Make sure to install `pre-commit` and the hooks by running:

```shell
pre-commit install
```

## Run tests

### Using make

Just run `make` from this directory.

### Using pytest

Just run `pytest` from this directory (you need to `pip install -r requirements.txt` first).

Keep in mind that this will only run unit tests. The acceptance tests are only
run when you build with `make`.
