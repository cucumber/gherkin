using System.Text.Json;
using System.Text.Json.Serialization;


namespace Gherkin.Specs.Helper;

public class NDJsonParser
{
    public static List<T> Deserialize<T>(string ndjson)
    {
        var lines = ndjson.Split(new char[] { '\n' }, StringSplitOptions.RemoveEmptyEntries);

        var result = new List<T>();

        foreach (var line in lines)
        {
            var deserializedObject = JsonSerializer.Deserialize<T>(line, new JsonSerializerOptions(JsonSerializerDefaults.Web)
            {
                Converters =
                {
                    new JsonStringEnumConverter(JsonNamingPolicy.CamelCase)
                }
            });
            result.Add(deserializedObject);
        }

        return result;
    }
}