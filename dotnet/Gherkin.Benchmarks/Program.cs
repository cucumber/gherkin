using BenchmarkDotNet.Configs;
using BenchmarkDotNet.Diagnosers;
using BenchmarkDotNet.Environments;
using BenchmarkDotNet.Jobs;
using BenchmarkDotNet.Running;

namespace Gherkin.Benchmarks;

internal class Program
{
    static void Main(string[] args)
    {
#if DEBUG
        var config = new DebugInProcessConfig()
#else
        var config = DefaultConfig.Instance
            .AddJob(Job.Default.WithRuntime(CoreRuntime.Core80))
            .AddJob(Job.Default.WithRuntime(ClrRuntime.Net481))
#endif
            .AddDiagnoser(MemoryDiagnoser.Default)
            ;
        _ = BenchmarkRunner.Run<GherkingParser>(config);
    }
}
