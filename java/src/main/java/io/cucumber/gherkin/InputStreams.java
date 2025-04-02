package io.cucumber.gherkin;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

class InputStreams {
    /**
     * Average line length in a feature file. 100 is a reasonable assumption.
     */
    public static final int AVERAGE_LINE_LENGTH = 100;

    /**
     * The maximum number of lines in a feature file. 2048 is a reasonable assumption.
     */
    public static final int AVERAGE_LINE_COUNT = 2048;

    /**
     * Shim for InputStream.readAllBytes
     */
    static byte[] readAllBytes(InputStream source) throws IOException {
        final byte[] buffer = new byte[2 * 1024]; // 2KB
        int read;
        // The BAOS initial capacity is guessed from the
        // average line count and average line length,
        // to avoid redimensioning the underlying array.
        try (ByteArrayOutputStream outputStream = new ByteArrayOutputStream(AVERAGE_LINE_COUNT*AVERAGE_LINE_LENGTH)) {
            while (-1 != (read = source.read(buffer, 0, buffer.length))) {
                outputStream.write(buffer, 0, read);
            }
            return outputStream.toByteArray();
        }
    }

}
