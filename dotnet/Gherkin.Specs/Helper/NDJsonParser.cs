using Newtonsoft.Json;

namespace Gherkin.Specs.Helper;

public class NDJsonParser
{
    public static List<T> Deserialize<T>(string ndjson)
    {
        var lines = ndjson.Split(new char[] { '\n' }, StringSplitOptions.RemoveEmptyEntries);

        var result = new List<T>();

        foreach (var line in lines)
        {
            var deserializedObject = JsonConvert.DeserializeObject<T>(line);
            result.Add(deserializedObject);
        }

        return result;
    }
}