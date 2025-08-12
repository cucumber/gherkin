package io.cucumber.gherkin;

import java.util.ArrayList;
import java.util.List;
import java.util.PrimitiveIterator;

import static io.cucumber.gherkin.Locations.COLUMN_OFFSET;
import static io.cucumber.gherkin.StringUtils.trimAndIndentKeepNewLines;

final class TableRowLine {

    static List<LineSpan> parse(int indent, String text) {
        List<LineSpan> lineSpans = new ArrayList<>();
        StringBuilder cellBuilder = new StringBuilder();
        boolean beforeFirst = true;
        int col = 0;
        int cellStart = 0;
        boolean escape = false;
        PrimitiveIterator.OfInt iterator = text.codePoints().iterator();
        while (iterator.hasNext()) {
            int c = iterator.next();
            if (escape) {
                switch (c) {
                    case 'n':
                        cellBuilder.append('\n');
                        break;
                    case '\\':
                        cellBuilder.append('\\');
                        break;
                    case '|':
                        cellBuilder.append('|');
                        break;
                    default:
                        // Invalid escape. We'll just ignore it.
                        cellBuilder.append("\\");
                        cellBuilder.appendCodePoint(c);
                        break;
                }
                escape = false;
            } else {
                if (c == '\\') {
                    escape = true;
                } else if (c == '|') {
                    if (beforeFirst) {
                        // Skip the first empty span
                        beforeFirst = false;
                    } else {
                        StringUtils.IndentedText trimmedCellIndent = trimAndIndentKeepNewLines(cellBuilder.toString());
                        int column = indent + cellStart + trimmedCellIndent.getIndent() + COLUMN_OFFSET;
                        lineSpans.add(new LineSpan(column, trimmedCellIndent.getText()));
                    }
                    cellBuilder.setLength(0);// reuse instance rather than creating a new one is faster
                    cellStart = col + 1;
                } else {
                    cellBuilder.appendCodePoint(c);
                }
            }
            col++;
        }
        return lineSpans;
    }

}
