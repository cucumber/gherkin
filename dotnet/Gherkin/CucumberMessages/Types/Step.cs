using System.Runtime.Serialization;

namespace Gherkin.CucumberMessages.Types;

public class Step
{
    [DataMember(Name = "location")]
    public required Location Location { get; set; }

    [DataMember(Name = "keyword")]
    public required string Keyword { get; set; }

    [DataMember(Name = "keywordType")]
    public StepKeywordType? KeywordType { get; set; }

    [DataMember(Name = "text")]
    public required string Text { get; set; }

    [DataMember(Name = "docString")]
    public DocString? DocString { get; set; }

    [DataMember(Name = "dataTable")]
    public DataTable? DataTable { get; set; }

    [DataMember(Name = "id")]
    public required string Id { get; set; }
}