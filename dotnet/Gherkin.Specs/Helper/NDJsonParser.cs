using MessageTypes = Io.Cucumber.Messages.Types;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace Gherkin.Specs.Helper;

public class NDJsonParser
{
    private static readonly Lazy<JsonSerializerOptions> _serializerOptions = new(() =>
    {
        var options = new JsonSerializerOptions();
        options.PropertyNamingPolicy = JsonNamingPolicy.CamelCase;
        options.Converters.Add(new CucumberMessagesEnumConverterFactory());
        options.DefaultIgnoreCondition = System.Text.Json.Serialization.JsonIgnoreCondition.WhenWritingNull;
        options.Encoder = System.Text.Encodings.Web.JavaScriptEncoder.UnsafeRelaxedJsonEscaping;
        return options;
    });

    public static JsonSerializerOptions SerializerOptions => _serializerOptions.Value;

    public static async Task<List<T>> DeserializeAsync<T>(string expectedFile)
    {
        var result = new List<T>();
        using var contentStream = File.OpenRead(expectedFile);

        await foreach (var deserializedObject in JsonSerializer.DeserializeAsyncEnumerable<T>(contentStream, true, SerializerOptions))
        {
            result.Add(deserializedObject);
        }

        return result;
    }
}