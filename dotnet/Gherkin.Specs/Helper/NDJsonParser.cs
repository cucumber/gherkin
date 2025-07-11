using Io.Cucumber.Messages.Types;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace Gherkin.Specs.Helper;

public class NDJsonParser
{
    static JsonSerializerOptions s_SerializerOptions() 
    {
            var options = new JsonSerializerOptions();
            options.PropertyNamingPolicy = JsonNamingPolicy.CamelCase;
            options.Converters.Add(new CucumberMessageEnumConverter<AttachmentContentEncoding>());
            options.Converters.Add(new CucumberMessageEnumConverter<HookType>());
            options.Converters.Add(new CucumberMessageEnumConverter<PickleStepType>());
            options.Converters.Add(new CucumberMessageEnumConverter<SourceMediaType>());
            options.Converters.Add(new CucumberMessageEnumConverter<StepDefinitionPatternType>());
            options.Converters.Add(new CucumberMessageEnumConverter<Io.Cucumber.Messages.Types.StepKeywordType>());
            options.Converters.Add(new CucumberMessageEnumConverter<TestStepResultStatus>());
            options.DefaultIgnoreCondition = System.Text.Json.Serialization.JsonIgnoreCondition.WhenWritingNull;
            options.Encoder = System.Text.Encodings.Web.JavaScriptEncoder.UnsafeRelaxedJsonEscaping;

            return options;    
    }

    public static async Task<List<T>> DeserializeAsync<T>(string expectedFile)
    {
        var result = new List<T>();
        using var contentStream = File.OpenRead(expectedFile);

        await foreach (var deserializedObject in JsonSerializer.DeserializeAsyncEnumerable<T>(contentStream, true, s_SerializerOptions()))
        {
            result.Add(deserializedObject);
        }

        return result;
    }
}