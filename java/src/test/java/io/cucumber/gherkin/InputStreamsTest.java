package io.cucumber.gherkin;

import org.junit.jupiter.api.Test;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;

import static io.cucumber.gherkin.GherkinParser.FEATURE_FILE_AVERAGE_SIZE;
import static org.junit.jupiter.api.Assertions.assertArrayEquals;

class InputStreamsTest {

    @Test
    void readsAllBytes() throws IOException {
        byte[] input = "# sample comment".getBytes(StandardCharsets.UTF_8);
        try (InputStream is = new ByteArrayInputStream(input)) {
            assertArrayEquals(input, InputStreams.readAllBytes(is, FEATURE_FILE_AVERAGE_SIZE));
        }
    }

    @Test
    void readsALotOfBytes() throws IOException {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < 4028; i++) {
            builder.append("# sample comment\n");
        }
        byte[] input = builder.toString().getBytes(StandardCharsets.UTF_8);
        try (InputStream is = new ByteArrayInputStream(input)) {
            assertArrayEquals(input, InputStreams.readAllBytes(is, FEATURE_FILE_AVERAGE_SIZE));
        }
    }

}
