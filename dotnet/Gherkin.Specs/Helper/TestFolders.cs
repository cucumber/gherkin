namespace Gherkin.Specs.Helper;

internal static class TestFolders
{
    public static string InputFolder
    {
        get
        {
            var inputFolder = Environment.CurrentDirectory;

            inputFolder = Path.Combine(inputFolder, "..");

            return inputFolder;
        }
    }
}
