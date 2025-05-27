package io.cucumber.gherkin;

import java.util.LinkedHashMap;
import java.util.Map;

import static java.util.Arrays.asList;
import static java.util.Collections.unmodifiableList;
import static java.util.Collections.unmodifiableMap;

final class GherkinDialects {
    static final Map<String, GherkinDialect> DIALECTS;

    static {
        Map<String, GherkinDialect> dialects  = new LinkedHashMap<>();
<#list dialects as name, dialect>

        dialects.put("${name}", new GherkinDialect(
            "${name}",
            "${dialect.name}",
            "${dialect.native}",
            unmodifiableList(asList("${dialect.feature?join("\", \"")}")),
            unmodifiableList(asList("${dialect.rule?join("\", \"")}")),
            unmodifiableList(asList("${dialect.scenario?join("\", \"")}")),
            unmodifiableList(asList("${dialect.scenarioOutline?join("\", \"")}")),
            unmodifiableList(asList("${dialect.background?join("\", \"")}")),
            unmodifiableList(asList("${dialect.examples?join("\", \"")}")),
            unmodifiableList(asList("${dialect.given?join("\", \"")}")),
            unmodifiableList(asList("${dialect.when?join("\", \"")}")),
            unmodifiableList(asList("${dialect.then?join("\", \"")}")),
            unmodifiableList(asList("${dialect.and?join("\", \"")}")),
            unmodifiableList(asList("${dialect.but?join("\", \"")}"))
        ));
</#list> 

        DIALECTS = unmodifiableMap(dialects);
    }
}
