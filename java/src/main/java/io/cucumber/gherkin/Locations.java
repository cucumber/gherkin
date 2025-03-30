package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;

import static java.util.Objects.requireNonNull;

class Locations {

    /**
     * Cache of Long objects for the range 0-3999. This is used
     * to avoid creating a huge amount of Long objects in getLocation().
     * We can't use Long.valueOf() because it caches only the first 128
     * values, and typical feature files have much more lines.
     */
    private final static Long[] longs = new Long[4000];
    static {
        for (int i = 0; i < longs.length; i++) {
            longs[i] = (long) i;
        }
    }

    private static Long getLong(int i) {
        if (i>=longs.length) return (long) i;
        return longs[i];
    }

    static Location atColumn(Location location, int column) {
        requireNonNull(location);
        if (column <= 0) {
            throw new IllegalArgumentException("Columns are index-1 based");
        }
        return new Location(location.getLine(), getLong(column));
    }

    static Location atLine(int line) {
        return new Location(getLong(line), null);
    }

}
