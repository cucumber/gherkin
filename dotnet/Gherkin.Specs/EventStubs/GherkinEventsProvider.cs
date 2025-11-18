using Gherkin.CucumberMessages;
using Gherkin.CucumberMessages.Pickles;
using Io.Cucumber.Messages.Types;

namespace Gherkin.Specs.EventStubs;

public class GherkinEventsProvider(bool printSource, bool printAst, bool printPickles, IIdGenerator idGenerator)
{
    private readonly Parser _parser = new Parser();
    private readonly PickleCompiler _pickleCompiler = new PickleCompiler(idGenerator);
    private readonly AstMessagesConverter _astMessagesConverter = new AstMessagesConverter(idGenerator);

    public IEnumerable<Envelope> GetEvents(Source source)
    {
        var events = new List<Envelope>();

        try
        {
            var gherkinDocument = _parser.Parse(new StringReader(source.Data));

            if (printSource)
            {
                events.Add(Envelope.Create(source));
            }
            if (printAst)
            {
                events.Add(Envelope.Create(_astMessagesConverter.ConvertGherkinDocumentToEventArgs(gherkinDocument, source.Uri)));
            }
            if (printPickles)
            {
                var pickles = _pickleCompiler.Compile(_astMessagesConverter.ConvertGherkinDocumentToEventArgs(gherkinDocument, source.Uri));
                foreach (Pickle pickle in pickles)
                {
                    events.Add(Envelope.Create(pickle));
                }
            }
        }
        catch (CompositeParserException e)
        {
            foreach (ParserException error in e.Errors)
            {
                AddParseError(events, error, source.Uri);
            }
        }
        catch (ParserException e)
        {
            AddParseError(events, e, source.Uri);
        }
        return events;
    }


    private void AddParseError(List<Envelope> events, ParserException e, String uri)
    {
        // This forces the suppression of the Column value in the Location when the Location is zero (the default)
        long? col = null;
        if (e.Location.HasValue && e.Location.Value.Column != 0)
            col = e.Location.Value.Column;

        events.Add(Envelope.Create(
                new ParseError(
                    new SourceReference(
                        uri, // Add the missing 'uri' parameter here
                        null, // Assuming JavaMethod is not needed
                        null, // Assuming JavaStackTraceElement is not needed
                        e.Location.HasValue ? new Location(e.Location.GetValueOrDefault().Line, col) : null
                    ),
                    e.Message
            )
        ));
    }
}
