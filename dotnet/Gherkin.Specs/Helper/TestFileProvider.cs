namespace Gherkin.Specs.Helper;

public class TestFileProvider
{
    public static IEnumerable<object[]> GetValidTestFiles()
    {
        return GetTestFiles("good");
    }

    public static IEnumerable<object[]> GetInvalidTestFiles()
    {
        return GetTestFiles("bad");
    }

    private static IEnumerable<object[]> GetTestFiles(string category)
    {
        string testFileFolder = GetTestFileFolder(category);

        return Directory.GetFiles(testFileFolder, "*.feature")
                        .Where(f => Path.GetFileName(f) != "escaped_pipes.feature")
                        .Select(f => new object[] { Path.GetFileName(f) });
    }

    public static string GetTestFileFolder(string category)
    {
        return Path.GetFullPath(Path.Combine(TestFolders.InputFolder, "..", "..", "..", "..", @"testdata", category));
    }
}
