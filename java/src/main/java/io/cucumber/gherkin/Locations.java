package io.cucumber.gherkin;

import io.cucumber.messages.types.Location;

final class Locations {

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
    private static final Long[] longs = new Long[4096];

    static {
        for (int i = 0; i < longs.length; i++) {
            longs[i] = (long) i;
        }
    }

    private static Long getLong(long i) {
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
        if (i >= longs.length) {
            return i;
        }
        return longs[(int) i];
    }

    static Location atColumn(Location location, long column) {
        // By design, the location cannot be null (it comes from the Token)
        // By design, the column cannot be less than 1
        return new Location(location.getLine(), getLong(column));
    }

    static Location atLine(long line) {
        // By design, the column cannot be less than 1 (it comes from TokenScanner)
        return new Location(getLong(line), null);
    }

}
