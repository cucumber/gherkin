namespace Gherkin.Ast;

public class Examples(Tag[] tags, Location location, string keyword, string name, string description, TableRow header, TableRow[] body)
    : IHasLocation, IHasDescription, IHasRows, IHasTags
{
    public IEnumerable<Tag> Tags { get; } = tags;
    public Location Location { get; } = location;
    public string Keyword { get; } = keyword;
    public string Name { get; } = name;
    public string Description { get; } = description;
    public TableRow TableHeader { get; } = header;
    public IEnumerable<TableRow> TableBody { get; } = body;

    IEnumerable<TableRow> IHasRows.Rows
    {
        get { return new TableRow[] { TableHeader }.Concat(TableBody); }
    }
}