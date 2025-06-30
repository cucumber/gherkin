Please read [CONTRIBUTING](https://github.com/cucumber/gherkin/blob/master/CONTRIBUTING.md) and [RELEASING](https://github.com/cucumber/gherkin/blob/master/RELEASING.md) first.

## Run tests

### MacOS/Linux

Install [.NET 5](https://github.com/dotnet/core/blob/master/release-notes/download-archives/2.0.7-download.md)

Run `make` from this directory.

### Windows

Open `Gherkin.DotNet.sln` from this directory in Visual Studio 2019 and build.

Alternatively, run `dotnet build` and `dotnet test` from this directory.

The `dotnet test` command will run the unit tests and the .NET-transformed acceptance tests. This is good as a first pass check and for debugging.
For a complete verification, run the `make` command as well (or let the PR build run it for you), so that the standard version of the acceptance tests are also executed.
