using BenchmarkDotNet.Attributes;
using Gherkin.Ast;
using System.Text;

namespace Gherkin.Benchmarks;

public class GherkingParser
{
    [Params("very_long.feature", "tags.feature")]
    public string? FeatureFile { get; set; }

    readonly MemoryStream _TestData = new();
    readonly Parser _ParserReused = new();
    readonly TokenMatcher _TokenMatcher = new();
    StreamReader? _Reader;

    [GlobalSetup]
    public void GlobalSetup()
    {
        var fullPathToTestFeatureFile = Path.Combine(TestFileProvider.GetTestFileFolder("good"), FeatureFile!);

        using var fileStream = new FileStream(fullPathToTestFeatureFile, FileMode.Open, FileAccess.Read);

        fileStream.CopyTo(_TestData);

        _Reader = new StreamReader(_TestData, Encoding.UTF8, false, 4096, true);
    }

    [Benchmark]
    public GherkinDocument Parser()
    {
        _TestData.Seek(0, SeekOrigin.Begin);
        var parser = new Parser();
        return parser.Parse(new TokenScanner(_Reader));
    }

    [Benchmark]
    public GherkinDocument ParserReuse()
    {
        _TestData.Seek(0, SeekOrigin.Begin);
        return _ParserReused.Parse(new TokenScanner(_Reader), _TokenMatcher);
    }
}
