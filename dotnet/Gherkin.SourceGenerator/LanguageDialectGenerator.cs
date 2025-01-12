using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using Microsoft.CodeAnalysis.Text;
using System.Text;

namespace Gherkin.SourceGenerator;

[Generator]
public class LanguageDialectGenerator : IIncrementalGenerator
{
    const string GeneratorVersion = "1.0.0";
    record ClassToAddLanguageDialects(string? Namespace, string ClassName);

    public void Initialize(IncrementalGeneratorInitializationContext context)
    {
        //System.Diagnostics.Debugger.Launch();

        context.RegisterPostInitializationOutput(context => context.AddSource(
            "LanguageDialectGeneratedAttribute.g.cs",
            SourceText.From("""
                [System.AttributeUsage(System.AttributeTargets.Class)]
                internal sealed class LanguageDialectGeneratedAttribute : Attribute { }
                """, Encoding.UTF8)));

        var pipeline = context.SyntaxProvider.ForAttributeWithMetadataName(
            fullyQualifiedMetadataName: "LanguageDialectGeneratedAttribute",
            predicate: static (syntaxNode, cancelToken) => syntaxNode is ClassDeclarationSyntax,
            transform: static (context, cancelToken) =>
            {
                var targetSymbol = (INamedTypeSymbol)context.TargetSymbol;
                var ns = targetSymbol.ContainingNamespace?.ToDisplayString(SymbolDisplayFormat.FullyQualifiedFormat.WithGlobalNamespaceStyle(SymbolDisplayGlobalNamespaceStyle.Omitted));
                var className = targetSymbol.Name;
                return new ClassToAddLanguageDialects(ns, className);
            });

        context.RegisterSourceOutput(pipeline, static (context, classToAdd) =>
        {
            var allLanguageSettings = LoadLanguageSettings();

            var sb = new StringBuilder();
            if (classToAdd.Namespace is not null)
                sb.AppendLine($"namespace {classToAdd.Namespace};");
            sb.AppendLine($$"""
public partial class {{classToAdd.ClassName}}
{
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Gherkin.SourceGenerator", "{{GeneratorVersion}}")]
    [global::System.Runtime.CompilerServices.MethodImpl(global::System.Runtime.CompilerServices.MethodImplOptions.NoInlining)]
    private static GherkinDialect TryCreateGherkinDialect(string language)
    {
        switch (language)
        {
""");
            foreach (var (language, methodSuffix, _) in allLanguageSettings)
            {
                sb.AppendLine($$"""
            case {{FormatLiteral(language)}}:
                return CreateGherkinDialectFor_{{methodSuffix}}();
""");
            }

            sb.AppendLine($$"""
            default:
                return null;
        }
    }

""");
            foreach (var (language, methodSuffix, languageSettings) in allLanguageSettings)
            {
                sb.AppendLine($$"""

    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Gherkin.SourceGenerator", "{{GeneratorVersion}}")]
    [global::System.Runtime.CompilerServices.MethodImpl(global::System.Runtime.CompilerServices.MethodImplOptions.NoInlining)]
    private static GherkinDialect CreateGherkinDialectFor_{{methodSuffix}}()
    {
        return new GherkinDialect(
            {{FormatLiteral(language)}},
            {{FormatListLiteral(languageSettings.Feature)}},
            {{FormatListLiteral(languageSettings.Rule)}},
            {{FormatListLiteral(languageSettings.Background)}},
            {{FormatListLiteral(languageSettings.Scenario)}},
            {{FormatListLiteral(languageSettings.ScenarioOutline)}},
            {{FormatListLiteral(languageSettings.Examples)}},
            {{FormatListLiteral(languageSettings.Given)}},
            {{FormatListLiteral(languageSettings.When)}},
            {{FormatListLiteral(languageSettings.Then)}},
            {{FormatListLiteral(languageSettings.And)}},
            {{FormatListLiteral(languageSettings.But)}});
    }
""");
            }

            sb.AppendLine(@"
}"
            );

            context.AddSource($"GherkinDialectProvider.LanguageDialect.g.cs", SourceText.From(sb.ToString(), Encoding.UTF8));
        });
    }

    static string FormatListLiteral(IEnumerable<string?>? items)
    {
        if (items is null)
            return "null";
        bool first = true;
        var sb = new StringBuilder();
        sb.Append("[");
        foreach (var item in items)
        {
            if (first)
                first = false;
            else
                sb.Append(", ");
            if (item is null)
                sb.Append("null");
            else
                sb.Append(FormatLiteral(item));
        }
        sb.Append("]");
        return sb.ToString();
    }

    static string FormatLiteral(string value) => Microsoft.CodeAnalysis.CSharp.SymbolDisplay.FormatLiteral(value, true);

    static List<(string Language, string MethodSuffix, GherkinLanguageSetting Settings)> LoadLanguageSettings()
    {
        const string languageFileName = "gherkin-languages.json";

        var assembly = typeof(LanguageDialectGenerator).Assembly;
        var resourceStream = assembly.GetManifestResourceStream("Gherkin.SourceGenerator." + languageFileName);

        if (resourceStream == null)
            throw new InvalidOperationException("Gherkin language resource not found: " + languageFileName);
        var languagesFileContent = new StreamReader(resourceStream).ReadToEnd();

        var result = Newtonsoft.Json.JsonConvert.DeserializeObject<Dictionary<string, GherkinLanguageSetting>>(languagesFileContent);
        if (result is null)
            throw new InvalidOperationException("Gherkin language resource is empty: " + languageFileName);
        return result.OrderBy(x => x.Key).Select(x => (x.Key, x.Key.Replace("-", "_"), x.Value)).ToList();
    }
}
