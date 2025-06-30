namespace Gherkin.Benchmarks;

public class TestFileProvider
{
    public static string GetTestFileFolder(string category)
    {
        var inputFolder = Environment.CurrentDirectory;
#if DEBUG
        // Artefacts are not created in subdirectories, so we don't need to go any higher.
#elif NET6_0_OR_GREATER
        inputFolder = Path.Combine(inputFolder, "..", "..", "..", "..");
#endif
        return Path.GetFullPath(Path.Combine(inputFolder, "..", "..", "..", "..", "..", "testdata", category));
    }
}
