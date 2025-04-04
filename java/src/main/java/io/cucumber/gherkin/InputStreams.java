package io.cucumber.gherkin;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

class InputStreams {
    /**
     * Shim for InputStream.readAllBytes
     */
    static byte[] readAllBytes(InputStream source) throws IOException {
        final byte[] buffer = new byte[2 * 1024]; // 2KB
        int read;
        // The BAOS initial capacity is guessed from the average line count
        // and average line length, to avoid resizing the underlying array.
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream(GherkinParser.FEATURE_FILE_AVERAGE_SIZE);
        while (-1 != (read = source.read(buffer, 0, buffer.length))) {
            outputStream.write(buffer, 0, read);
        }
        return outputStream.toByteArray();
    }

}
