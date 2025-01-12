using System.Globalization;

namespace Gherkin;

public class StringUtils
{
    public static bool StartsWith(string a, string b)
    {
        return a.StartsWith(b, StringComparison.Ordinal);
    }

    private static bool StartsWith(char[] a, char[] b)
    {
        if (a.Length < b.Length)
            return false;
        for (int i = 0; i < b.Length; i++)
        {
            if (a[i] != b[i])
                return false;
        }
        return true;
    }

    public static int CountSymbols(string s)
    {
        return new StringInfo(s).LengthInTextElements;
    }
}

