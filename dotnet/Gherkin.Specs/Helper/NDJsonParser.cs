using MessageTypes = Io.Cucumber.Messages.Types;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace Gherkin.Specs.Helper;

public class NDJsonParser
{
    static JsonSerializerOptions s_SerializerOptions() 
    {
            var options = new JsonSerializerOptions();
            options.PropertyNamingPolicy = JsonNamingPolicy.CamelCase;
            options.Converters.Add(new CucumberMessageEnumConverter<MessageTypes.AttachmentContentEncoding>());
            options.Converters.Add(new CucumberMessageEnumConverter<MessageTypes.HookType>());
            options.Converters.Add(new CucumberMessageEnumConverter<MessageTypes.PickleStepType>());
            options.Converters.Add(new CucumberMessageEnumConverter<MessageTypes.SourceMediaType>());
            options.Converters.Add(new CucumberMessageEnumConverter<MessageTypes.StepDefinitionPatternType>());
            options.Converters.Add(new CucumberMessageEnumConverter<MessageTypes.StepKeywordType>());
            options.Converters.Add(new CucumberMessageEnumConverter<MessageTypes.TestStepResultStatus>());
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