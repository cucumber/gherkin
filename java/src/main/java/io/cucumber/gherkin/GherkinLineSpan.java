package io.cucumber.gherkin;

class GherkinLineSpan {
    /**
     * Index-1 based position in codepoints.
      */ 
    final int column;

    /**
     * Text part of the line 
     */
    final String text;

    GherkinLineSpan(int column, String text) {
        this.column = column;
        this.text = text;
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
    public String toString() {
        return "GherkinLineSpan{" +
                "column=" + column +
                ", text='" + text + '\'' +
                '}';
    }
}
