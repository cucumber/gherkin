using Io.Cucumber.Messages.Types;   

namespace Gherkin.Specs.EventStubs;

public class SourceProvider
{
    public IEnumerable<Source> GetSources(IEnumerable<string> paths)
    {
        foreach (var path in paths)
        {
            string data = File.ReadAllText(path);
            yield return new Source(path, data, SourceMediaType.TEXT_X_CUCUMBER_GHERKIN_PLAIN);
        }
    }
}
