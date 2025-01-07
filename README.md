<h1 align="center">
  <img src="https://raw.githubusercontent.com/cucumber/cucumber-js/46a5a78107be27e99c6e044c69b6e8f885ce456c/docs/images/logo.svg" alt="Cucumber logo" width="75">
  <br>
  Gherkin
</h1>
<p align="center">
  <b>Parser and compiler for the Gherkin language</b>
</p>
<div align="center">
  <span><b><a href="https://cucumber.io/docs/gherkin/reference/">Syntax</a></b></span>
  <span><b>·</b></span>
  <span><b><a href="https://cucumber.io/docs/gherkin/languages">Localisation</a></b></span>
  <span><b>·</b></span>
  <span><b><a href="https://github.com/cucumber/gherkin/issues">Issues</a></b></span>
  <span><b>·</b></span>
  <span><b><a href="./CONTRIBUTING.md">Contributing</a></b></span>
</div>
<br>

Gherkin is a language for writing behavioural specifications through your spoken language. As they are written in plain language, they can be easily understood. These specifications can be executed as automated tests using tools such as [Cucumber](https://cucumber.io/).

Gherkin has been translated to over [70 spoken languages](https://cucumber.io/docs/gherkin/languages) and has parser implementations available for common programming languages.

<div align="center">

| Language | Workflow | Release |
|----------|----------|---------|
| 🥅 [.NET](./dotnet) | [![test dotnet workflow](https://github.com/cucumber/gherkin/actions/workflows/test-dotnet.yml/badge.svg)](./.github/workflows/test-dotnet.yml) | [![NuGet](https://img.shields.io/nuget/v/gherkin.svg?label=Nuget&color=dark-green)](https://www.nuget.org/packages/gherkin/) |
| ©️ [C](./c) | [![test c workflow](https://github.com/cucumber/gherkin/actions/workflows/test-c.yml/badge.svg)](./.github/workflows/test-c.yml) | [![GitHub release](https://img.shields.io/github/v/release/cucumber/gherkin?label=GitHub&color=dark-green)](https://github.com/cucumber/gherkin/releases) |
| ➕ [C++](./cpp) | [![test cpp workflow](https://github.com/cucumber/gherkin/actions/workflows/test-cpp.yml/badge.svg)](./.github/workflows/test-cpp.yml) | [![GitHub release](https://img.shields.io/github/v/release/cucumber/gherkin?label=GitHub&color=dark-green)](https://github.com/cucumber/gherkin/releases) |
| 🎯 [Dart](./dart) | [![test dart workflow](https://github.com/cucumber/gherkin/actions/workflows/test-dart.yml/badge.svg)](./.github/workflows/test-dart.yml) | [![GitHub release](https://img.shields.io/github/v/release/cucumber/gherkin?label=GitHub&color=dark-green)](https://github.com/cucumber/gherkin/releases) |
| 🐹 [Go](./go) | [![test go workflow](https://github.com/cucumber/gherkin/actions/workflows/test-go.yml/badge.svg)](./.github/workflows/test-go.yml) | [![GitHub release](https://img.shields.io/github/v/release/cucumber/gherkin?label=GitHub&color=dark-green)](https://github.com/cucumber/gherkin/releases) |
| ☕ [Java](./java) | [![test java workflow](https://github.com/cucumber/gherkin/actions/workflows/test-java.yml/badge.svg)](./.github/workflows/test-java.yml) | [![Maven Version](https://img.shields.io/maven-central/v/io.cucumber/gherkin.svg?label=Maven%20Central&color=dark-green)](https://central.sonatype.com/artifact/io.cucumber/gherkin) |
| 📃 [JavaScript](./javascript) | [![test javascript workflow](https://github.com/cucumber/gherkin/actions/workflows/test-javascript.yml/badge.svg)](./.github/workflows/test-javascript.yml) | [![npm version](https://img.shields.io/npm/v/@cucumber/gherkin.svg?label=Npm&color=dark-green)](https://www.npmjs.com/package/@cucumber/gherkin) |
| 🍏 [Objective-C](./objective-c) | _Without active testing_ | [![GitHub release](https://img.shields.io/github/v/release/cucumber/gherkin?label=GitHub&color=dark-green)](https://github.com/cucumber/gherkin/releases) |
| 🦪 [Perl](./perl) | [![test perl workflow](https://github.com/cucumber/gherkin/actions/workflows/test-perl.yml/badge.svg)](./.github/workflows/test-perl.yml) | [![CPAN version](https://img.shields.io/cpan/v/Gherkin?label=Cpan&color=dark-green)](https://metacpan.org/release/Gherkin) |
| 🐘 [PHP](./php) | [![test php workflow](https://github.com/cucumber/gherkin/actions/workflows/test-php.yml/badge.svg)](./.github/workflows/test-php.yml) | [![Packagist Version](https://img.shields.io/packagist/v/cucumber/gherkin.svg?label=Packagist&color=dark-green)](https://packagist.org/packages/cucumber/gherkin) |
| 🐍 [Python](./python) | [![test python workflow](https://github.com/cucumber/gherkin/actions/workflows/test-python.yml/badge.svg)](./.github/workflows/test-python.yml) | [![PyPI](https://img.shields.io/pypi/v/gherkin-official?label=PyPI&color=dark-green)](https://pypi.org/project/gherkin-official/) |
| ♦️ [Ruby](./ruby) | [![test ruby workflow](https://github.com/cucumber/gherkin/actions/workflows/test-ruby.yml/badge.svg)](./.github/workflows/test-ruby.yml) | [![Gem Version](https://img.shields.io/gem/v/cucumber-gherkin?label=Gem&color=dark-green)](https://rubygems.org/gems/cucumber-gherkin) |

</div>

Contributions are welcome, whether you would like to contribute [translations](./CONTRIBUTING.md#contributing-translations-i18n) or [parser implementations](./CONTRIBUTING.md#contributing-a-parser-implementation) - either by raising [issues](https://github.com/cucumber/gherkin/issues) or [pull requests](https://github.com/cucumber/gherkin/pulls). See our [contributing guidelines](./CONTRIBUTING.md) or use our [discussion board](https://github.com/orgs/cucumber/discussions) for questions and guidance.

## Usage

Gherkin can be used either through its command line interface (CLI) or as a
library.

It is designed to be used in conjunction with other tools such as Cucumber
which consumes the output from the CLI or library as [Cucumber Messages](https://github.com/cucumber/messages).

### Library

Using the library is the preferred way to use Gherkin since it produces easily
consumable AST and Pickle objects in-process without having to fork a CLI process
or parse JSON.

The library itself provides a _stream_ API, which is what the CLI is based on.
This is the recommended way to use the library as it provides a high level API
that is easy to use. See the CLI implementations to get an idea of how to use it.

Alternatively, you can use the lower level parser and compiler. Some usage examples are below:

#### Java

```java
Path path = Paths.get("../testdata/good/minimal.feature");
GherkinParser parser = GherkinParser.builder().build();
Stream<Envelope> pickles = parser.parse(envelope).filter(envelope -> envelope.getPickle().isPresent());
```

#### C#

```csharp
var parser = new Parser();
var gherkinDocument = parser.Parse(@"Drive:\PathToGherkinDocument\document.feature");
```

#### Ruby

```ruby
require 'gherkin/parser'
require 'gherkin/pickles/compiler'

source = {
  uri: 'uri_of_the_feature.feature',
  data: 'Feature: ...',
  mediaType: 'text/x.cucumber.gherkin+plain'
}

gherkin_document = Gherkin::Parser.new.parse(source[:data])
id_generator = Cucumber::Messages::IdGenerator::UUID.new

pickles = Gherkin::Pickles::Compiler.new(id_generator).compile(gherkin_document, source)
```

#### JavaScript

```javascript
var Gherkin = require("@cucumber/gherkin");
var Messages = require("@cucumber/messages");

var uuidFn = Messages.IdGenerator.uuid();
var builder = new Gherkin.AstBuilder(uuidFn);
var matcher = new Gherkin.GherkinClassicTokenMatcher(); // or Gherkin.GherkinInMarkdownTokenMatcher()

var parser = new Gherkin.Parser(builder, matcher);
var gherkinDocument = parser.parse("Feature: ...");
var pickles = Gherkin.compile(
  gherkinDocument,
  "uri_of_the_feature.feature",
  uuidFn
);
```

#### Go

```go
// Download the package via: `go get github.com/cucumber/gherkin/go/v27`
//   && go get "github.com/cucumber/messages/go/v22"
import (
  "strings"

  gherkin "github.com/cucumber/gherkin/go/v27"
  messages "github.com/cucumber/messages/go/v22"
)

func main() {
  uuid := &message.UUID{} // or &message.Incrementing{}
  reader := strings.NewReader(`Feature: ...`)
  gherkinDocument, err := gherkin.ParseGherkinDocument(reader, uuid.NewId)
  pickles := gherkin.Pickles(*gherkinDocument, "minimal.feature", uuid.NewId)
}
```

#### Python

```python
from gherkin.parser import Parser
from gherkin.pickles.compiler import Compiler

parser = Parser()
gherkin_document = parser.parse("Feature: ...")
gherkin_document["uri"] = "uri_of_the_feature.feature"
pickles = Compiler().compile(gherkin_document)
```

#### Objective-C

```Objective-C
#import "GHParser+Extensions.h"

GHParser * parser = [[GHParser alloc] init];
NSString * featureFilePath; // Should refer to the place where we can get the content of the feature
NSString * content = [NSString stringWithContentsOfURL:featureFilePath encoding:NSUTF8StringEncoding error:nil];
if([content stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]].length == 0){
      // GHParser will throw an error if you passed empty content... handle this issue first.
}
GHGherkinDocument * result = [parser parseContent:content];
```

#### Perl

```perl
use Gherkin::Parser;
use Gherkin::Pickles::Compiler;

my $parser = Gherkin::Parser->new();
my $gherkin_document = $parser->parse("Feature: ...");
my $pickles = Gherkin::Pickles::Compiler->compile($gherkin_document);
```

#### PHP

```php
use Cucumber\Gherkin\GherkinParser;

$path = '/path/to/my.feature';

$parser = new GherkinParser();
$pickles = $parser->parseString(uri: $path, data: file_get_contents($path));
```

### Command Line

The Gherkin CLI `gherkin` reads Gherkin source files (`.feature` files) and outputs
[ASTs](#abstract-syntax-tree-ast) and [Pickles](#pickles).

The `gherkin` program takes any number of files as arguments and prints the results
to `STDOUT` as [Newline Delimited JSON](https://jsonlines.org).

Each line is a JSON document that conforms to the [Cucumber Event Protocol](https://github.com/cucumber/messages).

To try it out, just install Gherkin for your favourite language, and run it over the
files in this repository:

```console
gherkin testdata/**/*.feature
```

Ndjson is easy to read for programs, but hard for people. To pretty print each JSON
document you can pipe it to the [jq](https://stedolan.github.io/jq/) program:

```console
gherkin testdata/**/*.feature | jq
```

## Table cell escaping

If you want to use a newline character in a table cell, you can write this
as `\n`. If you need a `|` as part of the cell, you can escape it as `\|`. And
finally, if you need a `\`, you can escape that with `\\`.

## Architecture

The following diagram outlines the architecture:

```mermaid
graph LR
    A[Feature file] -->|Scanner| B[Tokens]
    B -->|Parser| D[AST]
```

The _scanner_ reads a gherkin doc (typically read from a `.feature` file) and creates
a _token_ for each line. The tokens are passed to the _parser_, which outputs an _AST_
(Abstract Syntax Tree).

If the scanner sees a `#language` header, it will reconfigure itself dynamically
to look for Gherkin keywords for the associated language. The keywords are defined in
`gherkin-languages.json`.

The scanner is hand-written, but the parser is generated by the [Berp](https://github.com/gasparnagy/berp)
parser generator as part of the build process.

Berp takes a grammar file (`gherkin.berp`) and a template file (`gherkin-X.razor`) as input
and outputs a parser in language _X_:

```mermaid
graph TD
    A[gherkin.berp] --> B[berp.exe]
    C[gherkin-X.razor] --> B
    B --> D[Parser.x]
```

### Abstract Syntax Tree (AST)

The AST produced by the parser can be described with the following class diagram:

```mermaid
classDiagram
    ScenarioOutline --|> ScenarioDefinition
    GherkinDocument "1" *-- "0..1" Comment: comment
    GherkinDocument "1" *-- "0..1" Feature: feature
    Feature "1" *-- "0..*" ScenarioDefinition: scenarioDefinitions
    Feature "1" *-- "0..*" Rule: rules
    Rule "1" *-- "0..*" ScenarioDefinition: scenarioDefinitions
    Background "0..1" --* "1" Rule: background
    Feature "1" *-- "0..1" Background: background
    Scenario --|> ScenarioDefinition
    Tag "0..*" --* "1" Feature: tags
    Tag "0..*" --* "1" Rule: tags
    Tag "0..*" --* "1" Scenario: tags
    Tag "0..*" --* "1" ScenarioOutline: tags
    Tag "0..*" --* "1" Examples: tags
    Examples "0..*" --* "1" ScenarioOutline: examples
    TableRow "1" --* "1" Examples: header
    TableRow "0..*" --* "1" Examples: rows
    Background "1" *-- "0..*" Step: steps
    Step "0..*" --* "1" ScenarioDefinition: steps
    StepArgument "0..1" --* "1" Step: stepArgument
    DataTable --|> StepArgument
    StepArgument <|-- DocString
    TableRow "0..*" --* "1" DataTable: rows
    TableRow "1" *-- "0..*" TableCell: cells
    class ScenarioDefinition {
        keyword
        name
        description
    }
    class Step {
        keyword
        text
    }
    class Examples {
        keyword
        name
        description
    }
    class Feature {
        language
        keyword
        name
        description
    }
    class Background {
        keyword
        name
        description
    }
    class Rule {
        keyword
        name
        description
    }
    class DocString {
        content
        contentType
    }
    class Comment {
        text
    }
    class TableCell {
        value
    }
    class Tag {
        name
    }
    class Location {
        line: int
        column: int
    }
```

Every class represents a node in the AST. Every node has a `Location` that describes
the line number and column number in the input file. These numbers are 1-indexed.

All fields on nodes are strings (except for `Location.line` and `Location.column`).

The implementation is simple objects without behaviour, only data. It's up to
the implementation to decide whether to use classes or just basic collections,
but the AST _must_ have a JSON representation (this is used for testing).

Each node in the JSON representation also has a `type` property with the name
of the node type.

You can see some examples in the
[testdata/good](https://github.com/cucumber/gherkin/tree/main/testdata/good)
directory.

### Pickles

The AST isn't suitable for execution by Cucumber. It needs further processing
into a simpler form called _Pickles_.

The compiler compiles the AST produced by the parser into pickles:

```mermaid
graph LR
    A[AST] -->|Compiler| B[Pickles]
```

The rationale is to decouple Gherkin from Cucumber so that Cucumber is open to
support alternative formats to Gherkin (for example Markdown).

The simpler _Pickles_ data structure also simplifies the internals of Cucumber.
With the compilation logic maintained in the Gherkin library
we can easily use the same test suite for all implementations to verify that
compilation is behaving consistently between implementations.

Each `Scenario` will be compiled into a `Pickle`. A `Pickle` has a list of
`PickleStep`, derived from the steps in a `Scenario`.

Each `Examples` row under `Scenario Outline` will also be compiled into a `Pickle`.

Any `Background` steps will also be compiled into a `Pickle`.

Every tag, like `@a`, will be compiled into a `Pickle` as well (inheriting tags from parent elements
in the Gherkin AST).

Example:

```gherkin
@a
Feature:
  @b @c
  Scenario Outline:
    Given <x>

    Examples:
      | x |
      | y |

  @d @e
  Scenario Outline:
    Given <m>

    @f
    Examples:
      | m |
      | n |
```

Using the [CLI](#cli) we can compile this into several pickle objects:

```console
gherkin testdata/good/readme_example.feature --no-source --no-ast | jq
```

Output:

```json
{
  "type": "pickle",
  "uri": "testdata/good/readme_example.feature",
  "pickle": {
    "name": "",
    "steps": [
      {
        "text": "y",
        "arguments": [],
        "locations": [
          {
            "line": 9,
            "column": 7
          },
          {
            "line": 5,
            "column": 11
          }
        ]
      }
    ],
    "tags": [
      {
        "name": "@a",
        "location": {
          "line": 1,
          "column": 1
        }
      },
      {
        "name": "@b",
        "location": {
          "line": 3,
          "column": 3
        }
      },
      {
        "name": "@c",
        "location": {
          "line": 3,
          "column": 6
        }
      }
    ],
    "locations": [
      {
        "line": 9,
        "column": 7
      },
      {
        "line": 4,
        "column": 3
      }
    ]
  }
}
{
  "type": "pickle",
  "uri": "testdata/good/readme_example.feature",
  "pickle": {
    "name": "",
    "steps": [
      {
        "text": "n",
        "arguments": [],
        "locations": [
          {
            "line": 18,
            "column": 7
          },
          {
            "line": 13,
            "column": 11
          }
        ]
      }
    ],
    "tags": [
      {
        "name": "@a",
        "location": {
          "line": 1,
          "column": 1
        }
      },
      {
        "name": "@d",
        "location": {
          "line": 11,
          "column": 3
        }
      },
      {
        "name": "@e",
        "location": {
          "line": 11,
          "column": 6
        }
      },
      {
        "name": "@f",
        "location": {
          "line": 15,
          "column": 5
        }
      }
    ],
    "locations": [
      {
        "line": 18,
        "column": 7
      },
      {
        "line": 12,
        "column": 3
      }
    ]
  }
}
```

Each `Pickle` event also contains the path to the original source. This is useful for
generating reports and stack traces when a Scenario fails.

Cucumber will further transform this list of `Pickle` objects to a list of `TestCase`
objects. `TestCase` objects link to user code such as Hooks and Step Definitions.

## Building Gherkin

See [`CONTRIBUTING.md`](CONTRIBUTING.md)

## Markdown with Gherkin

See [Markdown with Gherkin](./MARKDOWN_WITH_GHERKIN.md).

## Projects using Gherkin

- [cucumber-jvm](https://github.com/cucumber/cucumber-jvm)
- [cucumber-ruby](https://github.com/cucumber/cucumber-ruby)
- [cucumber-js](https://github.com/cucumber/cucumber-js)
- [godog](https://github.com/cucumber/godog)
- [pytest-bdd](https://github.com/pytest-dev/pytest-bdd)
