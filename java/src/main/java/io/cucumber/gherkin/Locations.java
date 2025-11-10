package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;

import static java.util.Objects.requireNonNull;

class Locations {

    /**
     * Columns are index-1 based.
     */
    static final int COLUMN_OFFSET = 1;

    /**
     * Cache of Long objects for the range 0-4095. This is used
     * to avoid creating a huge amount of Long objects in getLocation().
     * We can't use Long.valueOf() because it caches only the first 128
     * values, and typical feature files have much more lines.
     */
    private static final Integer[] ints = new Integer[4096];

    static {
        for (int i = 0; i < ints.length; i++) {
            ints[i] = i;
        }
    }

    private static Integer getInteger(int i) {
        // JMH benchmark shows that this implementation is the
        // fastest when i<4096 (and about 20% slower than
        // Long.valueOf() when i>=4096).
        //
        // Tested variants:
        // - static pre-initialized cache of 127 elements
        //   (`Long.valueOf`)
        // - static pre-initialized cache of 4096 elements
        //   (the current implemented version)
        // - dynamic pre-initialized cache with 256 / 512 /
        //   1024/2048/4096 initial size
        // - dynamic lazy initialized cache with 256
        //   initialized size
        if (i >= ints.length) {
            return i;
        }
        return ints[i];
    }

    static Location atColumn(Location location, int column) {
        requireNonNull(location);
        if (column <= 0) {
            throw new IllegalArgumentException("Columns are index-1 based");
        }
        return new Location(location.getLine(), getInteger(column));
    }

    static Location atLine(int line) {
        if (line < 0) {
            throw new IllegalArgumentException("Lines are index-0 based");
        }
        return new Location(getInteger(line), null);
    }

}
