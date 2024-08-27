using Gherkin.CucumberMessages;
using Gherkin.CucumberMessages.Pickles;
using Gherkin.CucumberMessages.Types;

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
                events.Add(new Envelope
                {
                    Source = source
                });
            }
            if (printAst)
            {
                events.Add(new Envelope
                {
                    GherkinDocument =
                        _astMessagesConverter.ConvertGherkinDocumentToEventArgs(gherkinDocument, source.Uri)
                });
            }
            if (printPickles)
            {
                var pickles = _pickleCompiler.Compile(_astMessagesConverter.ConvertGherkinDocumentToEventArgs(gherkinDocument, source.Uri));
                foreach (Pickle pickle in pickles)
                {
                    events.Add(new Envelope
                    {
                        Pickle = pickle
                    });
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
        events.Add(new Envelope
        {
            ParseError = new ParseError()
            {
                Message = e.Message,
                Source = new SourceReference()
                {
                    Location = new Location(e.Location.Column, e.Location.Line),
                    Uri = uri
                }
            }
        });
    }
}
