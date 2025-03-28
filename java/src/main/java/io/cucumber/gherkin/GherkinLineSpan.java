package io.cucumber.gherkin;

class GherkinLineSpan implements Indentable {
    // One-based line position
    public int column;

    // text part of the line
    public String text;

    public GherkinLineSpan(int column, String text) {
        this.column = column;
        this.text = text;
    }

    public GherkinLineSpan(int column) {
        this.column = column;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        GherkinLineSpan that = (GherkinLineSpan) o;
        return column == that.column && text.equals(that.text);
    }

    @Override
    public int hashCode() {
        int result = column;
        result = 31 * result + text.hashCode();
        return result;
    }

    @Override
    public void indent(int indent, String trimmedText) {
        this.column += indent;
        this.text = trimmedText;
    }

}
