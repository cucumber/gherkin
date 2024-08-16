namespace Gherkin.Ast;

public class Background(Location location, string keyword, string name, string description, Step[] steps)
    : StepsContainer(location, keyword, name, description, steps);