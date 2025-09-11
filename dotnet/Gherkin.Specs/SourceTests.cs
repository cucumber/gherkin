using FluentAssertions;
using Io.Cucumber.Messages.Types;
using Gherkin.Specs.Helper;
using Xunit;

namespace Gherkin.Specs;

public class SourceTests : EventTestBase
{
    [Theory, MemberData(nameof(TestFileProvider.GetValidTestFiles), MemberType = typeof(TestFileProvider))]
    public async Task TestSourceMessage(string testFeatureFile)
    {
        var testFile = GetFullPathToTestFeatureFile(testFeatureFile, "good", ".source.ndjson");

        var expectedGherkinDocumentEvent = await NDJsonParser.DeserializeAsync<Envelope>(testFile.ExpectedFileFullPath);

        var raisedEvents = ProcessGherkinEvents(testFile.FullPath, true, false, false);

        raisedEvents.Should().Match(list => list.All(e => e.Source != null));
        AssertEvents(testFeatureFile, raisedEvents, expectedGherkinDocumentEvent, testFile);
    }
}
