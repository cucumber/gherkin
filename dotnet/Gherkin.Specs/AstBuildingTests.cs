using FluentAssertions;
using Io.Cucumber.Messages.Types;
using Gherkin.Specs.Helper;
using Xunit;

namespace Gherkin.Specs;

public class AstBuildingTests : EventTestBase
{
    [Theory, MemberData(nameof(TestFileProvider.GetValidTestFiles), MemberType = typeof(TestFileProvider))]
    public async Task TestSuccessfulAstBuilding(string testFeatureFile)
    {
        var testFile = GetFullPathToTestFeatureFile(testFeatureFile, "good", ".ast.ndjson");

        var expectedGherkinDocumentEvent = await NDJsonParser.DeserializeAsync<Envelope>(testFile.ExpectedFileFullPath);

        var raisedEvents = ProcessGherkinEvents(testFile.FullPath, false, true, false);

        raisedEvents.Should().Match(list => list.All(e => e.GherkinDocument != null));
        AssertEvents(testFeatureFile, raisedEvents, expectedGherkinDocumentEvent, testFile);
    }

    [Theory, MemberData(nameof(TestFileProvider.GetInvalidTestFiles), MemberType = typeof(TestFileProvider))]
    public async Task TestFailedAstBuilding(string testFeatureFile)
    {
        var testFile = GetFullPathToTestFeatureFile(testFeatureFile, "bad", ".errors.ndjson");

        var expectedGherkinDocumentEvent = await NDJsonParser.DeserializeAsync<Envelope>(testFile.ExpectedFileFullPath);

        var raisedEvents = ProcessGherkinEvents(testFile.FullPath, false, true, false);

        raisedEvents.Should().Match(list => list.All(e => e.ParseError != null));
        AssertEvents(testFeatureFile, raisedEvents, expectedGherkinDocumentEvent, testFile);
    }
}
