# Gherkin for C++

Gherkin parser/compiler for C++. Please see [Gherkin](https://github.com/cucumber/gherkin) for details.

## Regex backend

The parser uses RE2 when it is available, otherwise it falls back to `std::regex`.
RE2 offers predictable, linear-time matching for a fixed pattern without
backtracking, and can reduce the cost of regex operations compared with
`std::regex`. Overall parsing performance depends on the input and platform;
use the benchmarks below to compare both backends.

RE2 must be installed as a system dependency; the build does not download it.
CMake first looks for the `re2::re2` package target, then the `re2` pkg-config
module. No additional Gherkin option is needed to enable it.

Both backends support the parser's patterns. Custom regex patterns must be
compatible with the selected backend: RE2 does not support backreferences or
lookaround. Replacement strings retain the standard `$1`, `$&`, and `$$` syntax
with either backend.
Use `$&` to refer to the entire match; `$0` is not portable across standard
library implementations. The std backend retains its native `std::regex_replace`
behavior, including platform differences in replacement around empty matches.

RE2 has a rough improvement of 10% on Linux, 15% on Windows and 160% on Macos.

## Tests and benchmarks

Enable `CUCUMBER_GHERKIN_BUILD_TESTS` to build regression tests (requires system
GoogleTest and GoogleMock), then run `ctest --test-dir <build-directory> --output-on-failure`.
Enable `CUCUMBER_GHERKIN_BUILD_BENCHMARKS` to build
`cucumber_gherkin_benchmark`; no benchmark framework is required.

For example, from this C++ project directory, with the regular Cucumber Messages
and nlohmann-json dependencies installed, and system RE2 available for the RE2
build. To benchmark the fallback on the same machine, disable both discovery
paths using CMake's standard package controls:

~~~bash
cmake -S . -B build/std -DCMAKE_BUILD_TYPE=Release \
  -DCUCUMBER_GHERKIN_BUILD_BENCHMARKS=ON -DCUCUMBER_GHERKIN_BUILD_TESTS=ON \
  -DCMAKE_DISABLE_FIND_PACKAGE_re2=TRUE -DCMAKE_DISABLE_FIND_PACKAGE_PkgConfig=TRUE
cmake -S . -B build/re2 -DCMAKE_BUILD_TYPE=Release \
  -DCUCUMBER_GHERKIN_BUILD_BENCHMARKS=ON -DCUCUMBER_GHERKIN_BUILD_TESTS=ON
cmake --build build/std --target cucumber_gherkin_benchmark cucumber_gherkin.test
cmake --build build/re2 --target cucumber_gherkin_benchmark cucumber_gherkin.test
ctest --test-dir build/std --output-on-failure
ctest --test-dir build/re2 --output-on-failure
build/std/benchmark/cucumber_gherkin_benchmark 100
build/re2/benchmark/cucumber_gherkin_benchmark 100
~~~

## Developers

Some files are generated from the `gherkin-*.razor` file. Please run the
following command to generate the C++ files.

~~~bash
cd <project_root>/cpp
make generate-all
~~~
