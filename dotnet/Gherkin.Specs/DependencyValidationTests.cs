#if NETFRAMEWORK
using System.Reflection;
using System.Text.Json;
using Xunit;

namespace Gherkin.Specs;

public sealed class DependencyValidationTests
{
    [Fact]
    public void SystemTextJsonUpgradeBlocker()
    {
        // this test was made intentionally to block upgrade for system.text.json nuget package for .NET standard version of library
        // discussion: https://github.com/cucumber/messages/pull/237#issuecomment-2225649432

        var version = typeof(JsonSerializer).Assembly.GetCustomAttribute<AssemblyFileVersionAttribute>().Version;

        Assert.Equal("6.0.21.52210", version); // System.Text.Json Version 6.0.0
    }
}
#endif