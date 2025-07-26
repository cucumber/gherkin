# Contributing

Thank you for your interest in contributing to `gherkin-official`, the official Python parser implementation for Gherkin! This guide will help you get set up and understand our development workflow. Make sure to read the [language-agnostic contributing guidelines](https://github.com/cucumber/gherkin/blob/3322dba1bff0ffd94ad32c25be96c0af6af898a6/CONTRIBUTING.md) before proceeding.

## 🚀 Quick Start

Using [`uv`](https://docs.astral.sh/uv/) is recommended for contributing with this project, though you can also install dependencies via `pip` (use `pip install . --group dev` with v25.1+) or your preferred tool.

First change to the directory containing the Python implementation and install development dependencies.

```console
cd python
uv sync
```

At the root of the repository, install pre-commit hooks to automatically validate linting and formatting of your Python code with every commit.

```console
cd ..
uv run pre-commit install
```

Unit tests can run via `pytest`.

```console
uv run pytest
```

## 🧪 Running across Python versions

Tests and linting can be validating across supported Python versions through [`tox`](https://tox.wiki/) - preferably via [`tox-uv`](https://github.com/tox-dev/tox-uv).

```console
# Run unit tests on all supported Python versions
tox

# Test on a specific Python version
tox -e py312

# Run test coverage
tox -e coverage

# Run linting and formatting
tox -e lint
```
