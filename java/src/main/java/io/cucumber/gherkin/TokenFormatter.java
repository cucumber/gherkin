package io.cucumber.gherkin;

import static java.util.stream.Collectors.joining;

class TokenFormatter {

    String formatToken(Token token) {
        if (token.isEOF())
            return "EOF";

        return String.format("(%s:%s)%s:%s/%s/%s",
                toString(token.location.getLine()),
                toString(token.location.getColumn().orElse(0L)),
                toString(token.matchedType),
                token.matchedKeyword == null ? "" : String.format("(%s)%s",
                                                                  toString(token.keywordType),
                                                                  toString(token.matchedKeyword)),
                toString(token.matchedText),
                toString(token.matchedItems == null ? "" : token.matchedItems.stream()
                        .map(o ->  o.column + ":" + o.text)
                        .collect(joining(",")))
        );
    }

    private String toString(Object o) {
        return o == null ? "" : o.toString();
    }
}
