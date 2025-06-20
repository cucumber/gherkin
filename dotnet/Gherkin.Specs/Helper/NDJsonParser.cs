using System.Text.Json;
using System.Text.Json.Serialization;

namespace Gherkin.Specs.Helper;

public class NDJsonParser
{
    static readonly JsonSerializerOptions s_SerializerOptions = new(JsonSerializerDefaults.Web)
    {
        Converters =
        {
            new JsonStringEnumConverter(JsonNamingPolicy.CamelCase)
        }
    };

    public static async Task<List<T>> DeserializeAsync<T>(string expectedFile)
    {
        var result = new List<T>();
        using var contentStream = File.OpenRead(expectedFile);

        await foreach (var deserializedObject in JsonSerializer.DeserializeAsyncEnumerable<T>(contentStream, true, s_SerializerOptions))
        {
            result.Add(deserializedObject);
        }

        return result;
    }
}