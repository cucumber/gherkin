using FluentAssertions;
using Io.Cucumber.Messages.Types;
using Gherkin.Specs.Helper;
using Xunit;

namespace Gherkin.Specs;

public class PicklesTests : EventTestBase
{
    [Theory, MemberData(nameof(TestFileProvider.GetValidTestFiles), MemberType = typeof(TestFileProvider))]
    public async Task TestPickleCompilation(string testFeatureFile)
    {
        var testFile = GetFullPathToTestFeatureFile(testFeatureFile, "good", ".pickles.ndjson");

        var expectedEvents = await NDJsonParser.DeserializeAsync<Envelope>(testFile.ExpectedFileFullPath);

        var raisedEvents = ProcessGherkinEvents(testFile.FullPath, false, false, true);

        raisedEvents.Should().Match(list => list.All(e => e.Pickle != null));
        AssertEvents(testFeatureFile, raisedEvents, expectedEvents, testFile);
    }
}
