using Xunit;

namespace Gherkin.Specs;

public class GherkinLineTests
{
    [Fact]
    public void DefaultValueDontThrow()
    {
        var line = default(GherkinLine);
        Assert.Empty(line.GetLineText(0));
        Assert.Empty(line.GetRestTrimmed(0));
        Assert.False(line.StartsWith("test"));
        Assert.False(line.StartsWithTitleKeyword("test"));
        Assert.Empty(line.GetTableCells());
        Assert.Empty(line.GetTags());
        Assert.Equal(0, line.Indent);
        Assert.Equal(0, line.LineNumber);
    }
}
