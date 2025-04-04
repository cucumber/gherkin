package io.cucumber.gherkin;

import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;

class Stdio {
    /**
     * UTF-8 STDOUT
     */
    public static final PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out, StandardCharsets.UTF_8), true);

}
